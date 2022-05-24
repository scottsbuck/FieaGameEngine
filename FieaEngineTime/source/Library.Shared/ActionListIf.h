#pragma once
#include "ActionList.h"

namespace FieaGameEngine
{
	class ActionListIf : public ActionList
	{
		RTTI_DECLARATIONS(ActionListIf, ActionList);

	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		ActionListIf();

		ActionListIf(const ActionListIf&) = default;
		ActionListIf(ActionListIf&&) noexcept = default;
		ActionListIf& operator=(const ActionListIf&) = default;
		ActionListIf& operator=(ActionListIf&&) noexcept = default;
		virtual ~ActionListIf() = default;

		/// <summary>
		/// Overridden Update Function. Checks To see if condition is true or false and performs the corresponding Actions
		/// </summary>
		/// <param name="deltaTime">passed to called actions</param>
		virtual void Update(const GameTime & deltaTime) override;

		/// <summary>
		/// Returns signatures of prescribed attributes
		/// </summary>
		/// <returns>signatures of prescribed attributes</returns>
		static const Vector<Signature> Signatures();

	protected:
		size_t mCondition{ 0 };

	};

	ConcreteFactory(ActionListIf, Scope)
}