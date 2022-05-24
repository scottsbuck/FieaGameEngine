#pragma once
#include "Event.h"

namespace FieaGameEngine
{
	template<typename T>
	RTTI_DEFINITIONS(Event<T>)

	template<typename T>
	Event<T>::Event(T& messageObject) :
		EventPublisher(mSubscriberList), mMessageObject(messageObject)
	{
	
	}

	template<typename T>
	inline void Event<T>::Subscribe(EventSubscriber* subscriberToAdd)
	{
		if (subscriberToAdd != nullptr)
		{
			if (mSubscriberList.Find(subscriberToAdd) == mSubscriberList.end())
			{
				mSubscriberList.PushBack(subscriberToAdd);
			}
		}
	}

	template<typename T>
	inline void Event<T>::Unsubscribe(EventSubscriber* subscriberToRemove)
	{
		if (subscriberToRemove != nullptr)
		{
			mSubscriberList.Remove(subscriberToRemove);
		}
	}

	template<typename T>
	inline void Event<T>::UnsubscribeAll()
	{
		mSubscriberList.Clear();
	}

	template<typename T>
	inline const T& Event<T>::Message() const
	{
		return mMessageObject;
	}
}