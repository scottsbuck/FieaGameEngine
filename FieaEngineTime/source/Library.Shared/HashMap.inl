#include "HashMap.h"
#include <cstdlib>
#include <stdexcept>
#include <cassert>

namespace FieaGameEngine
{
	template<typename TKey, typename TData>
	TData& HashMap<TKey, TData>::operator[](const TKey& key)
	{
		size_t hashIndex = mHashFunctor(key) % mBuckets.Size();
		typename ChainType::Iterator it = mBuckets[hashIndex].begin();

		while (it != mBuckets[hashIndex].end())
		{
			if (mEqualityFunctor((*it).first, key))
			{
				return (*it).second;
			}
			it++;
		}

		auto pair = std::make_pair(key, TData());
		typename HashMap<TKey, TData>::Iterator  hashIt = Insert(pair);
		return (*hashIt).second;
	}

	template<typename TKey, typename TData>
	const TData& HashMap<TKey, TData>::operator[](const TKey& key) const
	{
		return At(key);
	}

	template<typename TKey, typename TData>
	HashMap<TKey, TData>::HashMap(size_t size, std::function<size_t(const TKey&)> hashFunctor, std::function<bool(const TKey&, const TKey&)> equalityFunctor) :
		mHashFunctor(hashFunctor), mEqualityFunctor(equalityFunctor), mSize(0)
	{
		mBuckets.Reserve(size);
		for (size_t i = 0; i < size; i++)
		{
			mBuckets.PushBack(ChainType());
		}
	}

