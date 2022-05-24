#include "SList.h"
#include <cstdlib>
#include <stdexcept>
#include <cassert>

namespace FieaGameEngine
{
	template <typename T>
	SList<T>::SList() :
		mSize(0), mFrontNode(nullptr), mBackNode(nullptr)
	{

	}

	template <typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template <typename T>
	SList<T>::SList(const SList& other) :
		mSize(0), mFrontNode(nullptr), mBackNode(nullptr)
	{

		Node* tempNode = other.mFrontNode;
		for (size_t i = 0; i < other.mSize; i++)
		{
			PushBack(tempNode->data);
			tempNode = tempNode->nextNode;
		}
	}

	template<typename T>
	SList<T>::SList(std::initializer_list<T> list)
	{
		for (const auto& value : list)
		{
			PushBack(value);
		}
	}

	template <typename T>
	SList<T>& SList<T>::operator=(const SList& other)
	{
		if (this != &other)
		{
			Clear();

			mSize = other.mSize;
			Node* tempNode = other.mFrontNode;
			mFrontNode = new Node(tempNode->data, nullptr);
			mBackNode = mFrontNode;

			for (size_t i = 0; i < other.mSize; i++)
			{
				mBackNode->nextNode = new Node(tempNode->nextNode->data, nullptr);
				mBackNode = mBackNode->nextNode;
				tempNode = tempNode->nextNode;
			}
		}

		return *this;
	}

	template <typename T>
	SList<T>::Node::Node(const T& Data, Node* NextNode) :
		data(Data), nextNode(NextNode)
	{

	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::PushFront(const T& data)
	{
		mFrontNode = new Node(data, mFrontNode);
		mSize++;
		if (mSize == 1)
		{
			mBackNode = mFrontNode;
		}
		return begin();
	}

	template <typename T>
	void SList<T>::PopFront()
	{
		if (mSize != 0)
		{
			Node* tempNode = mFrontNode->nextNode;
			delete mFrontNode;
			mFrontNode = tempNode;
			tempNode = nullptr;

			if (mSize == 1)
			{
				mFrontNode = nullptr;
				mBackNode = nullptr;
			}
			mSize--;
		}
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::PushBack(const T& data)
	{
		Node* newBackNode = new Node(data, nullptr);
		if (mSize != 0)
		{
			mBackNode->nextNode = newBackNode;
		}
		mBackNode = newBackNode;
		mSize++;
		if (mSize == 1)
		{
			mFrontNode = newBackNode;
		}
		return Iterator(*this, mBackNode);
	}

	template <typename T>
	void SList<T>::PopBack()
	{
		if (mSize != 0)
		{
			Node* tempNode;
			tempNode = mFrontNode;
			if (mSize > 1)
			{
				while (tempNode->nextNode->nextNode != nullptr)
				{
					tempNode = tempNode->nextNode;
				}
			}
			tempNode->nextNode = nullptr;
			delete mBackNode;
			mBackNode = tempNode;
			mSize--;
			if (mSize == 0)
			{
				mBackNode = nullptr;
				mFrontNode = nullptr;
			}
		}
	}

	template <typename T>
	bool SList<T>::IsEmpty() const
	{
		return (mFrontNode == nullptr);
	}

	template <typename T>
	const T& SList<T>::Front() const
	{
		if (mFrontNode == nullptr)
		{
			throw std::runtime_error("Can't access data of nullptr");
		}
		return mFrontNode->data;
	}

	template<typename T>
	T& SList<T>::Front()
	{
		if (mFrontNode == nullptr)
		{
			throw std::runtime_error("Can't access data of nullptr");
		}
		return mFrontNode->data;
	}

	template <typename T>
	const T& SList<T>::Back() const
	{
		if (mBackNode == nullptr)
		{
			throw std::runtime_error("Can't access data of nullptr");
		}
		return mBackNode->data;
	}

	template<typename T>
	T& SList<T>::Back()
	{
		if (mBackNode == nullptr)
		{
			throw std::runtime_error("Can't access data of nullptr");
		}
		return mBackNode->data;
	}

	template <typename T>
	void SList<T>::Clear()
	{
		if (mSize != 0)
		{
			Node* tempNode;

			while (mFrontNode != nullptr)
			{
				tempNode = mFrontNode->nextNode;
				delete mFrontNode;
				mFrontNode = tempNode;
			}
			mSize = 0;
			mFrontNode = nullptr;
			mBackNode = nullptr;
		}
	}

	template <typename T>
	const std::size_t& SList<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::begin()
	{
		return Iterator(*this, mFrontNode);
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::end()
	{
		return Iterator(*this);
	}

	template<typename T>
	typename SList<T>::ConstIterator SList<T>::begin() const
	{
		return ConstIterator(*this, mFrontNode);
	}

	template<typename T>
	typename SList<T>::ConstIterator SList<T>::end() const
	{
		
		return ConstIterator(*this);
	}

	template<typename T>
	typename SList<T>::ConstIterator SList<T>::cbegin() const
	{
		
		return ConstIterator(*this, mFrontNode);
	}

	template<typename T>
	typename SList<T>::ConstIterator SList<T>::cend() const
	{
		
		return ConstIterator (*this);
	}

	template<typename T>
	void SList<T>::InsertAfter(const T& data, const Iterator& it)
	{
		if (this != it.mOwner)
		{
			throw std::runtime_error("This iterator is associated with a different container!");
		}
		if (it.mNode == mBackNode || it == end())
		{
			PushBack(data);
		}
		else
		{
			Node* newNode = new Node(data, it.mNode->nextNode);
			it.mNode->nextNode = newNode;
			mSize++;
		}
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& data, std::function<bool(const T&, const T&)> equalityFunctor)
	{
		Iterator it;
		for (it = begin(); it != end(); ++it)
		{
			if (equalityFunctor(*it, data))
			{
				break;
			}
		}
		return it;
	}

	template<typename T>
	typename SList<T>::ConstIterator SList<T>::Find(const T& data, std::function<bool(const T&, const T&)> equalityFunctor) const
	{
		ConstIterator it;
		for (it = begin(); it != end(); ++it)
		{
			if (equalityFunctor(*it, data))
			{
				break;
			}
		}
		return it;
	}

	template<typename T>
	void SList<T>::Remove(const T& data, std::function<bool(const T&, const T&)> equalityFunctor)
	{
		Remove(Find(data));
	}

	template<typename T>
	void SList<T>::Remove(const Iterator& it, std::function<bool(const T&, const T&)> equalityFunctor)
	{
		
		if (it != end())
		{
			if (it.mNode == mBackNode)
			{
				PopBack();
			}
			else
			{
				Node* tempNode = it.mNode->nextNode;
				it.mNode->data = tempNode->data;
				it.mNode->nextNode = tempNode->nextNode;
				if (tempNode->nextNode == nullptr)
				{
					mBackNode = it.mNode;
				}
				delete tempNode;
				mSize--;
			}
		}
	}

	template<typename T>
	SList<T>::Iterator::Iterator(const SList& owner, Node* node) :
		mOwner(&owner), mNode(node)
	{

	}

	template<typename T>
	bool SList<T>::Iterator::operator==(const SList<T>::Iterator& other) const
	{
		return mOwner == other.mOwner && mNode == other.mNode;
	}

	template<typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& other) const
	{
		return !operator==(other);
	}

	template<typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}

		assert(mNode != nullptr);

		mNode = mNode->nextNode;
		return *this;
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator temp = *this;
		operator++();
		return temp;
	}

