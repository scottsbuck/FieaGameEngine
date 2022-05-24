#pragma once
#include "Foo.h"
#include "CppUnitTest.h"
#include "JsonParseCoordinator.h"
#include "JsonTestParseHelper.h"
#include "JsonIntegerParseHelper.h"
#include "JsonTableParseHelper.h"
#include "json\json.h"
#include "Factory.h"
#include "AttributedFoo.h"
#include "GameObject.h"
#include "Avatar.h"
#include "Action.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionIncrement.h"
#include "ActionList.h"
#include "ActionListIf.h"
#include <stdexcept>
#include <crtdbg.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std::string_literals;
using namespace FieaGameEngine;
using namespace LibraryDesktopUnitTests;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	std::wstring ToString<glm::mat4>(const glm::mat4&)
	{
		RETURN_WIDE_STRING("ugh");
	}

	template<>
	std::wstring ToString<glm::vec4>(const glm::vec4&)
	{
		RETURN_WIDE_STRING("bruh");
	}

	template<>
	std::wstring ToString<FactoryScope>(const FactoryScope*)
	{
		RETURN_WIDE_STRING("Gottem captain");
	}

	template<>
	std::wstring ToString<FactoryAttributedFoo>(const FactoryAttributedFoo*)
	{
		RETURN_WIDE_STRING("Sadge");
	}

	template<>
	std::wstring ToString<FactoryGameObject>(const FactoryGameObject*)
	{
		RETURN_WIDE_STRING("LameObject");
	}

	template<>
	std::wstring ToString<FactoryAvatar>(const FactoryAvatar*)
	{
		RETURN_WIDE_STRING("Badatar");
	}

	template<>
	std::wstring ToString<FactoryActionCreateAction>(const FactoryActionCreateAction*)
	{
		RETURN_WIDE_STRING("aca");
	}

	template<>
	std::wstring ToString<FactoryActionDestroyAction>(const FactoryActionDestroyAction*)
	{
		RETURN_WIDE_STRING("ada");
	}

	template<>
	std::wstring ToString<FactoryActionIncrement>(const FactoryActionIncrement*)
	{
		RETURN_WIDE_STRING("actionIncrement");
	}

	template<>
	std::wstring ToString<FactoryActionList>(const FactoryActionList*)
	{
		RETURN_WIDE_STRING("actionlsit");
	}

	template<>
	std::wstring ToString<FactoryActionListIf>(const FactoryActionListIf*)
	{
		RETURN_WIDE_STRING("actionlistif");
	}
}