	template<typename TKey, typename TData>
	HashMap<TKey, TData>::HashMap(std::initializer_list<PairType> list, std::function<size_t(const TKey&)> hashFunctor, std::function<bool(const TKey&, const TKey&)> equalityFunctor) :
		mHashFunctor(hashFunctor), mEqualityFunctor(equalityFunctor), mSize(0)
	{
		mBuckets.Reserve(list.size());
		for (size_t i = 0; i < list.size(); i++)
		{
			mBuckets.PushBack(ChainType());
		}

		for (const auto& value : list)
		{
			Insert(value);
		}
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Find(const TKey& key)
	{
		size_t hashIndex = mHashFunctor(key) % mBuckets.Size();
		typename ChainType::Iterator it = mBuckets[hashIndex].begin();
		while (it != mBuckets[hashIndex].end() && !mEqualityFunctor((*it).first, key) )
		{
			it++;
		}
		if (it == mBuckets[hashIndex].end())
		{
			return end();
		}
		return Iterator(*this, hashIndex, it);
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::Find(const TKey& key) const
	{
		size_t hashIndex = mHashFunctor(key) % mBuckets.Size();
		typename ChainType::ConstIterator it = mBuckets[hashIndex].begin();
		while (it != mBuckets[hashIndex].end() && !mEqualityFunctor((*it).first, key))
		{
			it++;
		}
		if (it == mBuckets[hashIndex].end())
		{
			return cend();
		}
		
		return ConstIterator(*this, hashIndex, it);
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Insert(const PairType& pair)
	{
		size_t hashIndex = mHashFunctor(pair.first) % mBuckets.Size();
		typename ChainType::Iterator sListIterator = mBuckets[hashIndex].begin();
		while (sListIterator != mBuckets[hashIndex].end())
		{
			if (mEqualityFunctor((*sListIterator).first, pair.first))
			{
				break;
			}
			sListIterator++;
		}
		if (sListIterator == mBuckets[hashIndex].end())
		{
			sListIterator = mBuckets[hashIndex].PushBack(pair);
			mSize++;
		}
		
		return Iterator(*this, hashIndex, sListIterator);
	}

	template<typename TKey, typename TData>
	void HashMap<TKey, TData>::Remove(const TKey& key)
	{
		size_t hashIndex = mHashFunctor(key) % mBuckets.Size();
		typename ChainType::Iterator it = mBuckets[hashIndex].begin();
		while (it != mBuckets[hashIndex].end() && !mEqualityFunctor((*it).first, key))
		{
			it++;
		}
		if (it != mBuckets[hashIndex].end())
		{
			mBuckets[hashIndex].Remove(it);
			mSize--;
		}
	}

	template<typename TKey, typename TData>
	void HashMap<TKey, TData>::Clear()
	{
		for (auto& chain: mBuckets)
		{
			chain.Clear();
		}

		mSize = 0;
		//mSize = 0;
		//size_t temp = mBuckets.Size();

		//BucketType tempBuckets;
		//mBuckets = tempBuckets;

		//for (size_t i = 0; i < temp; i++)
		//{
		//	mBuckets.PushBack(ChainType());
		//}
	}

	template<typename TKey, typename TData>
	size_t HashMap<TKey, TData>::Size() const
	{
		return mSize;
	}

	template<typename TKey, typename TData>
	size_t HashMap<TKey, TData>::BucketCount() const
	{
		return mBuckets.Size();
	}

	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::ContainsKey(const TKey& key)
	{
		auto it = begin();
		while (it != end())
		{
			if (mEqualityFunctor((*(it.mSListIterator)).first, key))
			{
				return true;
			}
			it++;
		}
		return false;
	}

	template<typename TKey, typename TData>
	TData& HashMap<TKey, TData>::At(const TKey& key)
	{
		size_t hashIndex = mHashFunctor(key) % mBuckets.Size();
		auto it = mBuckets[hashIndex].begin();

		while (it != mBuckets[hashIndex].end())
		{
			if (mEqualityFunctor((*it).first, key))
			{
				return (*it).second;
			}
			it++;
		}
		
		throw std::out_of_range("Key does not have an associated value in this hashmap");
	}

	template<typename TKey, typename TData>
	const TData& HashMap<TKey, TData>::At(const TKey& key) const
	{
		size_t hashIndex = mHashFunctor(key) % mBuckets.Size();
		auto it = mBuckets[hashIndex].begin();

		while (it != mBuckets[hashIndex].end())
		{
			if (mEqualityFunctor((*it).first, key))
			{
				return (*it).second;
			}
			it++;
		}

		throw std::out_of_range("Key does not have an associated value in this hashmap");
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::begin()
	{
		for (size_t i = 0; i < mBuckets.Size(); i++)
		{
			if (mBuckets[i].begin() != mBuckets[i].end())
			{
				return Iterator(*this, i);
			}
		}
		return Iterator(*this, mBuckets.Size());
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::begin() const
	{
		for (size_t i = 0; i < mBuckets.Size(); i++)
		{
			if (mBuckets[i].begin() != mBuckets[i].end())
			{
				return ConstIterator(*this, i);
			}
		}
		return ConstIterator(*this, mBuckets.Size());
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::end()
	{
		return Iterator(*this, mBuckets.Size());
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::end() const
	{
		return ConstIterator(*this, mBuckets.Size());
	}
	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::cbegin() const
	{
		for (size_t i = 0; i < mBuckets.Size(); i++)
		{
			if (mBuckets[i].begin() != mBuckets[i].end())
			{
				return ConstIterator(*this, i);
			}
		}
		return ConstIterator(*this, mBuckets.Size());
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::cend() const
	{
		return ConstIterator(*this, mBuckets.Size());
	}

	template<typename TKey, typename TData>
	HashMap<TKey, TData>::Iterator::Iterator(HashMap& owner, size_t index) :
		mOwner(&owner), mIndex(index)
	{
		if (index != mOwner->mBuckets.Size())
		{
			mSListIterator = mOwner->mBuckets[index].begin();
		}
	}

	template<typename TKey, typename TData>
	HashMap<TKey, TData>::Iterator::Iterator(HashMap& owner, size_t index, typename ChainType::Iterator sListIterator) :
		mOwner(&owner), mIndex(index), mSListIterator(sListIterator)
	{

	}

	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::Iterator::operator==(const HashMap<TKey, TData>::Iterator& other) const
	{
		return !operator!=(other);
	}

	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::Iterator::operator!=(const Iterator& other) const
	{
		return mOwner != other.mOwner || mIndex != other.mIndex || mSListIterator != other.mSListIterator;
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator& HashMap<TKey, TData>::Iterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}

		assert(mSListIterator != mOwner->mBuckets[mIndex].end());
		mSListIterator++;

		while (mIndex != mOwner->mBuckets.Size() && mSListIterator == mOwner->mBuckets[mIndex].end())
		{
			mIndex++;
			if (mIndex == mOwner->mBuckets.Size())
			{
				typename ChainType::Iterator it;
				mSListIterator = it;
			}
			else
			{
				mSListIterator = mOwner->mBuckets[mIndex].begin();
			}
		} 

		return *this;
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Iterator::operator++(int)
	{
		Iterator temp = *this;
		operator++();
		return temp;
	}

	template<typename TKey, typename TData>
	std::pair<TKey, TData>& HashMap<TKey, TData>::Iterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("The Iterator does not refer to a container, cannot access the data of a null container");
		}
		if (mIndex >= mOwner->mBuckets.Size())
		{
			throw std::runtime_error("The Iterator does not refer to a proper index, out of bounds exception.");
		}
		return *(mSListIterator);
	}

	template<typename TKey, typename TData>
	std::pair<TKey, TData>* HashMap<TKey, TData>::Iterator::operator->() const
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("The Iterator does not refer to a container, cannot access the data of a null container");
		}
		if (mIndex >= mOwner->mBuckets.Size())
		{
			throw std::runtime_error("The Iterator does not refer to a proper index, out of bounds exception.");
		}
		return &(*(mSListIterator));
	}

	template<typename TKey, typename TData>
	HashMap<TKey, TData>::ConstIterator::ConstIterator(const Iterator& other) :
		mOwner(other.mOwner), mIndex(other.mIndex), mSListIterator(other.mSListIterator)
	{

	}


	template<typename TKey, typename TData>
	HashMap<TKey, TData>::ConstIterator::ConstIterator(const HashMap& owner, size_t index, typename ChainType::ConstIterator sListIterator) :
		mOwner(&owner), mIndex(index), mSListIterator(sListIterator)
	{

	}
	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !operator!=(other);
	}

	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return mOwner != other.mOwner || mIndex != other.mIndex || mSListIterator != other.mSListIterator;
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator& HashMap<TKey, TData>::ConstIterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("ConstIterator is not associated with a container");
		}

		assert(mSListIterator != mOwner->mBuckets[mIndex].end());
		mSListIterator++;

		while (mIndex != mOwner->mBuckets.Size() && mSListIterator == mOwner->mBuckets[mIndex].end())
		{
			mIndex++;
			if (mIndex == mOwner->mBuckets.Size())
			{
				typename ChainType::ConstIterator it;
				mSListIterator = it;
			}
			else
			{
				mSListIterator = mOwner->mBuckets[mIndex].begin();
			}
		}

		return *this;
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::ConstIterator::operator++(int)
	{
		ConstIterator temp = *this;
		operator++();
		return temp;
	}

	template<typename TKey, typename TData>
	const std::pair<TKey, TData>& HashMap<TKey, TData>::ConstIterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("The ConstIterator does not refer to a container, cannot access the data of a null container");
		}
		if (mIndex >= mOwner->mBuckets.Size())
		{
			throw std::runtime_error("The ConstIterator does not refer to a proper index, out of bounds exception.");
		}
		return *(mSListIterator);
	}

	template<typename TKey, typename TData>
	const std::pair<TKey, TData>* HashMap<TKey, TData>::ConstIterator::operator->() const
	{
		if (mOwner == nullptr)
		{
			throw std::runtime_error("The ConstIterator does not refer to a container, cannot access the data of a null container");
		}
		if (mIndex >= mOwner->mBuckets.Size())
		{
			throw std::runtime_error("The ConstIterator does not refer to a proper index, out of bounds exception.");
		}
		return &(*(mSListIterator));
	}

	template<typename TKey, typename TData>
	HashMap<TKey, TData>::ConstIterator::ConstIterator(const HashMap& owner, size_t index) :
		mOwner(&owner), mIndex(index)
	{
		if (index != mOwner->mBuckets.Size())
		{
			mSListIterator = mOwner->mBuckets[index].begin();
		}
	}
}