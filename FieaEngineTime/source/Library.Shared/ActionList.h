#pragma once
#include "Action.h"
#include "GameState.h"

namespace FieaGameEngine
{
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action);
	
	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		ActionList();

		/// <summary>
		/// Constructor for children
		/// </summary>
		/// <param name="id">RTTI id passed for proper construction</param>
		ActionList(RTTI::IdType id);
		ActionList(const ActionList&) = default;
		ActionList(ActionList&&) noexcept = default;
		ActionList& operator=(const ActionList&) = default;
		ActionList& operator=(ActionList&&) noexcept = default;
		virtual ~ActionList() = default;

		/// <summary>
		/// Overridden Update Function. Iterates through list of Actions and calls Update
		/// </summary>
		/// <param name="deltaTime">passed to Actions</param>
		virtual void Update(const GameTime & deltaTime) override;

		/// <summary>
		/// Returns signatures of prescribed attributes
		/// </summary>
		/// <returns>signatures of prescribed attributes</returns>
		static const Vector<Signature> Signatures();
	};

	ConcreteFactory(ActionList, Scope)
}

