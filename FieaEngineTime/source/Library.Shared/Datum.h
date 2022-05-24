#pragma once
#include <string>
#include <cstddef>
#include <glm\glm.hpp>
#include <cstdlib>
#include <cassert>
#include <stdexcept>
#include "RTTI.h"



namespace FieaGameEngine
{
	class Scope;

	class Datum final
	{
	public:		

		enum class DatumTypes
		{
			Unknown,
			Integer,
			Float,
			Vector,
			Matrix,
			String,
			Pointer,
			Table
		};

		/// <summary>
		/// Reserves memory
		/// </summary>
		/// <param name="capacity">amount of memory to reserve</param>
		void Reserve(std::size_t capacity);
		/// <summary>
		/// Default constructor
		/// </summary>
		/// <param name="datumType">defaulted to unknown if default declared, but can pass in a datum type param</param>
		Datum(DatumTypes datumType = DatumTypes::Unknown);
		/// <summary>
		/// Type cast constructor
		/// </summary>
		/// <param name="inputInteger">Integer to be pushbacked onto datum</param>
		Datum(std::int32_t inputInteger);
		/// <summary>
		/// Type cast constructor
		/// </summary>
		/// <param name="inputFloat">Float to be pushbacked onto datum</param>
		Datum(float inputFloat);
		/// <summary>
		/// Type cast constructor
		/// </summary>
		/// <param name="inputVector">Vector to be pushbacked onto datum</param>
		Datum(glm::vec4 inputVector);
		/// <summary>
		/// Type cast constructor
		/// </summary>
		/// <param name="inputMatrix">Matrix to be pushbacked onto datum</param>
		Datum(glm::mat4 inputMatrix);
		/// <summary>
		/// Type cast constructor
		/// </summary>
		/// <param name="inputString">String to be pushbacked onto datum</param>
		Datum(std::string inputString);
		/// <summary>
		/// Type cast constructor
		/// </summary>
		/// <param name="inputRttiPtr">RTTI Pointer to be pushbacked onto datum</param>
		Datum(RTTI* inputRttiPtr);

		Datum(Scope& inputScope);

		/// <summary>
		/// default destructor
		/// </summary>
		~Datum();

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="other">datum to be copied, copied differently depending on storage settings</param>
		Datum(const Datum& other);
		
		/// <summary>
		/// Copy assignment operator
		/// </summary>
		/// <param name="other">datum to be copied depends on storage settings of rhs datum</param>
		/// <returns>copied datum</returns>
		Datum& operator=(const Datum& other);
		/// <summary>
		/// single variable assignment operator
		/// </summary>
		/// <param name="other">integer to be pushed back onto the datum</param>
		/// <returns>datum with type set and integer in it</returns>
		Datum& operator=(std::int32_t other);
		/// <summary>
		/// single variable assignment operator
		/// </summary>
		/// <param name="other">integer to be pushed back onto the datum</param>
		/// <returns>datum with type set and float in it</returns>
		Datum& operator=(float other);
		/// <summary>
		/// single variable assignment operator
		/// </summary>
		/// <param name="other">integer to be pushed back onto the datum</param>
		/// <returns>datum with type set and vec4 in it</returns>
		Datum& operator=(glm::vec4 other);
		/// <summary>
		/// single variable assignment operator
		/// </summary>
		/// <param name="other">integer to be pushed back onto the datum</param>
		/// <returns>datum with type set and mat4 in it</returns>
		Datum& operator=(glm::mat4 other);
		/// <summary>
		/// single variable assignment operator
		/// </summary>
		/// <param name="other">integer to be pushed back onto the datum</param>
		/// <returns>datum with type set and string in it</returns>
		Datum& operator=(const std::string& other);
		/// <summary>
		/// single variable assignment operator
		/// </summary>
		/// <param name="other">integer to be pushed back onto the datum</param>
		/// <returns>datum with type set and rtti pointer in it</returns>
		Datum& operator=(RTTI* other);

		Datum& operator=(Scope& other);

		/// <summary>
		/// Move constructor
		/// </summary>
		/// <param name="other">datum to be moved</param>
		/// <returns>datum with others values</returns>
		Datum(Datum&& other) noexcept;
		/// <summary>
		/// Move constructor
		/// </summary>
		/// <param name="other">datum to be moved</param>
		/// <returns>datum with others values</returns>
		Datum& operator=(Datum&& other) noexcept;

