#pragma once
#include <cstdlib>
#include <functional>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include "Vector.h"
#include "SList.h"
#include "DefaultHash.h"

namespace FieaGameEngine
{
	template <typename TKey, typename TData>
	class HashMap
	{

	public:
		using PairType = std::pair<TKey, TData>;
		using ChainType = SList<PairType>;
		using BucketType = Vector<ChainType>;

		class Iterator
		{

			friend HashMap;

		public:
			/// <summary>
			/// default constructor, initializes mIndex to 0 and mOwner to nullptr
			/// </summary>
			Iterator() = default;

			/// <summary>
			/// copy constructor
			/// </summary>
			/// <param name="other">takes in another iterator and copies it</param>
			Iterator(const Iterator& other) = default;

			/// <summary>
			/// copy assignment operator
			/// </summary>
			/// <param name="other">takes in another iterator and copies it</param>
			/// <returns>returns the iterator copy</returns>
			Iterator& operator=(const Iterator& other) = default;
			/// <summary>
			/// move constructor
			/// </summary>
			/// <param name="other">takes in another iterator and moves all its data to new iterator constructed</param>
			Iterator(Iterator&& other) = default;
			/// <summary>
			/// move assingment operator
			/// </summary>
			/// <param name="other">takes in another iterator and moves all its data to new iterator</param>
			/// <returns>iterator with data</returns>
			Iterator& operator=(Iterator&& other) = default;

			/// <summary>
			/// default destructor
			/// </summary>
			~Iterator() = default;

			/// <summary>
			/// comparison operator overload. checks the owner and index and compares those
			/// </summary>
			/// <param name="other">right hand value, left hand is the object the operator is being called on</param>
			/// <returns>if either owner or index arent the same return false, if both are the same return true</returns>
			bool operator==(const Iterator& other) const;

			/// <summary>
			/// calls inverse of the == operator
			/// </summary>
			/// <param name="other">look at == operator</param>
			/// <returns>inverse of == operator</returns>
			bool operator!=(const Iterator& other) const;

			/// <summary>
			/// Moves iterator to point to the next index
			/// </summary>
			/// <returns>returns the reference to the updated iterator</returns>
			Iterator& operator++();

			/// <summary>
			/// moves iterator to point to next index
			/// </summary>
			/// <returns>returns a copy of the non updated iterator</returns>
			Iterator operator++(int);

			/// <summary>
			/// dereference operator
			/// </summary>
			/// <returns>returns the data associated with the index the iterator points to</returns>
			PairType& operator*() const;

			/// <summary>
			/// pointer dereference operator
			/// </summary>
			/// <returns>returns a pointer to the data associated with the index the iterator points to</returns>
			PairType* operator->() const;

		private:
			Iterator(HashMap& owner, size_t index);
			Iterator(HashMap& owner, size_t index, typename ChainType::Iterator sListIterator);
			HashMap* mOwner{ nullptr };
			size_t mIndex{ 0 };
			typename ChainType::Iterator mSListIterator;

		};

		class ConstIterator
		{

			friend HashMap;

		public:
			/// <summary>
			/// default constructor. Initializes the ConstIterator mIndex to 0 and mOwner to nullptr
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// copy constructor
			/// </summary>
			/// <param name="other">takes in another ConstIterator and copies it</param>
			ConstIterator(const ConstIterator& other) = default;

			/// <summary>
			/// copy assignment operator
			/// </summary>
			/// <param name="other">takes in another ConstIterator and copies it</param>
			/// <returns>returns the ConstIterator copy</returns>
			ConstIterator& operator=(const ConstIterator& other) = default;

			/// <summary>
			/// move constructor
			/// </summary>
			/// <param name="other">takes in another iterator and moves all its data to new iterator constructed</param>
			ConstIterator(ConstIterator&& other) = default;

