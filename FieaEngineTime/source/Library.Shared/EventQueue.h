#pragma once
#include "EventPublisher.h"
#include "GameTime.h"

namespace FieaGameEngine
{
	class EventQueue
	{
	public:
		/// <summary>
		/// Queue up an event with a delay
		/// </summary>
		/// <param name="eventToQueue">the event to queue up (must be a shared pointer)</param>
		/// <param name="currentTime">a game time object</param>
		/// <param name="timeDelay">the time delay in milliseconds</param>
		void Enqueue(std::shared_ptr<EventPublisher> eventToQueue, const GameTime& currentTime, const std::chrono::milliseconds& timeDelay = std::chrono::milliseconds(0));
		/// <summary>
		/// The update call
		/// </summary>
		/// <param name="currentTime">the gametime object for update calls</param>
		void Update(const GameTime& currentTime);
		/// <summary>
		/// Clears the list
		/// </summary>
		void Clear();
		/// <summary>
		/// Checks if event queue is empty
		/// </summary>
		/// <returns>if empty</returns>
		bool IsEmpty();
		/// <summary>
		/// returns size of eventqueue
		/// </summary>
		/// <returns>size</returns>
		size_t Size();
	private:

		Vector<std::shared_ptr<EventPublisher>> mEventQueue;
	};
}