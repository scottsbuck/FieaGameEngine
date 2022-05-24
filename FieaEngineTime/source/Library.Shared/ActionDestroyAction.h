#pragma once
#include "Action.h"
#include "GameState.h"

namespace FieaGameEngine
{
	class ActionDestroyAction : public Action
	{
		RTTI_DECLARATIONS(ActionDestroyAction, Action);

	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		ActionDestroyAction();

		ActionDestroyAction(const ActionDestroyAction&) = default;
		ActionDestroyAction(ActionDestroyAction&&) noexcept = default;
		ActionDestroyAction& operator=(const ActionDestroyAction&) = default;
		ActionDestroyAction& operator=(ActionDestroyAction&&) noexcept = default;
		virtual ~ActionDestroyAction() = default;

		/// <summary>
		/// Overridden update function. adds the destroy action to the queue
		/// </summary>
		/// <param name="deltaTime">nothing</param>
		virtual void Update(const GameTime& deltaTime) override;

		/// <summary>
		/// Returns signatures of prescribed attributes
		/// </summary>
		/// <returns>signatures of prescribed attributes</returns>
		static const Vector<Signature> Signatures();

	protected:

		std::string mActionName{ "" };

	};

	ConcreteFactory(ActionDestroyAction, Scope)
}