	template<typename T>
	T& SList<T>::Iterator::operator*() const
	{
		if (mNode == nullptr)
		{
			throw std::runtime_error("The Iterator does not refer to a node, you can't dereference a nullptr");
		}
		return mNode->data;
	}

	template<typename T>
	SList<T>::ConstIterator::ConstIterator(const Iterator& other) :
		mOwner(other.mOwner), mNode(other.mNode)
	{

	}

	template<typename T>
	bool SList<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return mOwner == other.mOwner && mNode == other.mNode;
	}

	template<typename T>
	bool SList<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return !operator==(other);
	}

	template<typename T>
	typename SList<T>::ConstIterator& SList<T>::ConstIterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("ConstIterator is not associated with a container");
		}

		assert(mNode != nullptr);

		mNode = mNode->nextNode;
		return *this;
	}

	template<typename T>
	typename SList<T>::ConstIterator SList<T>::ConstIterator::operator++(int)
	{
		ConstIterator temp = *this;
		operator++();
		return temp;
	}

	template<typename T>
	const T& SList<T>::ConstIterator::operator*() const
	{
		if (mNode == nullptr)
		{
			throw std::runtime_error("The ConstIterator does not refer to a node, you can't dereference a nullptr");
		}
		return mNode->data;
	}

	template<typename T>
	inline SList<T>::ConstIterator::ConstIterator(const SList& owner, Node* node) :
		mOwner(&owner), mNode(node)
	{

	}
}