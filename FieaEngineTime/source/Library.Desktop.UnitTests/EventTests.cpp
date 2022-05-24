#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "Event.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include "EventSubscribers.h"
#include "EventQueue.h"
#include "GameTime.h"
#include "ToStringSpecializationsEvent.h"
#include <stdexcept>
#include <crtdbg.h>
#include <string>
#include <gsl/pointers>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std::string_literals;

namespace LibraryDesktopUnitTests
{
	TEST_CLASS(EventTests)
	{
	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined (_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(EventQueueEnqueueu)
		{
			GameTime gameTime;
			Foo foo(5);
			FooSubscriber fooSubscriber;
			EventQueue eventQueue;

			std::shared_ptr<Event<Foo>> event = std::make_shared<Event<Foo>>(foo);

			Assert::AreEqual(event->Message(), foo);
			Assert::AreEqual(size_t(0), eventQueue.Size());
			eventQueue.Enqueue(event, gameTime);
			Assert::AreEqual(size_t(1), eventQueue.Size());

			Event<Foo>::Subscribe(&fooSubscriber);
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(1)));
			Assert::IsFalse(fooSubscriber.WasNotified);
			eventQueue.Update(gameTime);
			Assert::IsTrue(fooSubscriber.WasNotified);

			fooSubscriber.WasNotified = false;

			eventQueue.Update(gameTime);
			Assert::IsFalse(fooSubscriber.WasNotified);
			Assert::AreEqual(size_t(0), eventQueue.Size());
			Assert::IsTrue(eventQueue.IsEmpty());

			eventQueue.Enqueue(event, gameTime);
			eventQueue.Clear();
			Assert::IsTrue(eventQueue.IsEmpty());

			eventQueue.Enqueue(event, gameTime);
			Event<Foo>::Unsubscribe(&fooSubscriber);
			eventQueue.Update(gameTime);
			Assert::IsFalse(fooSubscriber.WasNotified);

			eventQueue.Enqueue(event, gameTime);
			Event<Foo>::Subscribe(&fooSubscriber);
			Event<Foo>::UnsubscribeAll();
			eventQueue.Update(gameTime);
			Assert::IsFalse(fooSubscriber.WasNotified);
		}

	private:
		static _CrtMemState startMemState;
	};
	_CrtMemState EventTests::startMemState;
}