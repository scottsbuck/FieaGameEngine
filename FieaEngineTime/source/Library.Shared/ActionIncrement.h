#pragma once
#include "Action.h"

namespace FieaGameEngine
{
	class ActionIncrement : public Action
	{
		RTTI_DECLARATIONS(ActionIncrement, Action);

	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		ActionIncrement();

		ActionIncrement(const ActionIncrement&) = default;
		ActionIncrement(ActionIncrement&&) noexcept = default;
		ActionIncrement& operator=(const ActionIncrement&) = default;
		ActionIncrement& operator=(ActionIncrement&&) noexcept = default;
		virtual ~ActionIncrement() = default;

		/// <summary>
		/// Overridden Update Function. Adds step to target
		/// </summary>
		/// <param name="deltaTime">nothing</param>
		virtual void Update(const GameTime& deltaTime) override;

		/// <summary>
		/// Returns signatures of prescribed attributes
		/// </summary>
		/// <returns>signatures of prescribed attributes</returns>
		static const Vector<Signature> Signatures();

	protected:

		std::string mTarget{ "" };
		float mStep{ 0 };

	};

	ConcreteFactory(ActionIncrement, Scope)
}