#pragma once
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include "EventQueue.h"

namespace FieaGameEngine
{
	template <typename T>
	class Event : public EventPublisher
	{
		
		RTTI_DECLARATIONS(Event, EventPublisher)

	public:
		friend class EventQueue;

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="messageObject">message object that goes with the event</param>
		Event(T& messageObject);
		virtual ~Event() = default;
		Event(Event&) = default;
		Event& operator=(const Event&) = default;
		Event(Event&&) = default;
		Event& operator=(Event&&) = default;

		/// <summary>
		/// subscribes a subscriber to the event
		/// </summary>
		/// <param name="subscriberToAdd">the subscriber to add</param>
		static inline void Subscribe(EventSubscriber* subscriberToAdd);
		/// <summary>
		/// Removes a subscriber from the event
		/// </summary>
		/// <param name="subscriberToRemove">the subscriber to remove</param>
		static inline void Unsubscribe(EventSubscriber* subscriberToRemove);
		/// <summary>
		/// Removes all subscribers
		/// </summary>
		static inline void UnsubscribeAll();
		/// <summary>
		/// Returns the actual payload
		/// </summary>
		/// <returns>the T payload</returns>
		const T& Message() const;
		

	private:

		T& mMessageObject;
		static inline Vector<EventSubscriber*> mSubscriberList;
	};
}


#include "Event.inl"