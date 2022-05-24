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

	//template<>
	//std::wstring ToString<Datum>(const Datum& datum)
	//{
	//	datum;
	//	RETURN_WIDE_STRING("lmao");
	//}

	template<>
	std::wstring ToString<Datum>(Datum* datum)
	{
		datum;
		RETURN_WIDE_STRING("lmao");
	}

	template<>
	std::wstring ToString<Datum>(const Datum* datum)
	{
		datum;
		RETURN_WIDE_STRING("lmao const");
	}

	template<>
	std::wstring ToString<Datum::DatumTypes>(const Datum::DatumTypes& datumType)
	{
		RETURN_WIDE_STRING(static_cast<size_t>(datumType));
	}

	template<>
	std::wstring ToString<Scope>(Scope* scope)
	{
		scope;
		RETURN_WIDE_STRING("scopium");
	}

	template<>
	std::wstring ToString<Scope>(const Scope* scope)
	{
		scope;
		RETURN_WIDE_STRING("scopium const");
	}
}