#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>
#include <initializer_list>

namespace FieaGameEngine
{
	template <typename T>
	class SList
	{
	private:

		struct Node 
		{
			T data;
			Node* nextNode;

			Node(const T& Data, Node* NextNode);
		};

	public:

		class Iterator
		{

			friend SList;

		public:
			/// <summary>
			/// default constructor, initializes mNode and mOwner to nullptrs
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
			Iterator(Iterator&& other) = default;
			Iterator& operator=(Iterator&& other) = default;
			
			/// <summary>
			/// default destructor
			/// </summary>
			~Iterator() = default;

			/// <summary>
			/// comparison operator overload. checks the owner and node and compares those
			/// </summary>
			/// <param name="other">right hand value, left hand is the object the operator is being called on</param>
			/// <returns>if either owner or node arent the same return false, if both are the same return true</returns>
			bool operator==(const Iterator& other) const;

			/// <summary>
			/// calls inverse of the == operator
			/// </summary>
			/// <param name="other">look at == operator</param>
			/// <returns>inverse of == operator</returns>
			bool operator!=(const Iterator& other) const;

			/// <summary>
			/// Moves iterator to point to the next node
			/// </summary>
			/// <returns>returns the reference to the updated iterator</returns>
			Iterator& operator++();

			/// <summary>
			/// moves iterator to point to next node
			/// </summary>
			/// <returns>returns a copy of the non updated iterator</returns>
			Iterator operator++(int);

			/// <summary>
			/// dereference operator
			/// </summary>
			/// <returns>returns the data associated with the node the iterator points to</returns>
			T& operator*() const;

		private:
			Iterator(const SList& owner, Node* node = nullptr);
			Node* mNode{ nullptr };
			const SList* mOwner{ nullptr };
			
		};

		class ConstIterator
		{

			friend SList;

		public:
			/// <summary>
			/// default constructor. Initializes the ConstIterator mNode and mOwner to nullptrs
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// copy constructor
			/// </summary>
			/// <param name="other">takes in another ConstIterator and copies it</param>
			ConstIterator(const ConstIterator & other) = default;

			/// <summary>
			/// copy assignment operator
			/// </summary>
			/// <param name="other">takes in another ConstIterator and copies it</param>
			/// <returns>returns the ConstIterator copy</returns>
			ConstIterator& operator=(const ConstIterator & other) = default;
			ConstIterator(ConstIterator && other) = default;
			ConstIterator& operator=(ConstIterator && other) = default;

			~ConstIterator() = default;

			/// <summary>
			/// default destructor
			/// </summary>
			ConstIterator(const Iterator& other);

			/// <summary>
			/// comparison operator overload. checks the owner and node and compares those
			/// </summary>
			/// <param name="other">right hand value, left hand is the object the operator is being called on</param>
			/// <returns>if either owner or node arent the same return false, if both are the same return true</returns>
			bool operator==(const ConstIterator& other) const;

			/// <summary>
			/// calls inverse of the == operator
			/// </summary>
			/// <param name="other">look at == operator</param>
			/// <returns>inverse of == operator</returns>
			bool operator!=(const ConstIterator& other) const;

			/// <summary>
			/// Moves ConstIterator to point to the next node
			/// </summary>
			/// <returns>returns the reference to the updated ConstIterator</returns>
			ConstIterator& operator++();

			/// <summary>
			/// moves ConstIterator to point to next node
			/// </summary>
			/// <returns>returns a copy of the non updated ConstIterator</returns>
			ConstIterator operator++(int);

			/// <summary>
			/// dereference operator
			/// </summary>
			/// <returns>returns the data associated with the node the ConstIterator points to</returns>
			const T& operator*() const;

		private:
			ConstIterator(const SList& owner, Node* node = nullptr);
			Node* mNode{ nullptr };
			const SList* mOwner{ nullptr };
		};
		
		/// <summary>
		/// Default Constructor
		/// </summary>
		SList();

		/// <summary>
		/// Default Destructor
		/// </summary>
		~SList();

		/// <summary>
		/// Copy Constructor. Deep copies SList.
		/// </summary>
		/// <param name="other">SList to be deep copied</param>
		SList(const SList &other);

		/// <summary>
		/// Initializer list syntax function
		/// </summary>
		/// <param name="list">list in format {1, 2, 3} that allows you to intitialize the SList (or const SList) to those values in that order</param>
		SList(std::initializer_list<T> list);

		/// <summary>
		/// Assignment Operator. Deep copies SList.
		/// </summary>
		/// <param name="other">SList to be assigned and deep copied</param>
		/// <returns>Returns a reference to the deep copied SList</returns>
		SList& operator=(const SList& other);

