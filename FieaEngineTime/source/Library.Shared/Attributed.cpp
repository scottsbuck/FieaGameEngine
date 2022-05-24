#include "pch.h"
#include "Attributed.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Attributed)

	gsl::owner<Attributed*> Attributed::Clone() const
	{
		return new Attributed(*this);
	}

	Attributed::Attributed(IdType idType) :
		mIdType(idType)
	{
		Populate(idType);
	}

	Attributed::Attributed(const Attributed& other) :
		Scope(other), mIdType(other.mIdType)
	{
		Populate(mIdType, true);
	}

	Attributed& Attributed::operator=(const Attributed& other)
	{
		if (this != &other)
		{
			mIdType = other.mIdType;
			Scope::operator=(other);
			Populate(mIdType, true);
		}

		return *this;
	}

	Attributed::Attributed(Attributed&& other) :
		Scope(std::move(other)), mIdType(other.mIdType)
	{
		Populate(mIdType, true);

		other.mIdType = 0;
	}

	Attributed& Attributed::operator=(Attributed&& other)
	{
		if (this != &other)
		{
			mIdType = other.mIdType;
			Scope::operator=(std::move(other));
			Populate(mIdType, true);

			other.mIdType = 0;
		}

		return *this;
	}

	void Attributed::Populate(IdType idType, bool isCopying)
	{
		TypeRegistry& registry = registry.GetInstance();
		Vector<Signature> attributes = registry.GetAttributes(idType);
		Append("this") = this;
		uint8_t* thisPtr = reinterpret_cast<uint8_t*>(this);
		for (size_t i = 0; i < attributes.Size(); i++)
		{
			if (attributes[i].datumType == Datum::DatumTypes::Unknown)
			{
				throw std::runtime_error("Unkown datum type is not allowed");
			}
			if (attributes[i].datumType == Datum::DatumTypes::Table && !isCopying)
			{
				for (size_t j = 0; j < attributes[i].size; j++)
				{
					AppendScope(attributes[i].name);
				}
			}
			else if (attributes[i].datumType != Datum::DatumTypes::Table)
			{
				Append(attributes[i].name).SetStorage(attributes[i].datumType, thisPtr + attributes[i].offset, attributes[i].size);
			}
		}
	}

	bool Attributed::IsAttribute(const std::string& string)
	{
		return Find(string) != nullptr;
	}

	bool Attributed::IsPrescribedAttribute(const std::string& string)
	{
		TypeRegistry& registry = registry.GetInstance();
		const Vector<Signature>& vector = registry.GetAttributes(TypeIdInstance());
		for (size_t i = 0; i < vector.Size(); i++)
		{
			if (vector[i].name == string)
			{
				return true;
			}
		}
		return false;
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& string)
	{
		return IsAttribute(string) && !IsPrescribedAttribute(string);
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& string)
	{
		if (IsPrescribedAttribute(string))
		{
			throw std::runtime_error("Auxiliary attribute cannot have same name as a prescribed attribute");
		}
		return Append(string);
	}
}