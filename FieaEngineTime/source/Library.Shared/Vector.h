#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>
#include <initializer_list>

namespace FieaGameEngine
{
	template <typename T>
	class Vector
	{
	public:

		class Iterator
		{

			friend Vector;

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
			T& operator*() const;

		private:
			Iterator(const Vector& owner, size_t index);
			const Vector* mOwner{ nullptr };
			size_t mIndex{ 0 };

		};

		class ConstIterator
		{

			friend Vector;

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
			const T& operator*() const;

		private:
			ConstIterator(const Vector& owner, size_t index);
			const Vector* mOwner{ nullptr };
			size_t mIndex{ 0 };
		};
		
		/// <summary>
		/// vector constructor. Initializes size to zero, mDataArray to nullptr, capacity to 8, and previousCapacity to 5
		/// </summary>
		Vector();

		/// <summary>
		/// destuctor. Destructs all data in the array, then frees memory
		/// </summary>
		~Vector();

		/// <summary>
		/// Copy Constructor that constructs a vector that is a deep copy of other
		/// </summary>
		/// <param name="other">vector passed through to copy</param>
		Vector(const Vector& other);

		/// <summary>
		/// Copy Assignment operator that makes a vector a deep copy of other
		/// </summary>
		/// <param name="other">vector passed through to copy</param>
		Vector& operator=(const Vector& other);

		/// <summary>
		/// Move constructor that moves the passed through vector into a new vector. Transfers all its data.
		/// </summary>
		/// <param name="other">vector to be moved into new vector. This vector after moved has no data in it</param>
		/// <returns>moved vector with the data</returns>

		Vector(Vector&& other) noexcept;
		/// <summary>
		/// Move cAssignment operator that moves the passed through vector into a new vector. Transfers all its data.
		/// </summary>
		/// <param name="other">vector to be moved into new vector. This vector after moved has no data in it</param>
		/// <returns>moved vector with the data</returns>
		Vector& operator=(Vector&& other) noexcept;

		/// <summary>
		/// Allows the user to create a vector using the initialzier list format
		/// </summary>
		/// <param name="list">takes in a list {0, 1, 2} and constructs a vector with that data</param>
		Vector(std::initializer_list<T> list);

		/// <summary>
		/// operator [] overload for the Vector class, allows array like access to the vector data
		/// </summary>
		/// <param name="index">the index is unsigned int, a size_t, that is the index of the array you want returned</param>
		/// <returns>the value at the index of the array</returns>
		T& operator[](size_t index);

		/// <summary>
		/// const version of operator[]
		/// </summary>
		/// <param name="index">see above</param>
		/// <returns>returns const version of above</returns>
		const T& operator[](size_t index) const;

		/// <summary>
		/// returns the value in the data array at index
		/// </summary>
		/// <param name="index">the index of the array you want returned</param>
		/// <returns>returns a T reference of the data of the array at index</returns>
		T& At(size_t index);

		/// <summary>
		/// Const version of At()
		/// </summary>
		/// <param name="index">see above</param>
		/// <returns>const version of the T reference</returns>
		const T& At(size_t index) const;

		/// <summary>
		/// removes the last item in the list, calls the destructor on the removed item. mSize--
		/// </summary>
		void PopBack();

		/// <summary>
		/// pushes the indicated data to the back of the vector. pushes it to mSize and mSize++
		/// </summary>
		/// <param name="data">the data you want at the back of the vector</param>
		void PushBack(const T& data);

		/// <summary>
		/// Reserves a specific amount of memory
		/// </summary>
		/// <param name="capacity">the amount of variable spaces you would like to reserve in the array</param>
		void Reserve(size_t capacity);

		/// <summary>
		/// clears the entire list. Destructs all data and size set to 0. Capacity stays the same
		/// </summary>
		void Clear();

		/// <summary>
		/// call on vector to see if there are any elements in it
		/// </summary>
		/// <returns>true if size = 0, false if size > 0</returns>
		const bool IsEmpty();

		/// <summary>
		/// call on vector to return the data at the front of the array
		/// </summary>
		/// <returns>at T reference that is the data at element 0 of the array.</returns>
		T& Front();

