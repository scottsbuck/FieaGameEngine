#include "Vector.h"
#include <cstdlib>
#include <stdexcept>
#include <cassert>

namespace FieaGameEngine
{
	template <typename T>
	Vector<T>::Vector() :
		mDataArray(nullptr), mSize(0), mCapacity(0)
	{
		Reserve(8);
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		Clear();
		free(mDataArray);
	}

	template<typename T>
	Vector<T>::Vector(const Vector& other) :
		mDataArray(nullptr), mSize(0), mCapacity(0)
	{
		Reserve(other.mCapacity);
		mCapacity = other.mCapacity;
		mSize = other.mSize;

		for (size_t i = 0; i < other.mSize; i++)
		{
			new (mDataArray + i) T(other.mDataArray[i]);
		}
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(const Vector& other)
	{
		if (this != &other)
		{
			Clear();

			Reserve(other.mCapacity);
			mCapacity = other.mCapacity;
			mSize = other.mSize;

			for (size_t i = 0; i < other.mSize; i++)
			{
				new (mDataArray + i) T(other.mDataArray[i]);
			}
		}

		return *this;
	}

	template<typename T>
	Vector<T>::Vector(Vector&& other) noexcept :
		mDataArray(other.mDataArray), mCapacity(other.mCapacity), mSize(other.mSize)
	{
		other.mDataArray = nullptr;
		other.mCapacity = 0;
		other.mSize = 0;
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
	{
		if (this != &other)
		{
			Clear();
			free(mDataArray);

			mDataArray = other.mDataArray;
			mCapacity = other.mCapacity;
			mSize = other.mSize;

			other.mDataArray = nullptr;
			other.mCapacity = 0;
			other.mSize = 0;
		}

		return *this;
	}

	template<typename T>
	Vector<T>::Vector(std::initializer_list<T> list) :
		mDataArray(nullptr), mSize(0), mCapacity(0)
	{
		Reserve(list.size());

		for (const auto& value : list)
		{
			PushBack(value);
		}
	}

	template<typename T>
	T& Vector<T>::operator[](size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Out of range exception");
		}
		return mDataArray[index];
	}

	template<typename T>
	const T& Vector<T>::operator[](size_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Out of range exception");
		}
		return mDataArray[index];
	}

