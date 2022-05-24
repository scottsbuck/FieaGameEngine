#include "pch.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "IJsonParseHelper.h"
#include "JsonParseCoordinator.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(JsonParseCoordinator::SharedData)

	void JsonParseCoordinator::SharedData::Initialize()
	{
		mDepth = 0;
	}

	void JsonParseCoordinator::SharedData::CleanUp()
	{

	}

	JsonParseCoordinator* JsonParseCoordinator::SharedData::GetJsonParseCoordinator()
	{
		return mParseCoordinator;
	}
	void JsonParseCoordinator::SharedData::IncrementDepth()
	{
		mDepth++;
	}

	void JsonParseCoordinator::SharedData::DecrementDepth()
	{
		mDepth--;
	}

	size_t JsonParseCoordinator::SharedData::Depth()
	{
		return mDepth;
	}

	void JsonParseCoordinator::SharedData::SetJsonParseCoordinator(JsonParseCoordinator* parseCoordinator)
	{
		mParseCoordinator = parseCoordinator;
	}

	JsonParseCoordinator::JsonParseCoordinator(SharedData& data) :
		mData(&data)
	{
		mData->SetJsonParseCoordinator(this);
	}

	JsonParseCoordinator::~JsonParseCoordinator()
	{
		if (mIsClone)
		{
			for (auto parseHelper : mHelperList)
			{
				delete parseHelper;
			}
			delete mData;
		}
		else
		{
			if (mData != nullptr)
			{
				mData->CleanUp();
			}
		}
	}

	JsonParseCoordinator::JsonParseCoordinator(JsonParseCoordinator&& other) noexcept :
		mData(other.mData), mHelperList(std::move(other.mHelperList)), mIsClone(other.mIsClone), mFileName(other.mFileName)
	{
		mData->SetJsonParseCoordinator(this);

		other.mData = nullptr;
	}

	JsonParseCoordinator& JsonParseCoordinator::operator=(JsonParseCoordinator&& other) noexcept
	{
		if (this != &other)
		{
			mData = other.mData;
			mHelperList = std::move(other.mHelperList);
			mIsClone = other.mIsClone;
			mFileName = other.mFileName;
			mData->SetJsonParseCoordinator(this);

			other.mData = nullptr;
		}

		return *this;
	}

	JsonParseCoordinator* JsonParseCoordinator::Clone()
	{
		JsonParseCoordinator* clonedParseCoordinator = new JsonParseCoordinator(*GetSharedData()->Create());
		for (auto parseHelper : mHelperList)
		{
			clonedParseCoordinator->AddHelper(*parseHelper->Create());
		}
		clonedParseCoordinator->mIsClone = true;
		clonedParseCoordinator->mFileName = mFileName;

		return clonedParseCoordinator;
	}

	void JsonParseCoordinator::AddHelper(IJsonParseHelper& parseHelper)
	{
		if (mIsClone)
		{
			throw std::runtime_error("Cannot add parse helper to cloned coordinator");
		}
		for (auto helperInList : mHelperList)
		{
			if (parseHelper.TypeIdInstance() == helperInList->TypeIdInstance())
			{
				return;
			}
		}
		mHelperList.PushBack(&parseHelper);
	}

	void JsonParseCoordinator::RemoveHelper(IJsonParseHelper& parseHelper)
	{
		mHelperList.Remove(&parseHelper);

		if (mIsClone)
		{
			delete &parseHelper;
		}
	}

	bool JsonParseCoordinator::IsClone()
	{
		return mIsClone;
	}

	const Vector<IJsonParseHelper*>& JsonParseCoordinator::Helpers()
	{
		return mHelperList;
	}

	void JsonParseCoordinator::Initialize()
	{
		for (auto parseHelper : mHelperList)
		{
			parseHelper->Initialize();
		}
	}

	void JsonParseCoordinator::ParseObject(const std::string& string)
	{
		std::stringstream inputStream;
		inputStream << string;
		ParseObject(inputStream);
	}
	
	void JsonParseCoordinator::ParseObjectFromFile(const std::string& string)
	{
		std::ifstream file(string);
		if (file.good())
		{
			ParseObject(file);
		}
	}

	void JsonParseCoordinator::ParseObject(std::istream& inputStream)
	{
		mData->Initialize();
		Json::Value object;
		inputStream >> object;
		ParseMembers(object);
	}

	JsonParseCoordinator::SharedData* JsonParseCoordinator::GetSharedData()
	{
		return mData;
	}

	void JsonParseCoordinator::SetSharedData(SharedData* data)
	{
		if (data != nullptr)
		{
			mData = data;
			data->SetJsonParseCoordinator(this);
		}
	}

	void JsonParseCoordinator::ParseMembers(const Json::Value& value, size_t index)
	{
		for (const Json::String& memberName : value.getMemberNames())
		{
			mData->IncrementDepth();
			Parse(memberName, value[memberName], index);
			mData->DecrementDepth();
		}
	}

	void JsonParseCoordinator::Parse(const std::string& key, const Json::Value& value, size_t index)
	{
		if (value.isObject())
		{
			for (auto parseHelper : mHelperList)
			{
				if (parseHelper->StartHandler(*mData, key, value, index))
				{
					ParseMembers(value);
					parseHelper->EndHandler(*mData, key, value);
					break;
				}
			}
		}
		else if (value.isArray())
		{
			if (value[0].isObject())
			{
				for (Json::ArrayIndex i = 0; i < value.size(); i++)
				{
					ParseMembers(value[i], i);
				}
			}
			else
			{
				for (Json::ArrayIndex i = 0; i < value.size(); i++)
				{
					Parse(key, value[i], i);
				}
			}
		}
		else
		{
			for (auto parseHelper : mHelperList)
			{
				if (parseHelper->StartHandler(*mData, key, value, index))
				{
					parseHelper->EndHandler(*mData, key, value);
					break;
				}
			}
		}
	}
};