			/// <summary>
			/// move assingment operator
			/// </summary>
			/// <param name="other">takes in another iterator and moves all its data to new iterator</param>
			/// <returns>iterator with data</returns>
			ConstIterator& operator=(ConstIterator&& other) = default;

			/// <summary>
			/// default destructor
			/// </summary>
			~ConstIterator() = default;

			/// <summary>
			/// default destructor
			/// </summary>
			ConstIterator(const Iterator& other);

			/// <summary>
			/// comparison operator overload. checks the owner and index and compares those
			/// </summary>
			/// <param name="other">right hand value, left hand is the object the operator is being called on</param>
			/// <returns>if either owner or index arent the same return false, if both are the same return true</returns>
			bool operator==(const ConstIterator& other) const;

			/// <summary>
			/// calls inverse of the == operator
			/// </summary>
			/// <param name="other">look at == operator</param>
			/// <returns>inverse of == operator</returns>
			bool operator!=(const ConstIterator& other) const;

			/// <summary>
			/// Moves ConstIterator to point to the next index
			/// </summary>
			/// <returns>returns the reference to the updated ConstIterator</returns>
			ConstIterator& operator++();

			/// <summary>
			/// moves ConstIterator to point to next index
			/// </summary>
			/// <returns>returns a copy of the non updated ConstIterator</returns>
			ConstIterator operator++(int);

			/// <summary>
			/// dereference operator
			/// </summary>
			/// <returns>returns the data associated with the index the ConstIterator points to</returns>
			const PairType& operator*() const;

			/// <summary>
			/// arrow dereference operator
			/// </summary>
			/// <returns>returns a pointer to the data associated with the index the ConstIterator points to</returns>
			const PairType* operator->() const;

		private:
			ConstIterator(const HashMap& owner, size_t index);
			ConstIterator(const HashMap& owner, size_t index, typename ChainType::ConstIterator sListIterator);
			const HashMap* mOwner{ nullptr };
			size_t mIndex{ 0 };
			typename ChainType::ConstIterator mSListIterator;
		};

		/// <summary>
		/// operator[] overide for hashmap specification
		/// </summary>
		/// <param name="key">takes in a key value</param>
		/// <returns>the TData associated with the key value in the hashmap</returns>
		TData& operator[](const TKey& key);

		/// <summary>
		/// operator[] overide for hashmap specification
		/// </summary>
		/// <param name="key">takes in a key value</param>
		/// <returns>the TData associated with the key value in the hashmap</returns>
		const TData& operator[](const TKey& key) const;

		/// <summary>
		/// Constructor for hashmap
		/// </summary>
		/// <param name="size">takes in a size parameter that is the bucket amount</param>
		/// <param name="hashFunctor">takes in a custom hashfunctor for the key type</param>
		/// <param name="equalityFunctor">takes in a custom equalityfunctor to compare key types</param>
		HashMap(size_t size = 11, std::function<size_t(const TKey&)> hashFunctor = DefaultHash<TKey>(), std::function<bool(const TKey&, const TKey&)> equalityFunctor = std::equal_to<TKey>());
		
		/// <summary>
		/// Intializer list Constructor for hashmap
		/// </summary>
		/// <param name="list">takes in an initializer list and initalizes the hashmap to have those pairs inserted</param>
		/// <param name="hashFunctor">takes in a custom hashfunctor for the key type</param>
		/// <param name="equalityFunctor">takes in a custom equalityfunctor to compare key types</param>
		HashMap(std::initializer_list<PairType> list, std::function<size_t(const TKey&)> hashFunctor, std::function<bool(const TKey&, const TKey&)> equalityFunctor);

		/// <summary>
		/// Default Destructor
		/// </summary>
		~HashMap() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other">hashmap to be copied</param>
		HashMap(const HashMap& other) = default;

		/// <summary>
		/// Default copy assignment operator
		/// </summary>
		/// <param name="other">hashmap to be copied</param>
		/// <returns>copied hashmap</returns>
		HashMap& operator=(const HashMap& other) = default;

