#include "pch.h"
#include "Datum.h"
#include "Scope.h"

namespace FieaGameEngine
{
	const std::size_t Datum::DatumTypeSizes[] =
	{
		0,
		sizeof(std::int32_t),
		sizeof(float),
		sizeof(glm::vec4),
		sizeof(glm::mat4),
		sizeof(std::string),
		sizeof(RTTI*),
		sizeof(Scope*)
	};

	void Datum::Reserve(std::size_t capacity)
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Data is External, cannot reserve");
		}
		if (capacity > mCapacity)
		{
			std::size_t size = DatumTypeSizes[static_cast<std::size_t>(mType)];
			assert(size != 0);
			void* data = realloc(mDataArray.vp, capacity * size);
			assert(data != nullptr);
			mDataArray.vp = data;
			mCapacity = capacity;
		}
	}

	Datum::Datum(DatumTypes datumType) :
		mType(datumType)
	{
		
	}

	Datum::Datum(std::int32_t inputInteger)
	{
		PushBack(inputInteger);
	}

	Datum::Datum(float inputFloat)
	{
		PushBack(inputFloat);
	}

	Datum::Datum(glm::vec4 inputVector)
	{
		PushBack(inputVector);
	}

	Datum::Datum(glm::mat4 inputMatrix)
	{
		PushBack(inputMatrix);
	}

	Datum::Datum(std::string inputString)
	{
		PushBack(inputString);
	}

	Datum::Datum(RTTI* inputRttiPtr)
	{
		PushBack(inputRttiPtr);
	}

	Datum::Datum(Scope& inputScope)
	{
		PushBack(inputScope);
	}

	Datum::~Datum()
	{
		if (!mIsExternal)
		{
			Clear();
			free(mDataArray.vp);
		}
	}

	Datum::Datum(const Datum& other)
	{
		mType = other.mType;
		if (other.mIsExternal)
		{
			mDataArray.vp = other.mDataArray.vp;
		}
		else
		{
			Reserve(other.mCapacity);
			if (other.mType == DatumTypes::String)
			{
				for (size_t i = 0; i < other.mSize; i++)
				{
					new (mDataArray.s + i) std::string(other.mDataArray.s[i]);
				}
			}
			else
			{
				memcpy_s(mDataArray.vp, other.mSize * DatumTypeSizes[static_cast<std::size_t>(mType)], other.mDataArray.vp, other.mSize * DatumTypeSizes[static_cast<std::size_t>(mType)]);
			}
		}
		mSize = other.mSize;
		mCapacity = other.mCapacity;
		mIsExternal = other.mIsExternal;
	}

	Datum& Datum::operator=(const Datum& other)
	{
		if (this != &other)
		{
			mType = other.mType;
			if (!mIsExternal)
			{
				Clear();
				free(mDataArray.vp);
			}
			if (other.mIsExternal)
			{
				mDataArray.vp = other.mDataArray.vp;
			}
			else
			{
				if (mIsExternal)
				{
					mDataArray.vp = nullptr;
					mIsExternal = false;
					mSize = 0;
					mCapacity = 0;
				}
				Reserve(other.mCapacity);
				if (other.mType == DatumTypes::String)
				{
					for (size_t i = 0; i < other.mSize; i++)
					{
						new (mDataArray.s + i) std::string(other.mDataArray.s[i]);
					}
				}
				else
				{
					memcpy_s(mDataArray.vp, other.mSize * DatumTypeSizes[static_cast<std::size_t>(mType)], other.mDataArray.vp, other.mSize * DatumTypeSizes[static_cast<std::size_t>(mType)]);
				}
			}
			mSize = other.mSize;
			mCapacity = other.mCapacity;
			mIsExternal = other.mIsExternal;
		}

		return *this;
	}

	Datum& Datum::operator=(std::int32_t other)
	{
		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other);
		}
		return *this;
	}

	Datum& Datum::operator=(float other)
	{
		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other);
		}
		return *this;
	}

	Datum& Datum::operator=(glm::vec4 other)
	{
		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other);
		}
		return *this;
	}

	Datum& Datum::operator=(glm::mat4 other)
	{
		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other);
		}
		return *this;
	}

	Datum& Datum::operator=(const std::string& other)
	{
		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other);
		}
		return *this;
	}

	Datum& Datum::operator=(RTTI* other)
	{
		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other);
		}
		return *this;
	}

	Datum& Datum::operator=(Scope& other)
	{
		if (mSize == 0)
		{
			PushBack(other);
		}
		else
		{
			Set(other);
		}
		return *this;
	}

	Datum::Datum(Datum&& other) noexcept :
		mDataArray(other.mDataArray), mType(other.mType), mCapacity(other.mCapacity), mSize(other.mSize), mIsExternal(other.mIsExternal)
	{
		other.mDataArray.vp = nullptr;
		other.mType = DatumTypes::Unknown;
		other.mCapacity = 0;
		other.mSize = 0;
		other.mIsExternal = false;
	}

	Datum& Datum::operator=(Datum&& other) noexcept
	{
		if (this != &other)
		{
			if (!mIsExternal)
			{
				Clear();
				free(mDataArray.vp);
			}

			mDataArray = other.mDataArray;
			mType = other.mType;
			mCapacity = other.mCapacity;
			mSize = other.mSize;
			mIsExternal = other.mIsExternal;


			other.mDataArray.vp = nullptr;
			other.mType = DatumTypes::Unknown;
			other.mCapacity = 0;
			other.mSize = 0;
			other.mIsExternal = false;
		}

		return *this;
	}

	Datum::DatumTypes Datum::Type()
	{
		return mType;
	}

	void Datum::SetType(DatumTypes typeName)
	{
		if (mSize > 0)
		{
			throw std::runtime_error("This datum already has memory allocated, cannot change type");
		}
		mType = typeName;
	}

	size_t Datum::Size() const
	{
		return mSize;
	}

	size_t Datum::Capacity() const
	{
		return mCapacity;
	}

	bool Datum::IsExternal() const
	{
		return mIsExternal;
	}

	void Datum::Resize(size_t size)
	{
		if (mType == DatumTypes::Unknown)
		{
			throw std::runtime_error("Type is Unknown, Datum must have type to Resize");
		}
		if (mIsExternal)
		{
			throw std::runtime_error("Data is external, cannot resize");
		}
		if (size > mSize)
		{
			Reserve(size);
			if (mType == DatumTypes::String)
			{
				for (size_t i = mSize; i < size; i++)
				{
					new (mDataArray.s + i) std::string("");
				}
			}
			else
			{
				int8_t* buffer = static_cast<int8_t*>(mDataArray.vp);
				memset(buffer + mSize * DatumTypeSizes[static_cast<std::size_t>(mType)], 0, (size-mSize) * DatumTypeSizes[static_cast<std::size_t>(mType)]);
			}
			mSize = size;
		}
		else if (size < mSize)
		{
			if (mType == DatumTypes::String)
			{
				using namespace std;
				for (size_t i = mSize - 1; i >= size; i--)
				{
					mDataArray.s[i].~string();
				}
			}
			mDataArray.vp = realloc(mDataArray.vp, size * DatumTypeSizes[static_cast<std::size_t>(mType)]);
			mCapacity = size;
			mSize = size;
		}
	}

	void Datum::Clear()
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Data is external, cannot clear");
		}
		if (mType == DatumTypes::String)
		{
			using namespace std;
			for (size_t i = 0; i < mSize; i++)
			{
				mDataArray.s[i].~string();
			}
		}
		mSize = 0;
	}

	void Datum::SetStorage(int32_t* intArray, size_t size)
	{
		if (mSize > 0)
		{
			throw std::runtime_error("This Datum has memory allocated, cannot set storage");
		}
		mType = DatumTypes::Integer;
		mDataArray.i = intArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(float* floatArray, size_t size)
	{
		if (mSize > 0)
		{
			throw std::runtime_error("This Datum has memory allocated, cannot set storage");
		}
		mType = DatumTypes::Float;
		mDataArray.f = floatArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(glm::vec4* vectorArray, size_t size)
	{
		if (mSize > 0)
		{
			throw std::runtime_error("This Datum has memory allocated, cannot set storage");
		}
		mType = DatumTypes::Vector;
		mDataArray.v = vectorArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(glm::mat4* matrixArray, size_t size)
	{
		if (mSize > 0)
		{
			throw std::runtime_error("This Datum has memory allocated, cannot set storage");
		}
		mType = DatumTypes::Matrix;
		mDataArray.m = matrixArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(std::string* stringArray, size_t size)
	{
		if (mSize > 0)
		{
			throw std::runtime_error("This Datum has memory allocated, cannot set storage");
		}
		mType = DatumTypes::String;
		mDataArray.s = stringArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(RTTI** rttiPtrArray, size_t size)
	{
		if (mSize > 0)
		{
			throw std::runtime_error("This Datum has memory allocated, cannot set storage");
		}
		mType = DatumTypes::Pointer;
		mDataArray.r = rttiPtrArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	void Datum::SetStorage(DatumTypes type, uint8_t* ptrArray, size_t size)
	{
		if (!mIsExternal && mSize > 0)
		{
			throw std::runtime_error("This Datum has memory allocated, cannot set storage");
		}
		mType = type;
		mDataArray.vp = ptrArray;
		mSize = size;
		mCapacity = size;
		mIsExternal = true;
	}

	bool Datum::operator==(const Datum& other) const
	{
		return !operator!=(other);
	}

	bool Datum::operator==(std::int32_t other) const
	{
		return !operator!=(other);
	}

	bool Datum::operator==(float other) const
	{
		return !operator!=(other);
	}

	bool Datum::operator==(glm::vec4 other) const
	{
		return !operator!=(other);
	}

	bool Datum::operator==(glm::mat4 other) const
	{
		return !operator!=(other);
	}

	bool Datum::operator==(std::string other) const
	{
		return !operator!=(other);
	}

	bool Datum::operator==(RTTI* other) const
	{
		return !operator!=(other);
	}

	bool Datum::operator!=(const Datum& other) const
	{
		if ((mType == other.mType) && (mSize == other.mSize) && (mIsExternal == other.mIsExternal))
		{
			if (mType == DatumTypes::String)
			{
				for (size_t i = 0; i < mSize; i++)
				{
					if (mDataArray.s[i] != other.mDataArray.s[i])
					{
						return true;
					}
				}
			}
			else if (mType == DatumTypes::Pointer || mType == DatumTypes::Table)
			{
				for (size_t i = 0; i < mSize; i++)
				{
					if (!mDataArray.r[i]->Equals(other.mDataArray.r[i]))
					{
						return true;
					}
				}
			}
			else
			{
				if (memcmp(mDataArray.vp, other.mDataArray.vp, mSize * DatumTypeSizes[static_cast<std::size_t>(mType)]) != 0)
				{
					return true;
				}
			}
		}
		else
		{
			return true;
		}
		return false;
	}

	bool Datum::operator!=(std::int32_t other) const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("No value to compare in datum");
		}
		if (mType != DatumTypes::Integer)
		{
			throw std::runtime_error("Cannot compare an integer to a non integer datum");
		}
		return mDataArray.i[0] != other;
	}

	bool Datum::operator!=(float other) const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("No value to compare in datum");
		}
		if (mType != DatumTypes::Float)
		{
			throw std::runtime_error("Cannot compare a float to a non float datum");
		}
		return mDataArray.f[0] != other;
	}

	bool Datum::operator!=(glm::vec4 other) const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("No value to compare in datum");
		}
		if (mType != DatumTypes::Vector)
		{
			throw std::runtime_error("Cannot compare a vector to a non vector datum");
		}
		return mDataArray.v[0] != other;
	}

	bool Datum::operator!=(glm::mat4 other) const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("No value to compare in datum");
		}
		if (mType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Cannot compare a matrix to a non matrix datum");
		}
		return mDataArray.m[0] != other;
	}

	bool Datum::operator!=(std::string other) const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("No value to compare in datum");
		}
		if (mType != DatumTypes::String)
		{
			throw std::runtime_error("Cannot compare a string to a non string datum");
		}
		return mDataArray.s[0] != other;
	}

	bool Datum::operator!=(RTTI* other) const
	{
		if (mSize == 0)
		{
			throw std::runtime_error("No value to compare in datum");
		}
		if (mType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot compare a RTTI* to a non RTTI* datum");
		}
		return !mDataArray.r[0]->Equals(other);
	}

	void Datum::Set(std::int32_t integer, size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		mDataArray.i[index] = integer;
	}

	void Datum::Set(float inputFloat, size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Float)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		mDataArray.f[index] = inputFloat;
	}

	void Datum::Set(glm::mat4 matrix, size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		mDataArray.m[index] = matrix;
	}

	void Datum::Set(glm::vec4 vector, size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		mDataArray.v[index] = vector;
	}

	void Datum::Set(const std::string& string, size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::String)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		mDataArray.s[index] = string;
	}

	void Datum::Set(RTTI* rttiPtr, size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		mDataArray.r[index] = rttiPtr;
	}

	void Datum::Set(Scope& scope, size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Table)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		mDataArray.sc[index] = &scope;
	}

	std::int32_t& Datum::GetInt(size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.i[index];
	}

	float& Datum::GetFloat(size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Float)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.f[index];
	}

	glm::vec4& Datum::GetVector(size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.v[index];
	}

	glm::mat4& Datum::GetMatrix(size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.m[index];
	}

	std::string& Datum::GetString(size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::String)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.s[index];
	}

	RTTI*& Datum::GetRTTI(size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.r[index];
	}

	Scope*& Datum::GetScope(size_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Table)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.sc[index];
	}

	const std::int32_t& Datum::GetInt(size_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.i[index];
	}

	const float& Datum::GetFloat(size_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Float)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.f[index];
	}

	const glm::vec4& Datum::GetVector(size_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.v[index];
	}

	const glm::mat4& Datum::GetMatrix(size_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.m[index];
	}

	const std::string& Datum::GetString(size_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::String)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.s[index];
	}

	RTTI* const& Datum::GetRTTI(size_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.r[index];
	}

	Scope* const& Datum::GetScope(size_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType != DatumTypes::Table)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		return mDataArray.sc[index];
	}

	void Datum::SetFromString(const std::string& string, size_t index)
	{
		switch (mType)
		{
		case Datum::DatumTypes::Unknown:
		{
			throw std::runtime_error("Type is Unknown, Datum must have type to SetFromString");
		}
			break;
		case Datum::DatumTypes::Integer:
		{
			int32_t inputInt;
			sscanf_s(string.c_str(), "%d", &inputInt);
			Set(inputInt, index);
		}
			break;
		case Datum::DatumTypes::Float:
		{
			float inputFloat;
			sscanf_s(string.c_str(), "%f", &inputFloat);
			Set(inputFloat, index);
		}
			break;
		case Datum::DatumTypes::Vector:
		{
			glm::vec4 vector;
			sscanf_s(string.c_str(), "vec4(%f, %f, %f, %f)", &vector[0], &vector[1], &vector[2], &vector[3]);
			Set(vector, index);
		}
			break;
		case Datum::DatumTypes::Matrix:
		{
			glm::mat4 matrix;
			sscanf_s(string.c_str(), "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", 
				&matrix[0][0], &matrix[1][0], &matrix[2][0], &matrix[3][0],
				&matrix[0][1], &matrix[1][1], &matrix[2][1], &matrix[3][1],
				&matrix[0][2], &matrix[1][2], &matrix[2][2], &matrix[3][2],
				&matrix[0][3], &matrix[1][3], &matrix[2][3], &matrix[3][3]);
			Set(matrix, index);
		}
			break;
		case Datum::DatumTypes::String:
		{
			Set(string, index);
		}
			break;
		}
	}

	void Datum::PushBackFromString(const std::string& string)
	{
		switch (mType)
		{
		case Datum::DatumTypes::Unknown:
		{
			throw std::runtime_error("Type is Unknown, Datum must have type to SetFromString");
		}
		break;
		case Datum::DatumTypes::Integer:
		{
			int32_t inputInt;
			sscanf_s(string.c_str(), "%d", &inputInt);
			PushBack(inputInt);
		}
		break;
		case Datum::DatumTypes::Float:
		{
			float inputFloat;
			sscanf_s(string.c_str(), "%f", &inputFloat);
			PushBack(inputFloat);
		}
		break;
		case Datum::DatumTypes::Vector:
		{
			glm::vec4 vector;
			sscanf_s(string.c_str(), "vec4(%f, %f, %f, %f)", &vector[0], &vector[1], &vector[2], &vector[3]);
			PushBack(vector);
		}
		break;
		case Datum::DatumTypes::Matrix:
		{
			glm::mat4 matrix;
			sscanf_s(string.c_str(), "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
				&matrix[0][0], &matrix[1][0], &matrix[2][0], &matrix[3][0],
				&matrix[0][1], &matrix[1][1], &matrix[2][1], &matrix[3][1],
				&matrix[0][2], &matrix[1][2], &matrix[2][2], &matrix[3][2],
				&matrix[0][3], &matrix[1][3], &matrix[2][3], &matrix[3][3]);
			PushBack(matrix);
		}
		break;
		case Datum::DatumTypes::String:
		{
			PushBack(string);
		}
		break;
		}
	}

	std::string Datum::ToString(size_t index)
	{
		switch (mType)
		{
		case Datum::DatumTypes::Unknown:
		{
			throw std::runtime_error("Type is Unknown, Datum must have type to call ToString");
		}
		break;
		case Datum::DatumTypes::Integer:
		{
			return std::to_string(GetInt(index));
		}
		break;
		case Datum::DatumTypes::Float:
		{
			return std::to_string(GetFloat(index));
		}
		break;
		case Datum::DatumTypes::Vector:
		{
			glm::vec4 vector = GetVector(index);
			return (std::to_string(vector.x) + " " + std::to_string(vector.y) + " " + std::to_string(vector.z) + " " + std::to_string(vector.w));
		}
		break;
		case Datum::DatumTypes::Matrix:
		{
			glm::mat4 matrix = GetMatrix(index);
			std::string buffer;
			for (std::int32_t i = 0; i < 4; i++)
			{
				for (std::int32_t j = 0; j < 4; j++)
				{
					buffer += std::to_string(matrix[i][j]);
					if (i == 3 && j == 3)
					{
						break;
					}
					buffer += " ";
				}
			}
			return buffer;
		}
		break;
		case Datum::DatumTypes::String:
		{
			return GetString(index);
		}
		break;
		}
		throw std::runtime_error("Something is broken beyond repair");
	}

	void Datum::PushBack(std::int32_t integer)
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Data is External, cannot pushback");
		}
		if (mType == DatumTypes::Unknown && mSize == 0)
		{
			SetType(DatumTypes::Integer);
		}
		if (mType != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == mCapacity)
		{
			if (mCapacity == 0)
			{
				Reserve(1);
			}
			else
			{
				Reserve(2 * mCapacity);
			}
		}
		mDataArray.i[mSize] = integer;
		mSize++;
	}

	void Datum::PushBack(float inputFloat)
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Data is External, cannot pushback");
		}
		if (mType == DatumTypes::Unknown && mSize == 0)
		{
			SetType(DatumTypes::Float);
		}
		if (mType != DatumTypes::Float)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == mCapacity)
		{
			if (mCapacity == 0)
			{
				Reserve(1);
			}
			else
			{
				Reserve(2 * mCapacity);
			}
		}
		mDataArray.f[mSize] = inputFloat;
		mSize++;
	}

	void Datum::PushBack(glm::vec4 vector)
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Data is External, cannot pushback");
		}
		if (mType == DatumTypes::Unknown && mSize == 0)
		{
			SetType(DatumTypes::Vector);
		}
		if (mType != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == mCapacity)
		{
			if (mCapacity == 0)
			{
				Reserve(1);
			}
			else
			{
				Reserve(2 * mCapacity);
			}
		}
		mDataArray.v[mSize] = vector;
		mSize++;
	}

	void Datum::PushBack(glm::mat4 matrix)
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Data is External, cannot pushback");
		}
		if (mType == DatumTypes::Unknown && mSize == 0)
		{
			SetType(DatumTypes::Matrix);
		}
		if (mType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == mCapacity)
		{
			if (mCapacity == 0)
			{
				Reserve(1);
			}
			else
			{
				Reserve(2 * mCapacity);
			}
		}
		mDataArray.m[mSize] = matrix;
		mSize++;
	}

	void Datum::PushBack(const std::string& string)
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Data is External, cannot pushback");
		}
		if (mType == DatumTypes::Unknown && mSize == 0)
		{
			SetType(DatumTypes::String);
		}
		if (mType != DatumTypes::String)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == mCapacity)
		{
			if (mCapacity == 0)
			{
				Reserve(1);
			}
			else
			{
				Reserve(2 * mCapacity);
			}
		}
		new (mDataArray.s + mSize) std::string(string);
		mSize++;
	}

	void Datum::PushBack(RTTI* rttiPtr)
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Data is External, cannot pushback");
		}
		if (mType == DatumTypes::Unknown && mSize == 0)
		{
			SetType(DatumTypes::Pointer);
		}
		if (mType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == mCapacity)
		{
			if (mCapacity == 0)
			{
				Reserve(1);
			}
			else
			{
				Reserve(2 * mCapacity);
			}
		}
		mDataArray.r[mSize] = rttiPtr;
		mSize++;
	}

	void Datum::PushBack(Scope& scope)
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Data is External, cannot pushback");
		}
		if (mType == DatumTypes::Unknown && mSize == 0)
		{
			SetType(DatumTypes::Table);
		}
		if (mType != DatumTypes::Table)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == mCapacity)
		{
			if (mCapacity == 0)
			{
				Reserve(1);
			}
			else
			{
				Reserve(2 * mCapacity);
			}
		}
		mDataArray.sc[mSize] = &scope;
		mSize++;
	}

	void Datum::PopBack()
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Data is External, cannot popback");
		}
		if (mType == DatumTypes::String)
		{
			using namespace std;
			if (mSize > 0)
			{
				mDataArray.s[mSize - 1].~string();
				mSize--;
			}
		}
		else
		{
			if (mSize > 0)
			{
				mSize--;
			}
		}
	}

	std::int32_t& Datum::FrontInt()
	{
		if (mType != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.i[0];
	}

	float& Datum::FrontFloat()
	{
		if (mType != DatumTypes::Float)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.f[0];
	}

	glm::vec4& Datum::FrontVector()
	{
		if (mType != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.v[0];
	}

	glm::mat4& Datum::FrontMatrix()
	{
		if (mType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.m[0];
	}

	std::string& Datum::FrontString()
	{
		if (mType != DatumTypes::String)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.s[0];
	}

	RTTI*& Datum::FrontRTTI()
	{
		if (mType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.r[0];
	}

	const std::int32_t& Datum::FrontInt() const
	{
		if (mType != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.i[0];
	}

	const float& Datum::FrontFloat() const
	{
		if (mType != DatumTypes::Float)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.f[0];
	}

	const glm::vec4& Datum::FrontVector() const
	{
		if (mType != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.v[0];
	}

	const glm::mat4& Datum::FrontMatrix() const
	{
		if (mType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.m[0];
	}

	const std::string& Datum::FrontString() const
	{
		if (mType != DatumTypes::String)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.s[0];
	}

	RTTI* const& Datum::FrontRTTI() const
	{
		if (mType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces front of empty list");
		}
		return mDataArray.r[0];
	}

	std::int32_t& Datum::BackInt()
	{
		if (mType != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.i[mSize - 1];
	}

	float& Datum::BackFloat()
	{
		if (mType != DatumTypes::Float)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.f[mSize - 1];
	}

	glm::vec4& Datum::BackVector()
	{
		if (mType != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.v[mSize - 1];
	}

	glm::mat4& Datum::BackMatrix()
	{
		if (mType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.m[mSize - 1];
	}

	std::string& Datum::BackString()
	{
		if (mType != DatumTypes::String)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.s[mSize - 1];
	}

	RTTI*& Datum::BackRTTI()
	{
		if (mType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.r[mSize - 1];
	}

	Scope*& Datum::BackScope()
	{
		if (mType != DatumTypes::Table)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.sc[mSize - 1];
	}

	const std::int32_t& Datum::BackInt() const
	{
		if (mType != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.i[mSize - 1];
	}

	const float& Datum::BackFloat() const
	{
		if (mType != DatumTypes::Float)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.f[mSize - 1];
	}

	const glm::vec4& Datum::BackVector() const
	{
		if (mType != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.v[mSize - 1];
	}

	const glm::mat4& Datum::BackMatrix() const
	{
		if (mType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.m[mSize - 1];
	}

	const std::string& Datum::BackString() const
	{
		if (mType != DatumTypes::String)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.s[mSize - 1];
	}

	RTTI* const& Datum::BackRTTI() const
	{
		if (mType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.r[mSize - 1];
	}

	Scope* const& Datum::BackScope() const
	{
		if (mType != DatumTypes::Table)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		if (mSize == 0)
		{
			throw std::runtime_error("Can't acces back of empty list");
		}
		return mDataArray.sc[mSize - 1];
	}

	void Datum::Remove(std::int32_t integer)
	{
		RemoveAt(Find(integer).first);
	}

	void Datum::Remove(float inputFloat)
	{
		RemoveAt(Find(inputFloat).first);
	}

	void Datum::Remove(glm::vec4 vector)
	{
		RemoveAt(Find(vector).first);
	}

	void Datum::Remove(glm::mat4 matrix)
	{
		RemoveAt(Find(matrix).first);
	}

	void Datum::Remove(const std::string& string)
	{
		RemoveAt(Find(string).first);
	}

	void Datum::Remove(RTTI* rttiPtr)
	{
		RemoveAt(Find(rttiPtr).first);
	}

	void Datum::RemoveAt(size_t index)
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Data is External, cannot remove");
		}
		if (mType == DatumTypes::Unknown)
		{
			throw std::runtime_error("Datum Type is Unknown");
		}
		if (index >= mSize)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (mType == DatumTypes::String)
		{
			using namespace std;
			mDataArray.s[index].~string();
		}
		if (mType == DatumTypes::Table)
		{
			mDataArray.sc[index]->mParentScope = nullptr;
		}

		int8_t* buffer = static_cast<int8_t*>(mDataArray.vp);
		memmove_s(buffer+(index * DatumTypeSizes[static_cast<size_t>(mType)]), (mSize - index - 1) * DatumTypeSizes[static_cast<size_t>(mType)], buffer+(index + 1 * DatumTypeSizes[static_cast<size_t>(mType)]), (mSize-index-1) * DatumTypeSizes[static_cast<size_t>(mType)]);
		mSize--;
	}

	std::pair<size_t, bool> Datum::Find(std::int32_t integer)
	{
		if (mType != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.i[i] == integer)
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}

	std::pair<size_t, bool> Datum::Find(float inputFloat)
	{
		if (mType != DatumTypes::Float)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.f[i] == inputFloat)
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}

	std::pair<size_t, bool> Datum::Find(glm::vec4 vector)
	{
		if (mType != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.v[i] == vector)
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}

	std::pair<size_t, bool> Datum::Find(glm::mat4 matrix)
	{
		if (mType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.m[i] == matrix)
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}

	std::pair<size_t, bool> Datum::Find(std::string string)
	{
		if (mType != DatumTypes::String)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.s[i] == string)
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}

	std::pair<size_t, bool> Datum::Find(RTTI* rttiPtr)
	{
		if (mType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.r[i]->Equals(rttiPtr))
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}

	const std::pair<size_t, bool> Datum::Find(std::int32_t integer) const
	{
		if (mType != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.i[i] == integer)
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}

	const std::pair<size_t, bool> Datum::Find(float inputFloat) const
	{
		if (mType != DatumTypes::Float)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.f[i] == inputFloat)
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}

	const std::pair<size_t, bool> Datum::Find(glm::vec4 vector) const
	{
		if (mType != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.v[i] == vector)
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}

	const std::pair<size_t, bool> Datum::Find(glm::mat4 matrix) const
	{
		if (mType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.m[i] == matrix)
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}

	const std::pair<size_t, bool> Datum::Find(std::string string) const
	{
		if (mType != DatumTypes::String)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.s[i] == string)
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}

	const std::pair<size_t, bool> Datum::Find(RTTI* rttiPtr) const
	{
		if (mType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum Type does not match type of function");
		}
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDataArray.r[i]->Equals(rttiPtr))
			{
				return std::make_pair(i, true);
			}
		}
		return std::make_pair(mSize, false);
	}
}

