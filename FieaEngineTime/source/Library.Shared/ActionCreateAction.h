#pragma once
#include "Action.h"
#include "GameState.h"

namespace FieaGameEngine
{
	class ActionCreateAction : public Action
	{
		RTTI_DECLARATIONS(ActionCreateAction, Action);

	public:
		/// <summary>
		/// default constructor
		/// </summary>
		ActionCreateAction();

		ActionCreateAction(const ActionCreateAction&) = default;
		ActionCreateAction(ActionCreateAction&&) noexcept = default;
		ActionCreateAction& operator=(const ActionCreateAction&) = default;
		ActionCreateAction& operator=(ActionCreateAction&&) noexcept = default;
		virtual ~ActionCreateAction() = default;

		/// <summary>
		/// Overridden Update function adds the action create to the queue 
		/// </summary>
		/// <param name="deltaTime">does nothing</param>
		virtual void Update(const GameTime & deltaTime) override;

		/// <summary>
		/// Returns signatures of prescribed attributes
		/// </summary>
		/// <returns>signatures of prescribed attributes</returns>
		static const Vector<Signature> Signatures();

	protected:

		std::string mClassName{ "" };
		std::string mInstanceName{ "" };

	};

	ConcreteFactory(ActionCreateAction, Scope)
}