		/// <summary>
		/// const version of front
		/// </summary>
		/// <returns>const version of element 0</returns>
		const T& Front() const;

		/// <summary>
		/// call on vector to return the data at the back of the array
		/// </summary>
		/// <returns>the last elements data</returns>
		T& Back();

		/// <summary>
		/// const version of back
		/// </summary>
		/// <returns>const version of last elements data</returns>
		const T& Back() const;

		/// <summary>
		/// call on vector to get current size of the vector
		/// </summary>
		/// <returns>a size_t that is the current size of the vector. Is const, cant modify</returns>
		size_t Size() const;

		/// <summary>
		/// call on vector to get current capacity of the vector
		/// </summary>
		/// <returns>capacity of the vector. Const, cant modify</returns>
		size_t Capacity() const;

		/// <summary>
		/// Returns an iterator pointing to the index that contains the first instance of data
		/// </summary>
		/// <param name="data">the data you want to find in the vector</param>
		/// <param name="equalityFunctor">supply a custom functor for objects without an == operator</param>
		/// <returns>returns iterator with mOwner being the vector, and mIndex pointing the index that contains the first instance of data</returns>
		Iterator Find(const T& data, std::function<bool(const T&, const T&)> equalityFunctor = std::equal_to<T>());

		/// <summary>
		/// Returns an ConstIterator pointing to the index that contains the first instance of data
		/// </summary>
		/// <param name="data">the data you want to find in the vector</param>
		/// <param name="equalityFunctor">supply a custom functor for objects without an == operator</param>
		/// <returns>returns ConstIterator with mOwner being the vector, and mIndex pointing the index that contains the first instance of data</returns>
		ConstIterator Find(const T& data, std::function<bool(const T&, const T&)> equalityFunctor = std::equal_to<T>()) const;

		/// <summary>
		/// Finds the first instance of the data and removes it from the vector
		/// </summary>
		/// <param name="data">the data to be removed</param>
		/// <param name="equalityFunctor">supply a custom functor for objects without an == operator</param>
		void Remove(const T& data, std::function<bool(const T&, const T&)> equalityFunctor = std::equal_to<T>());

		void Remove(const Iterator& it, std::function<bool(const T&, const T&)> equalityFunctor = std::equal_to<T>());

		/// <summary>
		/// Remove any data between the first iterator and last from the vector. First is inclusive of that data, and last is exclusive
		/// </summary>
		/// <param name="first">the iterator pointing to the first index to be removed</param>
		/// <param name="last">the iterator pointing to index after the last index to be removed</param>
		/// <param name="equalityFunctor">supply a custom functor for objects without an == operator</param>
		void Remove(const Iterator& first, const Iterator& last, std::function<bool(const T&, const T&)> equalityFunctor = std::equal_to<T>());

		/// <summary>
		/// returns an iterator pointing to element 0 of the vector
		/// </summary>
		/// <returns>iterator pointing to element 0 of the vector</returns>
		Iterator begin();

		/// <summary>
		/// returns a ConstIterator pointing to element 0 of the vector
		/// </summary>
		/// <returns>ConstIterator pointing to element 0 of the vector</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Returns an Iterator pointing to the element after the last element in the vector
		/// </summary>
		/// <returns>Iterator pointing to the element after the last element in the vector</returns>
		Iterator end();

		/// <summary>
		/// Returns a ConstIterator pointing to the element after the last element in the vector
		/// </summary>
		/// <returns>ConstIterator pointing to the element after the last element in the vector</returns>
		ConstIterator end() const;

		/// <summary>
		/// returns a ConstIterator pointing to element 0 of the vector
		/// </summary>
		/// <returns>ConstIterator pointing to element 0 of the vector</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Returns a ConstIterator pointing to the element after the last element in the vector
		/// </summary>
		/// <returns>ConstIterator pointing to the element after the last element in the vector</returns>
		ConstIterator cend() const;

	private:

		T* mDataArray;
		size_t mCapacity;
		size_t mSize;
	};
}

#include "Vector.inl"
