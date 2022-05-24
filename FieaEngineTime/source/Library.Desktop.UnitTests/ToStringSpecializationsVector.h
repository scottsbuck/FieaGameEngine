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
	std::wstring ToString<Vector<Foo>::Iterator>(const Vector<Foo>::Iterator& t)
	{
		try
		{
			return ToString(*t);
		}
		catch (const std::exception&)
		{
			return L"end()"s;
		}
	}

	template<>
	std::wstring ToString<Vector<Foo>::ConstIterator>(const Vector<Foo>::ConstIterator& t)
	{
		try
		{
			return ToString(*t);
		}
		catch (const std::exception&)
		{
			return L"end()"s;
		}
	}
}
