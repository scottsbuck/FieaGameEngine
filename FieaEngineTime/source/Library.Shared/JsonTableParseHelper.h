#pragma once
#include "IJsonParseHelper.h"
#include "JsonParseCoordinator.h"
#include "Factory.h"
#include "Scope.h"
#include "HashMap.h"
#include "Datum.h"
#include "Stack.h"
#include "GameObject.h"
#include <gsl/pointers>
namespace FieaGameEngine
{
	struct ContextFrame
	{
		ContextFrame(std::string name, Scope* currentScope, std::string className):
			mName(name), mCurrentScope(currentScope), mClassName(className)
		{
		}
		std::string mName;
		Scope* mCurrentScope;
		std::string mClassName;
	};

	class JsonTableParseHelper : public IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonTableParseHelper, IJsonParseHelper)

	public:

		class SharedData final : public JsonParseCoordinator::SharedData
		{
			RTTI_DECLARATIONS(SharedData, JsonParseCoordinator::SharedData)

			friend JsonTableParseHelper;

		public:
			/// <summary>
			/// sets data = to a new Scope
			/// </summary>
			virtual void Initialize() override;
			/// <summary>
			/// deletes scope
			/// </summary>
			virtual void CleanUp() override;
			/// <summary>
			/// virtual constructor
			/// </summary>
			/// <returns></returns>
			virtual gsl::owner<SharedData*> Create() const override;

			GameObject& GetData();

		private:
			GameObject* data{ nullptr };
			size_t maxDepth = 0;
		};

		/// <summary>
		/// virtual constructor creates a new table parse helper
		/// </summary>
		/// <returns>returns a interface pointer to the table parse helper</returns>
		virtual gsl::owner<IJsonParseHelper*> Create() const override;
		/// <summary>
		/// Initializes the datumTypes hashmap
		/// </summary>
		virtual void Initialize() override;
		/// <summary>
		/// ???
		/// </summary>
		virtual void CleanUp() override;
		/// <summary>
		/// deals the with the json value and stores it in the shared data depending on how exactly it is
		/// </summary>
		/// <param name="sharedData">the shared data where everything gets stored</param>
		/// <param name="key">the key part of the key value pair for the json object</param>
		/// <param name="value">the value part of the key value pair for the json object</param>
		/// <returns>a boolean if the handler was able to handle the key</returns>
		virtual bool StartHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value, size_t index = 0) override;
		/// <summary>
		/// handles the popping off the context stack
		/// </summary>
		/// <param name="sharedData">the shared data where everything gets stored</param>
		/// <param name="key">the key part of the key value pair for the json object</param>
		/// <param name="value">the value part of the key value pair for the json object</param>
		/// <returns>boolean if the handler was able to handle they key</returns>
		virtual bool EndHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value) override;

	private:

		HashMap<std::string, Datum::DatumTypes> datumTypes;

		Stack<ContextFrame> contextStack;

		std::string typeKey{ "type" };
		std::string valueKey{ "value" };
		std::string classKey{ "class" };

		size_t arrayIndex{ 0 };
	};
}


