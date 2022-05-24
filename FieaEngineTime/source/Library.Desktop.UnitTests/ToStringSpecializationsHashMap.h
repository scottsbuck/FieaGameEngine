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
	std::wstring ToString<std::pair<Foo, int>>(const std::pair<Foo, int>& pair)
	{
		try
		{
			return ToString((pair.first).Data());
		}
		catch (const std::exception&)
		{
			return L"end()"s;
		}
	}

	//template<>
	//std::wstring ToString<std::pair<Foo, int>>(const std::pair<Foo, int>* pair)
	//{
	//	try
	//	{
	//		return ToString((pair->first).Data());
	//	}
	//	catch (const std::exception&)
	//	{
	//		return L"end()"s;
	//	}
	//}

	template<>
	std::wstring ToString<HashMap<Foo, int>::Iterator>(const HashMap<Foo, int>::Iterator& t)
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
	std::wstring ToString<HashMap<Foo, int>::ConstIterator>(const HashMap<Foo, int>::ConstIterator& t)
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

	//template<>
	//std::wstring ToString<SList<Foo>::ConstIterator>(const SList<Foo>::ConstIterator& t)
	//{
	//	try
	//	{
	//		return ToString(*t);
	//	}
	//	catch (const std::exception&)
	//	{
	//		return L"end()"s;
	//	}
	//}
}