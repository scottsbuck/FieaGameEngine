#include "pch.h"
#include "ActionListForEach.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionListForEach)

	ActionListForEach::ActionListForEach() :
		ActionList(ActionListForEach::TypeIdClass())
	{
	
	}

	ActionListForEach::ActionListForEach(RTTI::IdType id) :
		ActionList(id)
	{
	
	}

	void ActionListForEach::Update(const GameTime& deltaTime)
	{	
		Datum* contentsDatum = Search(mDatumName); 
		Datum::DatumTypes type = contentsDatum->Type();
		for (size_t i = 0; i < contentsDatum->Size(); i++)
		{
			mCurrentValue = i;
			ActionList::Update(deltaTime);
		}
	}

	const Vector<Signature> ActionListForEach::Signatures()
	{
		return Vector<Signature>
		{
			{ "CurrentValue", Datum::DatumTypes::Integer, 1, offsetof(ActionListForEach, mCurrentValue) },
			{ "DatumName", Datum::DatumTypes::String, 1, offsetof(ActionListForEach, mDatumName) }
		};
	}
}
