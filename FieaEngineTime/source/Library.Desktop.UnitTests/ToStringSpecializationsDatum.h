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
	std::wstring ToString<Datum::DatumTypes>(const Datum::DatumTypes& datumType)
	{
		RETURN_WIDE_STRING(static_cast<size_t>(datumType));
	}

	template<>
	std::wstring ToString<glm::mat4>(const glm::mat4& matrix)
	{
		RETURN_WIDE_STRING(matrix[0][0]);
	}

	template<>
	std::wstring ToString<glm::vec4>(const glm::vec4& vector)
	{
		RETURN_WIDE_STRING(vector[0]);
	}

	template<>
	std::wstring ToString<RTTI>(RTTI* rttiPtr)
	{
		RETURN_WIDE_STRING(rttiPtr->ToString().c_str());
	}
}