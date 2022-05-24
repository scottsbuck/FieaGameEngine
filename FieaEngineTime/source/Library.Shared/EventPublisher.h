#pragma once
#include "RTTI.h"
#include "EventSubscriber.h"
#include "Vector.h"
#include "GameTime.h"

namespace FieaGameEngine
{
	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)

	public:

		friend class EventQueue;

		virtual ~EventPublisher() = default;
		EventPublisher(EventPublisher&) = default;
		EventPublisher& operator=(const EventPublisher&) = default;
		EventPublisher(EventPublisher&&) = default;
		EventPublisher& operator=(EventPublisher&&) = default;

		/// <summary>
		/// Function to notify all subscribers of the event
		/// </summary>
		void Deliver();

	protected:
		EventPublisher(Vector<EventSubscriber*>& subscriberList);
		EventPublisher() = default;

	private:
		std::chrono::high_resolution_clock::time_point mExpirationTime;

		std::chrono::milliseconds mDelay;

		Vector<EventSubscriber*>* mSubscriberList{ nullptr };

	};
}
