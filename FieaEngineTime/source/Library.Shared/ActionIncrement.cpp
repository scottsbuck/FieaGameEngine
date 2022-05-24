#include "pch.h"
#include "ActionIncrement.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIncrement)

	ActionIncrement::ActionIncrement() :
		Action(ActionIncrement::TypeIdClass())
	{

	}

	void ActionIncrement::Update(const GameTime&)
	{
		Datum* foundDatum = Search(mTarget);
		if (foundDatum->Type() == Datum::DatumTypes::Integer)
		{
			foundDatum->GetInt() += static_cast<int32_t>(mStep);
		}
		else if (foundDatum->Type() == Datum::DatumTypes::Float)
		{
			foundDatum->GetFloat() += mStep;
		}
		else
		{
			throw std::runtime_error("Cannot increment a value that is not an Integer or a Float");
		}
	}

	const Vector<Signature> ActionIncrement::Signatures()
	{
		return Vector<Signature>
		{
			{ "Target", Datum::DatumTypes::String, 1, offsetof(ActionIncrement, mTarget) },
			{ "Step", Datum::DatumTypes::Float, 1, offsetof(ActionIncrement, mStep) }
		};
	}
}