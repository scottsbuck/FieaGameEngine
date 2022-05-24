#include "pch.h"
#include "GameState.h"
#include "Action.h"

namespace FieaGameEngine 
{
	void GameState::QueueCreateAction(const CreateDefermentInfo& createActionInfo)
	{
		CreateActionQueue.PushBack(createActionInfo);
	}

	void GameState::CreateActions()
	{
		for (size_t i = 0; i < CreateActionQueue.Size(); i++)
		{
			CreateDefermentInfo& currentCreateAction = CreateActionQueue[i];
			currentCreateAction.mContainingScope->Adopt(currentCreateAction.mInstanceName, *Factory<Scope>::Create(currentCreateAction.mClassName));
		}
		CreateActionQueue.Clear();
	}

	void GameState::QueueDestroyAction(const DestroyDefermentInfo& destroyActionInfo)
	{
		DestroyActionQueue.PushBack(destroyActionInfo);
	}

	void GameState::DestroyActions()
	{
		for (size_t i = 0; i < DestroyActionQueue.Size(); i++)
		{
			DestroyDefermentInfo& currentQueueItem = DestroyActionQueue[i];
			Datum* datum = currentQueueItem.mContainingScope->Find("Actions");
			for (size_t j = 0; j < datum->Size(); j++)
			{
				Scope* currentAction = datum->GetScope(j);
				assert(currentAction->Is(Action::TypeIdClass()));
				if (static_cast<Action*>(currentAction)->GetName() == currentQueueItem.mActionName)
				{
					datum->RemoveAt(j);
					delete currentAction;
					break;
				}
			}
		}
		DestroyActionQueue.Clear();
	}
}