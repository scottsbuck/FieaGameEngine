#include "pch.h"
#include "EventPublisher.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventPublisher)

	void EventPublisher::Deliver()
	{
		if (mSubscriberList != nullptr)
		{
			for (auto& subscriber : *mSubscriberList)
			{
				subscriber->Notify(*this);
			}
		}
	}

	EventPublisher::EventPublisher(Vector<EventSubscriber*>& subscriberList) :
		mSubscriberList(&subscriberList)
	{

	}
}