	template<typename T>
	T& Vector<T>::At(size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Out of range exception");
		}
		return  mDataArray[index];
	}

	template<typename T>
	const T& Vector<T>::At(size_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Out of range exception");
		}
		return mDataArray[index];
	}

	template<typename T>
	void Vector<T>::PopBack()
	{
		if (mSize > 0)
		{
			mDataArray[mSize - 1].~T();
			mSize--;
		}
	}

	template<typename T>
	void Vector<T>::PushBack(const T& data)
	{
		if (mSize == mCapacity)
		{
			Reserve(static_cast<size_t>(2 * mCapacity));
		}
		new (mDataArray + mSize) T(data);
		mSize++;
	}

	template<typename T>
	void Vector<T>::Reserve(size_t capacity)
	{
		if (mCapacity < capacity)
		{
			mCapacity = capacity;
			T* buffer = static_cast<T*>(realloc(mDataArray, mCapacity * sizeof(T)));
			if (buffer != nullptr)
			{
				mDataArray = buffer;
			}
			else
			{
				throw std::runtime_error("Failed to allocate memory");
			}
		}
	}

	template<typename T>
	void Vector<T>::Clear()
	{
		for (size_t i = 0; i < mSize; i++)
		{
			mDataArray[i].~T();
		}
		mSize = 0;
	}

	template<typename T>
	const bool Vector<T>::IsEmpty()
	{
		return mSize == 0;
	}

	template<typename T>
	T& Vector<T>::Front()
	{
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray[0];
	}

	template<typename T>
	const T& Vector<T>::Front() const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray[0]; 
	}

	template<typename T>
	T& Vector<T>::Back()
	{
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray[mSize - 1];
	}

	template<typename T>
	const T& Vector<T>::Back() const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray[mSize - 1];
	}

	template<typename T>
	size_t Vector<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	size_t Vector<T>::Capacity() const
	{
		return mCapacity;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& data, std::function<bool(const T&, const T&)> equalityFunctor)
	{
		size_t i;
		for (i = 0; i < mSize; i++)
		{
			if (equalityFunctor(mDataArray[i], data))
			{
				return Iterator (*this, i);
			}
		}
		return Iterator (*this, i);
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::Find(const T& data, std::function<bool(const T&, const T&)> equalityFunctor) const
	{
		size_t i;
		for (i = 0; i < mSize; i++)
		{
			if (equalityFunctor(mDataArray[i], data))
			{
				return ConstIterator(*this, i);
			}
		}
		return ConstIterator(*this, i);
	}

	template<typename T>
	void Vector<T>::Remove(const T& data, std::function<bool(const T&, const T&)> equalityFunctor)
	{
		Remove(Find(data));
	}

	template<typename T>
	void Vector<T>::Remove(const Iterator& it, std::function<bool(const T&, const T&)> equalityFunctor)
	{
		if (it.mOwner != this)
		{
			throw std::invalid_argument("Invalid iterator. Owned by different container.");
		}

		if (it.mIndex < mSize)
		{
			mDataArray[it.mIndex].~T();

			size_t moveSize = (mSize - it.mIndex - 1) * sizeof(T);
			if (moveSize > 0)
			{
				memmove_s(&mDataArray[it.mIndex], moveSize, &mDataArray[it.mIndex + 1], moveSize);
			}

			mSize--;
		}

	}

	template<typename T>
	void Vector<T>::Remove(const Iterator& first, const Iterator& last, std::function<bool(const T&, const T&)> equalityFunctor)
	{
		size_t indexFirst = 0;
		size_t indexLast = 0;
		size_t i = 0; 
		bool indexFirstSet = false;
		bool indexLastSet = false;
		for (Iterator it = begin(); it != end(); ++it, ++i)
		{
			if (it == first)
			{
				indexFirst = i;
				indexFirstSet = true;
			}
			if(it == last)
			{
				indexLast = i - 1;
				indexLastSet = true;
			}
			if (indexFirstSet && indexLastSet)
			{
				break;
			}
		}
		if (last == end())
		{
			indexLast = mSize - 1;
			indexLastSet = true;
		}
		if (indexFirstSet && indexLastSet)
		{
			if (indexLast > indexFirst)
			{
				size_t j = 1;
				for (i = indexFirst; indexLast + j < mSize; ++i, ++j)
				{
					mDataArray[i] = mDataArray[indexLast + j];
				}
				for (i; i < mSize; i++)
				{
					mDataArray[i].~T();
				}
				mSize -= (indexLast - indexFirst + 1);
			}
			else if (indexLast == indexFirst)
			{
				Remove(*first);
			}
		}
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::begin()
	{
		return Iterator (*this, 0);
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::begin() const
	{
		
		return ConstIterator (*this, 0);
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::end()
	{
		
		return Iterator (*this, mSize);
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::end() const
	{
		
		return ConstIterator (*this, mSize);
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::cbegin() const
	{
		return ConstIterator (*this, 0);
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::cend() const
	{
		
		return ConstIterator (*this, mSize);
	}

	template<typename T>
	Vector<T>::Iterator::Iterator(const Vector& owner, size_t index) :
		mOwner(&owner), mIndex(index)
	{

	}

	template<typename T>
	bool Vector<T>::Iterator::operator==(const Vector<T>::Iterator& other) const
	{
		return mOwner == other.mOwner && mIndex == other.mIndex;
	}

	template<typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& other) const
	{
		return !operator==(other);
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}

		assert(mIndex < mOwner->mSize);

		mIndex++;
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator temp = *this;
		operator++();
		return temp;
	}

	template<typename T>
	T& Vector<T>::Iterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("The Iterator does not refer to a container, cannot access the data of a null container");
		}
		if (mIndex >= mOwner->mSize)
		{
			throw std::runtime_error("The Iterator does not refer to a proper index, out of bounds exception.");
		}
		return mOwner->mDataArray[mIndex];
	}

	template<typename T>
	Vector<T>::ConstIterator::ConstIterator(const Iterator& other) :
		mOwner(other.mOwner), mIndex(other.mIndex)
	{

	}

	template<typename T>
	bool Vector<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return mOwner == other.mOwner && mIndex == other.mIndex;
	}

	template<typename T>
	bool Vector<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return !operator==(other);
	}

	template<typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("ConstIterator is not associated with a container");
		}

		assert(mIndex < mOwner->mSize);

		mIndex++;
		return *this;
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int)
	{
		ConstIterator temp = *this;
		operator++();
		return temp;
	}

	template<typename T>
	const T& Vector<T>::ConstIterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("The ConstIterator does not refer to a container, cannot access the data of a null container");
		}
		if (mIndex >= mOwner->mSize)
		{
			throw std::runtime_error("The ConstIterator does not refer to a proper index, out of bounds exception.");
		}
		return mOwner->mDataArray[mIndex];
	}

	template<typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Vector& owner, size_t index) :
		mOwner(&owner), mIndex(index)
	{

	}
}
