#pragma once
#include "Vector.h"
#include "Scope.h"
#include "Datum.h"
#include "Factory.h"

namespace FieaGameEngine
{
	struct CreateDefermentInfo
	{
		/// <summary>
		/// Constructor for the deferment of the CreateAction
		/// </summary>
		/// <param name="containingScope">scope the action should be placed into</param>
		/// <param name="className">class of action to create</param>
		/// <param name="instanceName">instance name</param>
		CreateDefermentInfo(Scope* containingScope, const std::string& className, const std::string& instanceName) :
			mContainingScope(containingScope), mClassName(className), mInstanceName(instanceName)
		{
		}

		Scope* mContainingScope;
		std::string mClassName;
		std::string mInstanceName;
	};

	struct DestroyDefermentInfo
	{
		/// <summary>
		/// Constructor for the deferment of the DestroyAction
		/// </summary>
		/// <param name="containingScope">Scope the the action is located in to destroy</param>
		/// <param name="actionName">name of action to destroy</param>
		DestroyDefermentInfo(Scope* containingScope, const std::string& actionName) :
			mContainingScope(containingScope), mActionName(actionName)
		{
		}

		Scope* mContainingScope;
		std::string mActionName;
	};

	class GameState
	{
	public:
		/// <summary>
		/// Call to Queue a CreateAction
		/// </summary>
		/// <param name="createActionInfo">info about the createAction to pass to the queue</param>
		static void QueueCreateAction(const CreateDefermentInfo& createActionInfo);
		/// <summary>
		/// Actual Creation of Actions. Goes through the queue
		/// </summary>
		static void CreateActions();
		/// <summary>
		/// Create Action Queue
		/// </summary>
		inline static Vector<CreateDefermentInfo> CreateActionQueue;

		/// <summary>
		/// Call to queue a DestroyAction
		/// </summary>
		/// <param name="destroyActionInfo">info about the destroyAction to pass to the queue</param>
		static void QueueDestroyAction(const DestroyDefermentInfo& destroyActionInfo);
		/// <summary>
		/// Actual Destruction of Actions. Goes through the queue
		/// </summary>
		static void DestroyActions();
		/// <summary>
		/// Destroy Action Queue
		/// </summary>
		inline static Vector<DestroyDefermentInfo> DestroyActionQueue;
	};
}