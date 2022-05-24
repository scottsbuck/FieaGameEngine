#pragma once
#include "Event.h"
#include "Foo.h"

namespace LibraryDesktopUnitTests
{
	struct FooSubscriber final : public FieaGameEngine::EventSubscriber
	{
	public:

		void Notify(const FieaGameEngine::EventPublisher& currentEvent) override;

		bool WasNotified = false;
		int Data;
	};


}