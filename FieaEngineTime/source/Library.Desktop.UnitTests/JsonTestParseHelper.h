#pragma once
#include <gsl/pointers>
#include "IJsonParseHelper.h"

namespace LibraryDesktopUnitTests
{
	class JsonTestParseHelper final : public FieaGameEngine::IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonTestParseHelper, FieaGameEngine::IJsonParseHelper)

	public:
		class SharedData final : public FieaGameEngine::JsonParseCoordinator::SharedData
		{
			RTTI_DECLARATIONS(SharedData, FieaGameEngine::JsonParseCoordinator::SharedData)

		public:
			virtual void Initialize() override;
			virtual gsl::owner<SharedData*> Create() const override;

			size_t maxDepth = 0;
		};

		virtual gsl::owner<IJsonParseHelper*> Create() const override;
		virtual void Initialize() override;
		virtual bool StartHandler(FieaGameEngine::JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& object, size_t index = 0) override;
		virtual bool EndHandler(FieaGameEngine::JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value) override;

		bool InitializeCalled = false;
		size_t startHandlerCount = 0;
		size_t endHandlerCount = 0;
		size_t arrayElementCount = 0;
	};
};

