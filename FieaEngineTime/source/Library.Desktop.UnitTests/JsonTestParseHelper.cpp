#include "pch.h"
#include "JsonTestParseHelper.h"

namespace LibraryDesktopUnitTests
{
	RTTI_DEFINITIONS(JsonTestParseHelper)

	RTTI_DEFINITIONS(JsonTestParseHelper::SharedData)

	void JsonTestParseHelper::SharedData::Initialize()
	{
		FieaGameEngine::JsonParseCoordinator::SharedData::Initialize();
		maxDepth = 0;
	}

	gsl::owner<JsonTestParseHelper::SharedData*> JsonTestParseHelper::SharedData::Create() const
	{
		return new SharedData();
	}

	gsl::owner<JsonTestParseHelper::IJsonParseHelper*> JsonTestParseHelper::Create() const
	{
		return new JsonTestParseHelper();
	}

	void JsonTestParseHelper::Initialize()
	{
		FieaGameEngine::IJsonParseHelper::Initialize();
		InitializeCalled = true;
		startHandlerCount = 0;
		endHandlerCount = 0;
	}

	bool JsonTestParseHelper::StartHandler(FieaGameEngine::JsonParseCoordinator::SharedData& sharedData, const std::string&, const Json::Value&, size_t)
	{
		JsonTestParseHelper::SharedData* customSharedData = sharedData.As<JsonTestParseHelper::SharedData>();
		if (customSharedData == nullptr)
		{
			return false;
		}
		startHandlerCount++;
		if (customSharedData->Depth() > customSharedData->maxDepth)
		{
			customSharedData->maxDepth = customSharedData->Depth();
		}

		return true;
	}

	bool JsonTestParseHelper::EndHandler(FieaGameEngine::JsonParseCoordinator::SharedData& sharedData, const std::string&, const Json::Value&)
	{
		JsonTestParseHelper::SharedData* customSharedData = sharedData.As < JsonTestParseHelper::SharedData>();
		if (customSharedData == nullptr)
		{
			return false;
		}
		endHandlerCount++;

		return true;
	}
};