		/// <summary>
		/// Creates Node and pushes it to the front of the SList
		/// </summary>
		/// <param name="data">Data to be inputted into the created node</param>
		Iterator PushFront(const T& data);

		/// <summary>
		/// Remove front node from Slist.
		/// </summary>
		void PopFront();

		/// <summary>
		/// Creates Node and pushes it to the back of the SList
		/// </summary>
		/// <param name="data">Data to be inputted into the created node</param>
		Iterator PushBack(const T& data);

		/// <summary>
		/// Removes the back node of the SList
		/// </summary>
		void PopBack();

		/// <summary>
		/// Checks if the SList is empty.
		/// </summary>
		/// <returns>returns true if empty, false if not</returns>
		bool IsEmpty() const;

		/// <summary>
		/// Returns the data of the front node of the SList
		/// </summary>
		/// <returns>reference to the data value</returns>
		const T& Front() const;

		/// <summary>
		/// Returns the data of the front node of the SList
		/// </summary>
		/// <returns>reference to the data value</returns>
		T& Front();

		/// <summary>
		/// Returns the data of the back node of the SList
		/// </summary>
		/// <returns>reference to the data value</returns>
		const T& Back() const;

		/// <summary>
		/// Returns the data of the back node of the SList
		/// </summary>
		/// <returns>reference to the data value</returns>
		T& Back();

		/// <summary>
		/// Completely clears the nodes out of the SList
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns a size_t of the current size of the list
		/// </summary>
		/// <returns>Size_t of the size of the list</returns>
		const std::size_t& Size() const;

		/// <summary>
		/// call on list to return an iterator that points to the beginning of the list
		/// </summary>
		/// <returns>an iterator that points to the beginning of the list</returns>
		Iterator begin();

		/// <summary>
		/// call on list to return an iterator that points to the item past the end of the list
		/// </summary>
		/// <returns>an iterator that points to the item past the end of the list or null</returns>
		Iterator end();

		/// <summary>
		/// same as begin but can be called on a const SList
		/// </summary>
		/// <returns>returns a ConstIterator if called on a const SList</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Same as end but can be called on a const SList
		/// </summary>
		/// <returns>returns a ConstIterator if called on a const SList</returns>
		ConstIterator end() const;

		/// <summary>
		/// explicit call on regular slist or const slist to return an Iterator that points to the beginning
		/// </summary>
		/// <returns>returns a constIterator regardless of list type</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// explicit call on regular slist or const slist to return and iterator that points to the end (or null)
		/// </summary>
		/// <returns>returns a constIterator regardless of list type</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Creates a node with the data and places it in the SList after the node indicated by the iterator
		/// </summary>
		/// <param name="data">data wanted to be inputted into the list</param>
		/// <param name="it">spot where the data should be inserted after</param>
		void InsertAfter(const T& data, const Iterator& it);

		/// <summary>
		/// Find and return the iterator indicated by the data. Will return first instance of the data in the list. will return an iterator = to end if data does not exist
		/// </summary>
		/// <param name="data">data to find</param>
		/// <param name="equalityFunctor">useful if the data type youre trying to find doesnt have an == operator overload</param>
		/// <returns>returns iterator pointing to the found data</returns>
		Iterator Find(const T& data, std::function<bool(const T&, const T&)> equalityFunctor = std::equal_to<T>());

		/// <summary>
		/// Find and return the ConstIterator indicated by the data. Will return first instance of the data in the const slist. will return a ConstIterator = to end if data does not exist
		/// </summary>
		/// <param name="data">data to find</param>
		/// <param name="equalityFunctor">useful if the data type youre trying to find doesnt have an == operator overload</param>
		/// <returns>returns ConstIterator pointing to the found data</returns>
		ConstIterator Find(const T& data, std::function<bool(const T&, const T&)> equalityFunctor = std::equal_to<T>()) const;

		/// <summary>
		/// Will remove the node from the list indicated by the data. Removes the first instance. Keeps list integrity
		/// </summary>
		/// <param name="data">data to be removed</param>
		/// <param name="equalityFunctor">useful if the data type youre trying to remove doesnt have an == operator overload</param>
		void Remove(const T& data, std::function<bool(const T&, const T&)> equalityFunctor = std::equal_to<T>());

		void Remove(const Iterator& it, std::function<bool(const T&, const T&)> equalityFunctor = std::equal_to<T>());

	private:

		std::size_t mSize;
		Node* mFrontNode;
		Node* mBackNode;
	};

}

#include "SList.inl"