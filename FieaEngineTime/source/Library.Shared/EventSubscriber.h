#pragma once

namespace FieaGameEngine
{
	class EventPublisher;

	class EventSubscriber
	{
	public:
		/// <summary>
		/// notify function to override for each subscriber
		/// </summary>
		/// <param name="currentEvent">the event that contains the message to be notified of</param>
		virtual void Notify(const EventPublisher& currentEvent) = 0;
	};
}