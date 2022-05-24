#pragma once
#include <gsl/pointers>
#include "GameObject.h"

namespace LibraryDesktopUnitTests
{
	class Avatar : public FieaGameEngine::GameObject
	{
		RTTI_DECLARATIONS(Avatar, FieaGameEngine::GameObject);

	public:
		Avatar();

		gsl::owner<Avatar*> Clone() const override;

		void Update(const FieaGameEngine::GameTime& deltaTime) override;

		size_t HitPoints{ 100 };

		static FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();
	};

	ConcreteFactory(Avatar, FieaGameEngine::Scope);
}