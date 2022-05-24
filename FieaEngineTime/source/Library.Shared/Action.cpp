#include "pch.h"
#include "Action.h"
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Action)

	Action::Action(RTTI::IdType id) :
		Attributed(id)
	{

	}

	const std::string& Action::GetName()
	{
		return mName;
	}

	void Action::SetName(const std::string& name)
	{
		mName = name;
	}

	const Vector<Signature> Action::Signatures()
	{
		return Vector<Signature>
		{
			{ "Name", Datum::DatumTypes::String, 1, offsetof(Action, mName) },
		};
	}
}
