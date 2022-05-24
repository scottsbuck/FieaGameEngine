#pragma once
#include "Attributed.h"
#include "Factory.h"
#include "Transform.h"
#include "GameClock.h"
#include "GameTime.h"

namespace FieaGameEngine
{
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed);

	public:

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="id">RTTI id to pass in for proper construction</param>
		Action(RTTI::IdType id);
		Action(const Action&) = default;
		Action(Action&&) noexcept = default;
		Action& operator=(const Action&) = default;
		Action& operator=(Action&&) noexcept = default;
		virtual ~Action() = default;

		/// <summary>
		/// pure virtual update function implemented by children
		/// </summary>
		/// <param name="deltaTime">delta time to pass to children for functional use</param>
		virtual void Update(const GameTime& deltaTime) = 0;

		/// <summary>
		/// Returns Name of Action
		/// </summary>
		/// <returns>Name of Action</returns>
		const std::string& GetName();
		/// <summary>
		/// Sets Action Name
		/// </summary>
		/// <param name="name">Name to set to</param>
		void SetName(const std::string& name);

		/// <summary>
		/// vector of prescribed attributes
		/// </summary>
		/// <returns>prescribed attributes</returns>
		static const Vector<Signature> Signatures();

	protected:

		std::string mName;
	};
}

