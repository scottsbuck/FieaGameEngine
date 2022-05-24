#include "pch.h"
#include "ActionList.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionList)

	ActionList::ActionList() :
		Action(ActionList::TypeIdClass())
	{

	}

	ActionList::ActionList(RTTI::IdType id) : 
		Action(id)
	{

	}

	void ActionList::Update(const GameTime& deltaTime)
	{
		Datum* datum = Find("Actions");
		if (datum != nullptr)
		{
			Datum* childDatum = datum->GetScope()->Find("Actions");
			size_t size = childDatum->Size();
			for (size_t i = 0; i < size; i++)
			{
				assert(childDatum->GetScope(i)->Is(Action::TypeIdClass()));
				static_cast<Action*>(childDatum->GetScope(i))->Update(deltaTime);
			}
		}

		if (GetParent()->GetParent() == nullptr)
        {
            GameState::CreateActions();
            GameState::DestroyActions();
        }
	}

	const Vector<Signature> ActionList::Signatures()
	{
		return Vector<Signature>
		{
			{ "Actions", Datum::DatumTypes::Table, 0, 0 },
		};
	}
}