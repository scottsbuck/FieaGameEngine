#pragma once
#include "Datum.h"
#include "HashMap.h"
#include "RTTI.h"
#include "Factory.h"
#include <exception>
#include <cassert>
#include <gsl/pointers>
#include <cstdlib>


namespace FieaGameEngine
{
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI)
	public:

		friend Datum;

		using VectorType = std::pair<std::string, Datum>*;

		/// <summary>
		/// Default Scope constructor
		/// </summary>
		/// <param name="capacity">Defaults to 11. Vector and hashmap capacity are defaulted to this value. Can take in a custom value</param>
		Scope(size_t capacity = 11);

		/// <summary>
		/// destructor
		/// </summary>
		virtual ~Scope();

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">scope to take in to copy. Makes a deep copy</param>
		Scope(const Scope& other);

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">scope to take in to copy. Makes a deep copy</param>
		/// <returns>the copied scope</returns>
		Scope& operator=(const Scope& other);

		/// <summary>
		/// Move constructor
		/// </summary>
		/// <param name="other">scope to be moved to new scope. Makes a shallow copy.</param>
		Scope(Scope&& other) noexcept;

		/// <summary>
		/// Move assignment operator
		/// </summary>
		/// <param name="other">scope to be moved to new scope. Makes a shallow copy</param>
		/// <returns>the moved scope</returns>
		Scope& operator=(Scope&& other) noexcept;

		/// <summary>
		/// Virtual constructor used for dynamic scope copying
		/// </summary>
		virtual gsl::owner<Scope*> Clone() const;

		/// <summary>
		/// Operator [] overload
		/// </summary>
		/// <param name="string">takes in a string value and wraps append</param>
		/// <returns>a reference to the datum created by append</returns>
		Datum& operator[](const std::string& string);

		/// <summary>
		/// Operator [] overload
		/// </summary>
		/// <param name="index">takes in an index</param>
		/// <returns>a reference to the datum at the index location in the ordered vector</returns>
		Datum& operator[](size_t index);
		/// <summary>
		/// Operator [] overload for const
		/// </summary>
		/// <param name="index">takes in an index</param>
		/// <returns>a reference to the datum at the index location in the ordered vector</returns>
		const Datum& operator[](size_t index) const;

		/// <summary>
		/// Override of the RTTI Equals function
		/// </summary>
		/// <param name="rhs">the scope passed in as an RTTI pointer</param>
		/// <returns>whether or not this is equal to rhs. Wraps the == operator</returns>
		bool Equals(const RTTI* rhs) const override;

		/// <summary>
		/// == comparator operator overload
		/// </summary>
		/// <param name="rhs">the passed in value to be compared to this</param>
		/// <returns>whether or not the scopes are equal</returns>
		bool operator==(const Scope& rhs) const;

		/// <summary>
		/// != comparator operator overload
		/// </summary>
		/// <param name="rhs">the passed in value to be compared to this</param>
		/// <returns>whether or not the scopes are not equal</returns>
		bool operator!=(const Scope& rhs) const;

		/// <summary>
		/// Clear function that clears the hashmap and vector and frees all memory allocated by the scope.
		/// </summary>
		void Clear();

		/// <summary>
		/// Finds the datum associated with the string passed in
		/// </summary>
		/// <param name="string">string key to search for</param>
		/// <returns>the datum associated with the string in the string datum pair</returns>
		Datum* Find(const std::string& string);

		/// <summary>
		/// Const Version of Find
		/// </summary>
		/// <param name="string"></param>
		/// <returns></returns>
		const Datum* Find(const std::string& string) const;

		/// <summary>
		/// Finds a scope contained within this scope
		/// </summary>
		/// <param name="scope">scope pointer to find</param>
		/// <returns>a pair containing the index of the datum at which the scope was found, and a pointer to the datum in which the scope was found</returns>
		std::pair<size_t, Datum*> FindContainedScope(const Scope* scope);

		/// <summary>
		/// Search up the hiearchy for the datum with the string as the key
		/// </summary>
		/// <param name="string">the key for the datum</param>
		/// <returns>the datum associated with the string in the string datum pair</returns>
		Datum* Search(const std::string& string);

		/// <summary>
		/// Search up the hiearchy for the datum with the string as the key and updates the scope *& to be the scope where the datum is stored
		/// </summary>
		/// <param name="string">the key for the datum</param>
		/// <param name="scope">Output parameter. Is the scope where the datum is located</param>
		/// <returns>the datum associated with the string in the string datum pair</returns>
		Datum* Search(const std::string& string, Scope*& scope);

		/// <summary>
		/// Search up the hiearchy for the datum with the string as the key
		/// </summary>
		/// <param name="string">the key for the datum</param>
		/// <returns>the datum associated with the string in the string datum pair</returns>
		const Datum* Search(const std::string& string) const;

		/// <summary>
		/// Search up the hiearchy for the datum with the string as the key and updates the scope *& to be the scope where the datum is stored
		/// </summary>
		/// <param name="string">the key for the datum</param>
		/// <param name="scope">Output parameter. Is the scope where the datum is located</param>
		/// <returns>the datum associated with the string in the string datum pair</returns>
		const Datum* Search(const std::string& string, const Scope*& scope) const;

		/// <summary>
		/// Appends a new datum to the scope with key of string
		/// </summary>
		/// <param name="string">the key of the new datum you are appending</param>
		/// <returns>A reference to the datum appended, or the datum that already exists at key string</returns>
		Datum& Append(const std::string& string);

		/// <summary>
		/// Appends a new datum of type scope to the string key. Adds a scope to the new table datum. If Datum of type Scope already exists, will just add another scope to the datum
		/// </summary>
		/// <param name="string">key for the datum pair</param>
		/// <returns>A reference to the scope just created</returns>
		Scope& AppendScope(const std::string& string);

		/// <summary>
		/// Adopts a scope into this scope at key string
		/// </summary>
		/// <param name="string">string key associated with either a new datum of type table, or an existing datum of type table</param>
		/// <param name="scope">the scope to be adopted</param>
		void Adopt(const std::string& string, Scope& scope);

		/// <summary>
		/// Checks if this is ancestor of scope
		/// </summary>
		/// <param name="scope">scope to see if this is ancestor of</param>
		/// <returns>whether or not this is ancestor of scope</returns>
		bool IsAncestorOf(const Scope& scope) const;

		/// <summary>
		/// Checks if this is descendant of scope
		/// </summary>
		/// <param name="scope">scope to see if this is descendant of</param>
		/// <returns>whether or not this is descendant of scope</returns>
		bool  IsDescendantOf(const Scope& scope) const;

		/// <summary>
		/// Gets the parent of this
		/// </summary>
		/// <returns>a const scope pointer which points to the scopes parent scope</returns>
		Scope* const GetParent() const;

		const size_t Size();

	protected:

		void Orphan(Scope& scope);

		HashMap<std::string, Datum> mHashmap;
		Vector<VectorType> mVector;
		Scope* mParentScope{ nullptr };
	};

	ConcreteFactory(Scope, Scope)
}
