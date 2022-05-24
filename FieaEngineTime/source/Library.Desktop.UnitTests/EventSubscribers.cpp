#include "pch.h"
#include "EventSubscribers.h"

using namespace FieaGameEngine;

namespace LibraryDesktopUnitTests
{
	void FooSubscriber::Notify(const FieaGameEngine::EventPublisher& event)
	{
		const Event<Foo>* e = event.As<Event<Foo>>();
		if (e != nullptr)
		{
			const Foo& foo = e->Message();
			Data = foo.Data();
		}

		WasNotified = true;
	}
}