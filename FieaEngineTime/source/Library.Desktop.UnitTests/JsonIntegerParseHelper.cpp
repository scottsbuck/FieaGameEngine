#include "pch.h"
#include "JsonIntegerParseHelper.h"

namespace LibraryDesktopUnitTests
{
	RTTI_DEFINITIONS(JsonIntegerParseHelper)

	RTTI_DEFINITIONS(JsonIntegerParseHelper::SharedData)

	void JsonIntegerParseHelper::SharedData::Initialize()
	{
		FieaGameEngine::JsonParseCoordinator::SharedData::Initialize();
		data.Clear();
	}

	gsl::owner<JsonIntegerParseHelper::SharedData*> JsonIntegerParseHelper::SharedData::Create() const
	{
		return new SharedData();
	}

	gsl::owner<JsonIntegerParseHelper::IJsonParseHelper*> JsonIntegerParseHelper::Create() const
	{
		return new JsonIntegerParseHelper();
	}

	void JsonIntegerParseHelper::Initialize()
	{
		FieaGameEngine::IJsonParseHelper::Initialize();
		mParsingData = false;
	}

	bool JsonIntegerParseHelper::StartHandler(FieaGameEngine::JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& object, size_t)
	{
		JsonIntegerParseHelper::SharedData* customSharedData = sharedData.As<JsonIntegerParseHelper::SharedData>();
		if (customSharedData == nullptr)
		{
			return false;
		}

		if (key != mIntegerKey)
		{
			return false;
		}

		if (mParsingData)
		{
			throw std::runtime_error("Received another start element while already parsing an integer.");
		}

		mParsingData = true;

		customSharedData->data.PushBack(object.asInt());

		return true;
	}

	bool JsonIntegerParseHelper::EndHandler(FieaGameEngine::JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value&)
	{
		JsonIntegerParseHelper::SharedData* customSharedData = sharedData.As < JsonIntegerParseHelper::SharedData>();
		if (customSharedData == nullptr || key != mIntegerKey || mParsingData == false)
		{
			return false;
		}

		mParsingData = false;

		return true;
	}
};