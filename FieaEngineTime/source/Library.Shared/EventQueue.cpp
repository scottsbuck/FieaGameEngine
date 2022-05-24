#include "pch.h"
#include "EventQueue.h"
#include "GameState.h"

namespace FieaGameEngine
{
	void EventQueue::Enqueue(std::shared_ptr<EventPublisher> eventToQueue, const GameTime& currentTime, const std::chrono::milliseconds& timeDelay)
	{
		EventPublisher* event = eventToQueue.get();
		event->mDelay = timeDelay;
		event->mExpirationTime = currentTime.CurrentTime() + timeDelay;

		mEventQueue.PushBack(eventToQueue);
	}

	void EventQueue::Update(const GameTime& currentTime)
	{
		Vector<std::shared_ptr<EventPublisher>> eventsToRemove;
		for (auto& event : mEventQueue)
		{
			if (currentTime.CurrentTime() >= event.get()->mExpirationTime)
			{
				event->Deliver();
				eventsToRemove.PushBack(event);
			}
		}

		for (auto& event : eventsToRemove)
		{
			mEventQueue.Remove(event);
		}
	}

	void EventQueue::Clear()
	{
		mEventQueue.Clear();
	}

	bool EventQueue::IsEmpty()
	{
		return mEventQueue.IsEmpty();
	}

	size_t EventQueue::Size()
	{
		return mEventQueue.Size();
	}
}