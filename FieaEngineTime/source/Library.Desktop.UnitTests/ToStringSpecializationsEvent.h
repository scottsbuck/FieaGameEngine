#pragma once
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

using namespace std::string_literals;
using namespace FieaGameEngine;
using namespace LibraryDesktopUnitTests;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<> inline
		std::wstring ToString<Foo>(const Foo& t)
	{
		RETURN_WIDE_STRING(t.Data());
	}

	template<> inline
		std::wstring ToString<Foo>(Foo* t)
	{
		RETURN_WIDE_STRING(t->Data());
	}
}