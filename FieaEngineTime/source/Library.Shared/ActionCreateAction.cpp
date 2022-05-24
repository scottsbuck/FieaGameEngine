#include "pch.h"
#include "ActionCreateAction.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionCreateAction)
		
	ActionCreateAction::ActionCreateAction() :
		Action(ActionCreateAction::TypeIdClass())
	{

	}
		
	void ActionCreateAction::Update(const GameTime&)
	{
		assert(!mClassName.empty());
		assert(!mInstanceName.empty());
		GameState::QueueCreateAction(CreateDefermentInfo(GetParent(), mClassName, mInstanceName));
	}

	const Vector<Signature> ActionCreateAction::Signatures()
	{
		return Vector<Signature>
		{
			{ "ActionClassName", Datum::DatumTypes::String, 1, offsetof(ActionCreateAction, mClassName) },
			{ "ActionInstanceName", Datum::DatumTypes::String, 1, offsetof(ActionCreateAction, mInstanceName) }
		};
	}
}