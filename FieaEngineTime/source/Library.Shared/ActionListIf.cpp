#include "pch.h"
#include "ActionListIf.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionListIf)

	ActionListIf::ActionListIf() :
		ActionList(ActionListIf::TypeIdClass())
	{

	}

	void ActionListIf::Update(const GameTime& deltaTime)
	{
		if (mCondition == 1)
		{
			Datum* datum = Find("True");
			if (datum != nullptr)
			{
				Datum* childDatum = datum->GetScope()->Find("True");
				size_t size = childDatum->Size();
				for (size_t i = 0; i < size; i++)
				{
					assert(childDatum->GetScope(i)->Is(Action::TypeIdClass()));
					static_cast<Action*>(childDatum->GetScope(i))->Update(deltaTime);
				}
			}
		}
		else
		{
			Datum* datum = Find("False");
			if (datum != nullptr)
			{
				Datum* childDatum = datum->GetScope()->Find("False");
				size_t size = childDatum->Size();
				for (size_t i = 0; i < size; i++)
				{
					assert(childDatum->GetScope(i)->Is(Action::TypeIdClass()));
					static_cast<Action*>(childDatum->GetScope(i))->Update(deltaTime);
				}
			}
		}
	}

	const Vector<Signature> ActionListIf::Signatures()
	{
		return Vector<Signature>
		{
			{ "Condition", Datum::DatumTypes::Integer, 1, offsetof(ActionListIf, mCondition) },
			{ "True", Datum::DatumTypes::Table, 0, 0 },
			{ "False", Datum::DatumTypes::Table, 0, 0 }
		};
	}
}