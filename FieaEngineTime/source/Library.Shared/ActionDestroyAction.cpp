#include "pch.h"
#include "ActionDestroyAction.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionDestroyAction)

	ActionDestroyAction::ActionDestroyAction() :
		Action(ActionDestroyAction::TypeIdClass())
	{

	}

	void ActionDestroyAction::Update(const GameTime&)
	{
		assert(!mActionName.empty());
		GameState::QueueDestroyAction(DestroyDefermentInfo(GetParent(), mActionName));
	}

	const Vector<Signature> ActionDestroyAction::Signatures()
	{
		return Vector<Signature>
		{
			{ "ActionToDelete", Datum::DatumTypes::String, 1, offsetof(ActionDestroyAction, mActionName) }
		};
	}
}
