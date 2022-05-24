#pragma once
#include "ActionList.h"

namespace FieaGameEngine
{
	class ActionListForEach : public ActionList
	{
		RTTI_DECLARATIONS(ActionListForEach, ActionList)

	public:

		ActionListForEach();

		ActionListForEach(RTTI::IdType id);
		ActionListForEach(const ActionListForEach&) = default;
		ActionListForEach(ActionListForEach&&) noexcept = default;
		ActionListForEach& operator=(const ActionListForEach&) = default;
		ActionListForEach& operator=(ActionListForEach&&) noexcept = default;
		virtual ~ActionListForEach() = default;

		virtual void Update(const GameTime & deltaTime) override;

		static const Vector<Signature> Signatures();

	protected:

		size_t mCurrentValue { 0 };
		std::string mDatumName { "" };
	};

	ConcreteFactory(ActionListForEach, Scope)
}