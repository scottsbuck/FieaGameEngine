#pragma once

#include "Foo.h"
#include "CppUnitTest.h"

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

	template<>
	std::wstring ToString<AttributedFoo>(const AttributedFoo& af)
	{
		af;
		RETURN_WIDE_STRING("attributed foo");
	}
}