		Scope& operator[](std::uint32_t index) { return *GetScope(index); };

		/// <summary>
		/// returns type of datum
		/// </summary>
		/// <returns>enum type of datum</returns>
		DatumTypes Type();
		/// <summary>
		/// Sets datum type
		/// </summary>
		/// <param name="typeName">typename to set datum to</param>
		void SetType(DatumTypes typeName);

		/// <summary>
		/// returns size of datum
		/// </summary>
		/// <returns>size of datum</returns>
		size_t Size() const;
		/// <summary>
		/// returns capacity of datum
		/// </summary>
		/// <returns>capacity of datum</returns>
		size_t Capacity() const;
		/// <summary>
		/// returns storage setting of datum
		/// </summary>
		/// <returns>storage setting of datum</returns>
		bool IsExternal() const;

		/// <summary>
		/// Resizes datum, can shrink or grow, initializes values to 0
		/// </summary>
		/// <param name="size">size to grow or shrink to</param>
		void Resize(size_t size);

		/// <summary>
		/// Clears datum, keeps capacity and type the same
		/// </summary>
		void Clear();

		/// <summary>
		/// Sets storage to external and initializes datum array with inputted array
		/// </summary>
		/// <param name="intArray">array to pass into for the datum to hold</param>
		/// <param name="size">size of the array</param>
		void SetStorage(int32_t* intArray, size_t size);
		/// <summary>
		/// Sets storage to external and initializes datum array with inputted array
		/// </summary>
		/// <param name="floatArray">array to pass into for the datum to hold</param>
		/// <param name="size">size of the array</param>
		void SetStorage(float* floatArray, size_t size);
		/// <summary>
		/// Sets storage to external and initializes datum array with inputted array
		/// </summary>
		/// <param name="vectorArray">array to pass into for the datum to hold</param>
		/// <param name="size">size of the array</param>
		void SetStorage(glm::vec4* vectorArray, size_t size);
		/// <summary>
		/// Sets storage to external and initializes datum array with inputted array
		/// </summary>
		/// <param name="matrixArray">array to pass into for the datum to hold</param>
		/// <param name="size">size of the array</param>
		void SetStorage(glm::mat4* matrixArray, size_t size);
		/// <summary>
		/// Sets storage to external and initializes datum array with inputted array
		/// </summary>
		/// <param name="stringArray">array to pass into for the datum to hold</param>
		/// <param name="size">size of the array</param>
		void SetStorage(std::string* stringArray, size_t size);
		/// <summary>
		/// Sets storage to external and initializes datum array with inputted array
		/// </summary>
		/// <param name="rttiPtrArray">array to pass into for the datum to hold</param>
		/// <param name="size">size of the array</param>
		void SetStorage(RTTI** rttiPtrArray, size_t size);

		void SetStorage(DatumTypes type, uint8_t* ptrArray, size_t size);

