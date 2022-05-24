#pragma once
#include <string>
#include <gsl/pointers>
#include "Action.h"
#include "Attributed.h"
#include "Factory.h"
#include "Transform.h"
#include "GameClock.h"
#include "GameTime.h"
#include "GameState.h"

namespace FieaGameEngine
{
	class GameObject : public Attributed
	{
		RTTI_DECLARATIONS(GameObject, Attributed)

	public:

		/// <summary>
		/// Default Constructor
		/// </summary>
		GameObject();
		/// <summary>
		/// Constructor for child classes
		/// </summary>
		/// <param name="id">id type of the child class to pass to the attributed constructor</param>
		GameObject(RTTI::IdType id);
		GameObject(const GameObject&) = default;
		GameObject(GameObject&&) noexcept = default;
		GameObject& operator=(const GameObject&) = default;
		GameObject& operator=(GameObject&&) noexcept = default;
		virtual ~GameObject() = default;

		/// <summary>
		/// Virtual Copy constructor
		/// </summary>
		/// <returns>overriden from Scope, returns a new GameObject</returns>
		virtual gsl::owner<GameObject*> Clone() const override;
		/// <summary>
		/// RTTI Equals override
		/// </summary>
		/// <param name="rhs">thing to compare to</param>
		/// <returns>returns pointer comparison</returns>
		virtual bool Equals(const RTTI* rhs) const override;
		/// <summary>
		/// ToString overriden from RTTI
		/// </summary>
		/// <returns>returns mName</returns>
		virtual std::string ToString() const override;
		/// <summary>
		/// update function that calls update on all children. Virtual to override for derived classes
		/// </summary>
		/// <param name="deltaTime">GameTime object to be passed to each child</param>
		virtual void Update(const GameTime& deltaTime);
		/// <summary>
		/// Signatures which contains prescribed attributes of GameObject
		/// </summary>
		/// <returns>The Signatures</returns>
		static const Vector<Signature> Signatures();

		void CreateAction(const std::string& className, const std::string& instanceName);

		const Datum& Actions();
	protected:

		std::string mName;
		Transform mTransform;
	};

	ConcreteFactory(GameObject, Scope)
}