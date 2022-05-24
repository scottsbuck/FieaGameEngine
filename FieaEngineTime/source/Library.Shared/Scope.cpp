#include "pch.h"
#include "Scope.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Scope)

	Scope::Scope(size_t capacity) :
		mHashmap(capacity)
	{
		mVector.Reserve(capacity);
	}

	Scope::~Scope()
	{
		if (mParentScope != nullptr)
		{
			Orphan(*this);
		}
		Clear();
	}

	Scope::Scope(const Scope& other) :
		mHashmap(other.mHashmap.BucketCount())	
	{
		mVector.Reserve(other.mVector.Capacity());

		for (size_t i = 0; i < other.mVector.Size(); i++)
		{
			if (other.mVector[i]->second.Type() == Datum::DatumTypes::Table)
			{
				mVector.PushBack(&(*mHashmap.Insert(std::make_pair(other.mVector[i]->first, Datum(Datum::DatumTypes::Table)))));
				for (size_t j = 0; j < other.mVector[i]->second.Size(); j++)
				{
					Scope* scopeChild = other.mVector[i]->second.GetScope(j)->Clone();
					scopeChild->mParentScope = this;
					mVector[i]->second.PushBack(*scopeChild);
				}
			}
			else
			{
				Datum* d = &Append(other.mVector[i]->first);
				*d = other.mVector[i]->second;
			}
		}
	}

	Scope& Scope::operator=(const Scope& other)
	{
		if (this != &other)
		{
			Clear();

			mVector.Reserve(other.mVector.Capacity());

			for (size_t i = 0; i < other.mVector.Size(); i++)
			{
				if (other.mVector[i]->second.Type() == Datum::DatumTypes::Table)
				{
					mVector.PushBack(&(*mHashmap.Insert(std::make_pair(other.mVector[i]->first, Datum(Datum::DatumTypes::Table)))));
					for (size_t j = 0; j < other.mVector[i]->second.Size(); j++)
					{
						Scope* scopeChild = other.mVector[i]->second.GetScope(j)->Clone();
						scopeChild->mParentScope = this;
						mVector[i]->second.PushBack(*scopeChild);
					}
				}
				else
				{
					Datum* d = &Append(other.mVector[i]->first);
					*d = other.mVector[i]->second;
				}
			}
		}
		return *this;
	}

	Scope::Scope(Scope&& other) noexcept :
		mParentScope(other.mParentScope), mHashmap(std::move(other.mHashmap)), mVector(std::move(other.mVector))
	{
		if (other.mParentScope != nullptr)
		{
			auto [index, datum] = other.mParentScope->FindContainedScope(&other);
			datum->Set(*this, index);
			other.mParentScope = nullptr;
		}
		for (size_t i = 0; i < mVector.Size(); i++)
		{
			if (mVector[i]->second.Type() == Datum::DatumTypes::Table)
			{
				for (size_t j = 0; j < mVector[i]->second.Size(); j++)
				{
					mVector[i]->second.GetScope(j)->mParentScope = this;
				}
			}
		}
	}

	Scope& Scope::operator=(Scope&& other) noexcept
	{
		if (this != &other)
		{
			Clear();

			mParentScope = other.mParentScope;
			mHashmap = std::move(other.mHashmap);
			mVector = std::move(other.mVector);

			if (other.mParentScope != nullptr)
			{
				auto [index, datum] = other.mParentScope->FindContainedScope(&other);
				datum->Set(*this, index);
				other.mParentScope = nullptr;
			}
			for (size_t i = 0; i < mVector.Size(); i++)
			{
				if (mVector[i]->second.Type() == Datum::DatumTypes::Table)
				{
					for (size_t j = 0; j < mVector[i]->second.Size(); j++)
					{
						mVector[i]->second.GetScope(j)->mParentScope = this;
					}
				}
			}
		}

		return *this;
	}

	gsl::owner<Scope*> Scope::Clone() const
	{
		return new Scope(*this);
	}

	Datum& Scope::operator[](const std::string& string)
	{
		return Append(string);
	}

	Datum& Scope::operator[](size_t index)
	{
		return mVector[index]->second;
	}

	const Datum& Scope::operator[](size_t index) const
	{
		return mVector[index]->second;
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		const Scope* scope = const_cast<RTTI*>(rhs)->As<Scope>();
		return !operator!=(*scope);
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		return !operator!=(rhs);
	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		if (&rhs == this)
		{
			return false;
		}
		if (mVector.Size() != rhs.mVector.Size())
		{
			return true;
		}
		for (size_t i = 0; i < mVector.Size(); i++)
		{
			if (mVector[i]->second.Type() == Datum::DatumTypes::Table)
			{
				if (mVector[i]->second.Size() != rhs.mVector[i]->second.Size())
				{
					return true;
				}
				for (size_t j = 0; j < mVector[i]->second.Size(); j++)
				{
					if (*mVector[i]->second.GetScope(j) != *rhs.mVector[i]->second.GetScope(j))
					{
						return true;
					}
				}
			}
			else
			{
				if (mVector[i]->first != rhs.mVector[i]->first || mVector[i]->second != rhs.mVector[i]->second)
				{
					return true;
				}
			}
		}
		return false;
	}

	void Scope::Clear()
	{
		for (size_t i = 0; i < mVector.Size(); i++)
		{
			if (mVector[i]->second.Type() == Datum::DatumTypes::Table)
			{
				size_t size = mVector[i]->second.Size();
				for (size_t j = 0; j < size; j++)
				{
					delete mVector[i]->second.GetScope();
				}
			}
		}
		mVector.Clear();
		mHashmap.Clear();
	}

	Datum* Scope::Find(const std::string& string)
	{
		HashMap<std::string, Datum>::Iterator iterator = mHashmap.Find(string);
		if (iterator == mHashmap.end())
		{
			return nullptr;
		}
		return &(*iterator).second;
	}

	const Datum* Scope::Find(const std::string& string) const
	{
		HashMap<std::string, Datum>::ConstIterator iterator = mHashmap.Find(string);
		if (iterator == mHashmap.end())
		{
			return nullptr;
		}
		return &(*iterator).second;
	}

	std::pair<size_t, Datum*> Scope::FindContainedScope(const Scope* scope)
	{
		for (size_t i = 0; i < mVector.Size(); i++)
		{
			if (mVector[i]->second.Type() == Datum::DatumTypes::Table)
			{
				for (size_t j = 0; j < mVector[i]->second.Size(); j++)
				{
					if (*mVector[i]->second.GetScope(j) == *scope)
					{
						return std::make_pair(j, &mVector[i]->second);
					}
				}
			}
		}
		return std::make_pair(mVector.Size(), nullptr);
	}

	Datum* Scope::Search(const std::string& string)
	{
		Scope* scope = this;
		while (scope != nullptr)
		{
			HashMap<std::string, Datum>::Iterator iterator = scope->mHashmap.Find(string);
			if (iterator != scope->mHashmap.end())
			{
				return &((*iterator).second);
			}
			scope = scope->mParentScope;
		}
		return nullptr;
	}

	Datum* Scope::Search(const std::string& string, Scope*& scope)
	{
		scope = this;
		while (scope != nullptr)
		{
			HashMap<std::string, Datum>::Iterator iterator = scope->mHashmap.Find(string);
			if (iterator != scope->mHashmap.end())
			{
				return &((*iterator).second);
			}
			scope = scope->mParentScope;
		}
		return nullptr;
	}

	const Datum* Scope::Search(const std::string& string) const
	{
		Scope const* scope = this;
		while (scope != nullptr)
		{
			HashMap<std::string, Datum>::ConstIterator iterator = scope->mHashmap.Find(string);
			if (iterator != scope->mHashmap.end())
			{
				return &((*iterator).second);
			}
			scope = scope->mParentScope;
		}
		return nullptr;
	}

	const Datum* Scope::Search(const std::string& string, const Scope *& scope) const
	{
		scope = this;
		while (scope != nullptr)
		{
			HashMap<std::string, Datum>::ConstIterator iterator = scope->mHashmap.Find(string);
			if (iterator != scope->mHashmap.end())
			{
				return &((*iterator).second);
			}
			scope = scope->mParentScope;
		}
		return nullptr;
	}

	Datum& Scope::Append(const std::string& string)
	{
		Vector<VectorType>::Iterator iterator = mVector.Find(&(*mHashmap.Insert(std::make_pair(string, Datum()))));
		if (iterator == mVector.end())
		{
			mVector.PushBack(&(*(mHashmap.Find(string))));
			return mVector.Back()->second;
		}
		return (*iterator)->second;
	}

	Scope& Scope::AppendScope(const std::string& string)
	{
		Vector<VectorType>::Iterator iterator = mVector.Find(&(*mHashmap.Insert(std::make_pair(string, Datum(Datum::DatumTypes::Table)))));
		if (iterator == mVector.end())
		{
			mVector.PushBack(&(*(mHashmap.Find(string))));
			mVector.Back()->second.PushBack(*new Scope());
			mVector.Back()->second.GetScope()->mParentScope = this;
			return *mVector.Back()->second.GetScope();
		}
		else
		{
			if ((*iterator)->second.Type() != Datum::DatumTypes::Table && (*iterator)->second.Type() != Datum::DatumTypes::Unknown)
			{
				throw std::runtime_error("Key already exists in Scope and is not type Table. Cannot adopt Scope into a non Table Datum");
			}
			(*iterator)->second.PushBack(*new Scope());
			(*iterator)->second.BackScope()->mParentScope = this;
			return *(*iterator)->second.BackScope();
		}
	}

	void Scope::Adopt(const std::string& string, Scope& scope)
	{
		if (!IsDescendantOf(scope))
		{
			if (scope.mParentScope != nullptr)
			{
				Orphan(scope);
			}
			HashMap<std::string, Datum>::Iterator iterator = mHashmap.Find(string);
			if (iterator != mHashmap.end())
			{
				if ((*iterator).second.Type() != Datum::DatumTypes::Table)
				{
					throw std::runtime_error("Key already exists in Scope and is not type Table. Cannot adopt Scope into a non Table Datum");
				}
				scope.mParentScope = this;
				(*iterator).second.PushBack(scope);
			}
			else
			{
				mVector.PushBack(&(*(mHashmap.Insert(std::make_pair(string, Datum(Datum::DatumTypes::Table))))));
				scope.mParentScope = this;
				mVector.Back()->second.PushBack(scope);
			}
		}
	}

	bool Scope::IsAncestorOf(const Scope& scope) const
	{
		Scope* parent = scope.mParentScope;
		while (parent != nullptr)
		{
			if (parent == this)
			{
				return true;
			}
			parent = parent->mParentScope;
		}
		return false;
	}

	bool Scope::IsDescendantOf(const Scope& scope) const
	{
		return scope.IsAncestorOf(*this);
	}

	Scope* const Scope::GetParent() const
	{
		return mParentScope;
	}

	const size_t Scope::Size()
	{
		return mVector.Size();
	}

	void Scope::Orphan(Scope& scope)
	{
		assert(scope.mParentScope != nullptr);
		std::pair<size_t, Datum*> pair = scope.mParentScope->FindContainedScope(&scope);
		pair.second->RemoveAt(pair.first);
		scope.mParentScope = nullptr;
	}
}