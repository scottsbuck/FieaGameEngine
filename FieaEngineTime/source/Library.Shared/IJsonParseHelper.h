#pragma once
#include <string>
#include <gsl/pointers>
#include "RTTI.h"
#include "JsonParseCoordinator.h"
#include "json/json.h"

namespace FieaGameEngine
{
	class IJsonParseHelper : public RTTI
	{
		RTTI_DECLARATIONS(IJsonParseHelper, RTTI)

	public:
		virtual gsl::owner<IJsonParseHelper*> Create() const = 0;
		virtual void Initialize();
		virtual void CleanUp();
		virtual bool StartHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value, size_t index = 0) = 0;
		virtual bool EndHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value) = 0;
		virtual ~IJsonParseHelper() = default;

	protected:
		IJsonParseHelper() = default;
	};
}
