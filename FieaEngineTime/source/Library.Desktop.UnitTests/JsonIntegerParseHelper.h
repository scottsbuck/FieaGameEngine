#pragma once
#include "RTTI.h"
#include "IJsonParseHelper.h"
#include <gsl/pointers>
#include "Vector.h"

namespace LibraryDesktopUnitTests
{
	class JsonIntegerParseHelper final : public FieaGameEngine::IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonIntegerParseHelper, FieaGameEngine::IJsonParseHelper)

	public:
		class SharedData final : public FieaGameEngine::JsonParseCoordinator::SharedData
		{
			RTTI_DECLARATIONS(SharedData, FieaGameEngine::JsonParseCoordinator::SharedData)

		public:
			virtual void Initialize() override;
			virtual gsl::owner<SharedData*> Create() const override;

			FieaGameEngine::Vector<std::int32_t> data;
		};

		virtual gsl::owner<IJsonParseHelper*> Create() const override;
		virtual void Initialize() override;
		virtual bool StartHandler(FieaGameEngine::JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& object, size_t index = 0) override;
		virtual bool EndHandler(FieaGameEngine::JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value) override;

	private:
		inline static const std::string mIntegerKey = "integer";
		bool mParsingData = false;
	};
};