		/// <summary>
		/// Default Move Constructor
		/// </summary>
		/// <param name="other">hashmap to be moved</param>
		HashMap(HashMap && other) = default;

		/// <summary>
		/// Default move assignment operator
		/// </summary>
		/// <param name="other">hashmap to be moved</param>
		/// <returns>moved hashmap</returns>
		HashMap& operator=(HashMap&& other) = default;

		/// <summary>
		/// Takes in a key and returns an iterator pointing to it
		/// </summary>
		/// <param name="key">key to be hashed and searched for in the hashmap</param>
		/// <returns>iterator pointing to the inserted pair associated with the key</returns>
		Iterator Find(const TKey& key);

		/// <summary>
		/// Takes in a key and returns an iterator pointing to it
		/// </summary>
		/// <param name="key">key to be hashed and searched for in the hashmap</param>
		/// <returns>iterator pointing to the inserted pair associated with the key</returns>
		ConstIterator Find(const TKey& key) const;

		/// <summary>
		/// Inserts a pair into the hashmap
		/// </summary>
		/// <param name="pair">pair to be inserted with first being key, second being data</param>
		/// <returns>Iterator pointing to inserted pair</returns>
		Iterator Insert(const PairType& pair);

		/// <summary>
		/// Removes pair associated with the key
		/// </summary>
		/// <param name="key">key to be hashed to find the pair to be removed</param>
		void Remove(const TKey& key);

		/// <summary>
		/// empties the list completely
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns mSize
		/// </summary>
		/// <returns>returns how many times you have inserted a value into the hashmap</returns>
		size_t Size() const;

		size_t BucketCount() const;

		/// <summary>
		/// checks to see if a key is in the hashmap or not
		/// </summary>
		/// <param name="key">key to search for in the hashmap</param>
		/// <returns>a boolean indicating the key is in the hashmap or not</returns>
		bool ContainsKey(const TKey& key);

		/// <summary>
		/// returns the data at the hashed keys index
		/// </summary>
		/// <param name="key">key to be hashed to locate the data within the hashmap</param>
		/// <returns>data associated with the key</returns>
		TData& At(const TKey& key);

		/// <summary>
		/// returns the data at the hashed keys index
		/// </summary>
		/// <param name="key">key to be hashed to locate the data within the hashmap</param>
		/// <returns>data associated with the key</returns>
		const TData& At(const TKey& key) const;

		/// <summary>
		/// returns the iterator pointing to the first element in the hashmap. In order of the map, not order of insert
		/// </summary>
		/// <returns>iterator pointing to first item in the hashmap</returns>
		Iterator begin();

		/// <summary>
		/// Returns the iterator pointing to the end of the hashmap.
		/// </summary>
		/// <returns>an iterator poitnign to the end of the hashmap</returns>
		Iterator end();

		/// <summary>
		/// returns the constiterator pointing to the first element in the hashmap. In order of the map, not order of insert
		/// </summary>
		/// <returns>constiterator pointing to first item in the hashmap</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Returns the constiterator pointing to the end of the hashmap.
		/// </summary>
		/// <returns>an constiterator poitnign to the end of the hashmap</returns>
		ConstIterator end() const;

		/// <summary>
		/// returns the constiterator pointing to the first element in the hashmap. In order of the map, not order of insert
		/// </summary>
		/// <returns>constiterator pointing to first item in the hashmap</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Returns the constiterator pointing to the end of the hashmap.
		/// </summary>
		/// <returns>an constiterator poitnign to the end of the hashmap</returns>
		ConstIterator cend() const;

	private:

		size_t mSize;
		BucketType mBuckets;
		
		std::function<size_t(const TKey&)> mHashFunctor;
		std::function<bool(const TKey&, const TKey&)> mEqualityFunctor;
	};

}

#include "HashMap.inl"