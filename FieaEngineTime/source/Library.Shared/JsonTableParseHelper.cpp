#include "pch.h"
#include "JsonTableParseHelper.h"
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(JsonTableParseHelper)

	RTTI_DEFINITIONS(JsonTableParseHelper::SharedData)
		

	void JsonTableParseHelper::SharedData::Initialize()
	{
		if (data != nullptr)
		{
			delete data;
		}
		data = new GameObject();
	}

	void JsonTableParseHelper::SharedData::CleanUp()
	{
		delete data;
	}

	gsl::owner<JsonTableParseHelper::SharedData*> JsonTableParseHelper::SharedData::Create() const
	{
		return new JsonTableParseHelper::SharedData();
	}
		
	gsl::owner<IJsonParseHelper*> JsonTableParseHelper::Create() const
	{
		return new JsonTableParseHelper();
	}

	GameObject& JsonTableParseHelper::SharedData::GetData()
	{
		return *data;
	}

	void JsonTableParseHelper::Initialize()
	{
		datumTypes.Insert(std::make_pair("integer", Datum::DatumTypes::Integer));
		datumTypes.Insert(std::make_pair("float", Datum::DatumTypes::Float));
		datumTypes.Insert(std::make_pair("matrix", Datum::DatumTypes::Matrix));
		datumTypes.Insert(std::make_pair("pointer", Datum::DatumTypes::Pointer));
		datumTypes.Insert(std::make_pair("string", Datum::DatumTypes::String));
		datumTypes.Insert(std::make_pair("table", Datum::DatumTypes::Table));
		datumTypes.Insert(std::make_pair("vector", Datum::DatumTypes::Vector));
	}

	void JsonTableParseHelper::CleanUp()
	{

	}

	bool JsonTableParseHelper::StartHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value, size_t index)
	{
		JsonTableParseHelper::SharedData* customSharedData = sharedData.As<JsonTableParseHelper::SharedData>();
		if (customSharedData == nullptr)
		{
			return false;
		}
		if (contextStack.IsEmpty())
		{
			contextStack.Push(ContextFrame("", customSharedData->data, "Scope"));
		}

		ContextFrame currentFrame = contextStack.Top();
		Scope* currentScope = currentFrame.mCurrentScope;

		if (value.isObject())
		{
			if (key != valueKey)
			{
				contextStack.Push(ContextFrame(key, currentFrame.mCurrentScope, currentFrame.mClassName));
			}
		}
		else 
		{
			if (key == classKey)
			{
				contextStack.Push(ContextFrame(currentFrame.mName, currentFrame.mCurrentScope, value.asString()));
			}
			else if (key == typeKey)
			{
				if (datumTypes[value.asString()] == Datum::DatumTypes::Table)
				{
					if (currentFrame.mClassName == "Scope")
					{
						contextStack.Push(ContextFrame(currentFrame.mName, currentFrame.mCurrentScope, "Scope"));
					}
					Scope* newScope = Factory<Scope>::Create(currentFrame.mClassName);
					if (newScope == nullptr)
					{
						throw std::runtime_error(currentFrame.mClassName + "does not have a factory associated with it");
					}
					currentScope->Adopt(currentFrame.mName, *newScope);
					ContextFrame newFrame(currentFrame.mName, newScope, "Scope");
					contextStack.Pop();
					contextStack.Push(newFrame);
				}
				else
				{
					Datum& datum = currentScope->Append(currentFrame.mName);
					if (!datum.IsExternal())
					{
						datum.SetType(datumTypes[value.asString()]);
					}
				}
			}
			else if (key == valueKey)
			{
				Datum* datum = currentScope->Find(currentFrame.mName);
				if (datum->IsExternal())
				{
					datum->SetFromString(value.asString(), index);
				}
				else
				{
					datum->PushBackFromString(value.asString());
				}
			}
			else
			{
				return false;
			}
		}

		return true;
	}

	bool JsonTableParseHelper::EndHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value)
	{
		JsonTableParseHelper::SharedData* customSharedData = sharedData.As<JsonTableParseHelper::SharedData>();
		if (customSharedData == nullptr)
		{
			return false;
		}

		if (value.isObject())
		{
			contextStack.Pop();
		}

		if (key == contextStack.Top().mName)
		{
			contextStack.Pop();
		}

		return true;
	}

};