		/// <summary>
		/// Compares datum to other datums
		/// </summary>
		/// <param name="other">datum to compare</param>
		/// <returns>true if same, false if not</returns>
		bool operator==(const Datum& other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>true if same, false if not</returns>
		bool operator==(std::int32_t other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>true if same, false if not</returns>
		bool operator==(float other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>true if same, false if not</returns>
		bool operator==(glm::vec4 other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>true if same, false if not</returns>
		bool operator==(glm::mat4 other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>true if same, false if not</returns>
		bool operator==(std::string other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>true if same, false if not</returns>
		bool operator==(RTTI* other) const;

		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>false if same, true if not</returns>
		bool operator!=(const Datum& other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>false if same, true if not</returns>
		bool operator!=(std::int32_t other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>false if same, true if not</returns>
		bool operator!=(float other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>false if same, true if not</returns>
		bool operator!=(glm::vec4 other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>false if same, true if not</returns>
		bool operator!=(glm::mat4 other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>false if same, true if not</returns>
		bool operator!=(std::string other) const;
		/// <summary>
		/// Compares first value in datum to inputted value
		/// </summary>
		/// <param name="other">value to compare</param>
		/// <returns>false if same, true if not</returns>
		bool operator!=(RTTI* other) const;

		/// <summary>
		/// Sets a value in the datum at a specified index
		/// </summary>
		/// <param name="integer">value to set datum to</param>
		/// <param name="index">index to change</param>
		void Set(std::int32_t integer, size_t index = 0);
		/// <summary>
		/// Sets a value in the datum at a specified index
		/// </summary>
		/// <param name="inputFloat">value to set datum to</param>
		/// <param name="index">index to change</param>
		void Set(float inputFloat, size_t index = 0);
		/// <summary>
		/// Sets a value in the datum at a specified index
		/// </summary>
		/// <param name="vector">value to set datum to</param>
		/// <param name="index">index to change</param>
		void Set(glm::vec4 vector, size_t index = 0);
		/// <summary>
		/// Sets a value in the datum at a specified index
		/// </summary>
		/// <param name="matrix">value to set datum to</param>
		/// <param name="index">index to change</param>
		void Set(glm::mat4 matrix, size_t index = 0);
		/// <summary>
		/// Sets a value in the datum at a specified index
		/// </summary>
		/// <param name="string">value to set datum to</param>
		/// <param name="index">index to change</param>
		void Set(const std::string& string, size_t index = 0);
		/// <summary>
		/// Sets a value in the datum at a specified index
		/// </summary>
		/// <param name="rttiPtr">value to set datum to</param>
		/// <param name="index">index to change</param>
		void Set(RTTI* rttiPtr, size_t index = 0);

		void Set(Scope& scope, size_t index = 0);

		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		std::int32_t& GetInt(size_t index = 0);
		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		float& GetFloat(size_t index = 0);
		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		glm::vec4& GetVector(size_t index = 0);
		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		glm::mat4& GetMatrix(size_t index = 0);
		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		std::string& GetString(size_t index = 0);
		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		RTTI*& GetRTTI(size_t index = 0);

		Scope*& GetScope(size_t index = 0);

		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		const std::int32_t& GetInt(size_t index = 0) const;
		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		const float& GetFloat(size_t index = 0) const;
		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		const glm::vec4& GetVector(size_t index = 0) const;
		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		const glm::mat4& GetMatrix(size_t index = 0) const;
		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		const std::string& GetString(size_t index = 0) const;
		/// <summary>
		/// Returns a reference to the item at the index
		/// </summary>
		/// <param name="index">index to return item from</param>
		/// <returns>item at index</returns>
		RTTI* const& GetRTTI(size_t index = 0) const;

		Scope* const& GetScope(size_t index = 0) const;

		/// <summary>
		/// Sets the datum value from an inputted string
		/// </summary>
		/// <param name="string">string formatted in the way the datum requires</param>
		/// <param name="index">index to set at</param>
		void SetFromString(const std::string& string, size_t index = 0);

		void PushBackFromString(const std::string& string);

		/// <summary>
		/// returns the value at the index as a string
		/// </summary>
		/// <param name="index">to return item as string</param>
		/// <returns>a string that is the item at the index in the datum</returns>
		std::string ToString(size_t index = 0);

		/// <summary>
		/// Inserts value to the back of the datum
		/// </summary>
		/// <param name="integer">value to insert</param>
		void PushBack(std::int32_t integer);
		/// <summary>
		/// Inserts value to the back of the datum
		/// </summary>
		/// <param name="inputFloat">value to insert</param>
		void PushBack(float inputFloat);
		/// <summary>
		/// Inserts value to the back of the datum
		/// </summary>
		/// <param name="vector">value to insert</param>
		void PushBack(glm::vec4 vector);
		/// <summary>
		/// Inserts value to the back of the datum
		/// </summary>
		/// <param name="matrix">value to insert</param>
		void PushBack(glm::mat4 matrix);
		/// <summary>
		/// Inserts value to the back of the datum
		/// </summary>
		/// <param name="string">value to insert</param>
		void PushBack(const std::string& string);
		/// <summary>
		/// Inserts value to the back of the datum
		/// </summary>
		/// <param name="rttiPtr">value to insert</param>
		void PushBack(RTTI* rttiPtr);

		void PushBack(Scope& scope);

		/// <summary>
		/// Removes the last item in the datum
		/// </summary>
		void PopBack();

		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		std::int32_t& FrontInt();
		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		float& FrontFloat();
		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		glm::vec4& FrontVector();
		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		glm::mat4& FrontMatrix();
		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		std::string& FrontString();
		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		RTTI*& FrontRTTI();

		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		const std::int32_t& FrontInt() const;
		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		const float& FrontFloat() const;
		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		const glm::vec4& FrontVector() const;
		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		const glm::mat4& FrontMatrix() const;
		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		const std::string& FrontString() const;
		/// <summary>
		/// Returns the first value in the datum
		/// </summary>
		/// <returns>first value in the datum</returns>
		RTTI* const& FrontRTTI() const;

		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		std::int32_t& BackInt();
		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		float& BackFloat();
		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		glm::vec4& BackVector();
		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		glm::mat4& BackMatrix();
		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		std::string& BackString();
		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		RTTI*& BackRTTI();

		Scope*& BackScope();

		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		const std::int32_t& BackInt() const;
		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		const float& BackFloat() const;
		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		const glm::vec4& BackVector() const;
		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		const glm::mat4& BackMatrix() const;
		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		const std::string& BackString() const;
		/// <summary>
		/// Returns last value in the datum
		/// </summary>
		/// <returns>last value in the datum</returns>
		RTTI* const& BackRTTI() const;

		Scope* const& BackScope() const;

		/// <summary>
		/// Removes first instance of the inputted value
		/// </summary>
		/// <param name="integer">value to be removed</param>
		void Remove(std::int32_t integer);
		/// <summary>
		/// Removes first instance of the inputted value
		/// </summary>
		/// <param name="inputFloat">value to be removed</param>
		void Remove(float inputFloat);
		/// <summary>
		/// Removes first instance of the inputted value
		/// </summary>
		/// <param name="vector">value to be removed</param>
		void Remove(glm::vec4 vector);
		/// <summary>
		/// Removes first instance of the inputted value
		/// </summary>
		/// <param name="matrix">value to be removed</param>
		void Remove(glm::mat4 matrix);
		/// <summary>
		/// Removes first instance of the inputted value
		/// </summary>
		/// <param name="string">value to be removed</param>
		void Remove(const std::string& string);
		/// <summary>
		/// Removes first instance of the inputted value
		/// </summary>
		/// <param name="rttiPtr">value to be removed</param>
		void Remove(RTTI* rttiPtr);

		/// <summary>
		/// Removes item at specified index
		/// </summary>
		/// <param name="index">index for item to be removed at</param>
		void RemoveAt(size_t index);

		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="integer">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		std::pair<size_t, bool> Find(std::int32_t integer);
		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="inputFloat">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		std::pair<size_t, bool> Find(float inputFloat);
		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="vector">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		std::pair<size_t, bool> Find(glm::vec4 vector);
		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="matrix">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		std::pair<size_t, bool> Find(glm::mat4 matrix);
		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="string">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		std::pair<size_t, bool> Find(std::string string);
		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="rttiPtr">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		std::pair<size_t, bool> Find(RTTI* rttiPtr);

		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="integer">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		const std::pair<size_t, bool> Find(std::int32_t integer) const;
		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="inputFloat">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		const std::pair<size_t, bool> Find(float inputFloat) const;
		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="vector">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		const std::pair<size_t, bool> Find(glm::vec4 vector) const;
		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="matrix">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		const std::pair<size_t, bool> Find(glm::mat4 matrix) const;
		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="string">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		const std::pair<size_t, bool> Find(std::string string) const;
		/// <summary>
		/// Finds the first instance of the specified value
		/// </summary>
		/// <param name="rttiPtr">value to be found</param>
		/// <returns>the index and whether it was found or not</returns>
		const std::pair<size_t, bool> Find(RTTI* rttiPtr) const;

	private:

		union DatumValues
		{
			std::int32_t* i;
			float* f;
			glm::vec4* v;
			glm::mat4* m;
			std::string* s;
			RTTI** r;
			Scope** sc;
			void* vp{ nullptr };
		};

		DatumValues mDataArray{ nullptr };
		DatumTypes mType{ DatumTypes::Unknown };
		static const std::size_t DatumTypeSizes[static_cast<std::size_t>(DatumTypes::Table) + 1];
		bool mIsExternal{ false };
		std::size_t mCapacity{ 0 };
		std::size_t mSize{ 0 };
	};
}


