#include "pch.h"
#include "Avatar.h"

using namespace FieaGameEngine;

namespace LibraryDesktopUnitTests
{
	RTTI_DEFINITIONS(Avatar)

	Avatar::Avatar() :
		GameObject(Avatar::TypeIdClass())
	{

	}

	gsl::owner<Avatar*> Avatar::Clone() const
	{
		return new Avatar(*this);
	}

	void Avatar::Update(const GameTime& deltaTime)
	{
		HitPoints -= 10;
		GameObject::Update(deltaTime);
	}

	Vector<Signature> Avatar::Signatures()
	{
		return Vector<FieaGameEngine::Signature>
		{
			{ "HitPoints", Datum::DatumTypes::Integer, 1, offsetof(Avatar, HitPoints) }
		};
	}
}