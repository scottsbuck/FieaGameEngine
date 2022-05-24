#pragma once
#include "Scope.h"
#include "TypeRegistry.h"
#include <gsl/pointers>

namespace FieaGameEngine
{
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope);

	public:
		/// <summary>
		/// defauly destructor
		/// </summary>
		virtual ~Attributed() = default;

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">the attributed to be copied</param>
		Attributed(const Attributed& other);

		/// <summary>
		/// Copy assignment operator
		/// </summary>
		/// <param name="other">the attributed to be copied</param>
		/// <returns>a reference to the copied attributed</returns>
		Attributed& operator=(const Attributed& other);

		/// <summary>
		/// Move constructor
		/// </summary>
		/// <param name="other">the attributed to be moved</param>
		Attributed(Attributed&& other);

		/// <summary>
		/// Move assignment operator
		/// </summary>
		/// <param name="other">the attributed to be moved</param>
		/// <returns>a reference the attributed with others data</returns>
		Attributed& operator=(Attributed&& other);

		/// <summary>
		/// checks to see if a string is a member in the scopes hashmap. if it is it is an attribute
		/// </summary>
		/// <param name="string">the key to look for</param>
		/// <returns>a boolean indicating whether the key is an attribute or not</returns>
		bool IsAttribute(const std::string& string);

		/// <summary>
		/// Checks to see if the string is a prescribed attribute. Looks in the type registry of prescribed attributes for this class
		/// </summary>
		/// <param name="string">the key to look for</param>
		/// <returns>a boolean indicating whether the key is a prescribed attribute or not</returns>
		bool IsPrescribedAttribute(const std::string& string);

		/// <summary>
		/// Checks to see if the string is an auxiliary attribute. Checks to see if its an attribute and not a prescribed attribute
		/// </summary>
		/// <param name="string">the key to look for</param>
		/// <returns>a boolean indicating whether the key is a prescribed attribute or not</returns>
		bool IsAuxiliaryAttribute(const std::string& string);

		/// <summary>
		/// Appends an auxiliary attribute which is a local attribute to this object
		/// </summary>
		/// <param name="string">the attribute name to append</param>
		/// <returns>returns a datum reference associated with the key value pair for editing</returns>
		Datum& AppendAuxiliaryAttribute(const std::string& string);
		

	protected:
		gsl::owner<Attributed*> Clone() const override;
		Attributed(IdType idType);
		IdType mIdType;

	private:
		void Populate(IdType idType, bool isCopying = false);
	};
}
