#pragma once

#include "Foo.h"
#include "CppUnitTest.h"
#include "JsonParseCoordinator.h"
#include "ToStringSpecializationsJson.h"
#include "JsonTestParseHelper.h"
#include "JsonIntegerParseHelper.h"
#include "JsonTableParseHelper.h"
#include "json\json.h"
#include "Factory.h"
#include "AttributedFoo.h"
#include "GameObject.h"
#include "Avatar.h"
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
	std::wstring ToString<JsonParseCoordinator>(JsonParseCoordinator* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	std::wstring ToString<JsonParseCoordinator::SharedData>(JsonParseCoordinator::SharedData* t)
	{
		t;
		RETURN_WIDE_STRING("lmao");
	}

	template<>
	std::wstring ToString<JsonTestParseHelper::SharedData>(JsonTestParseHelper::SharedData* t)
	{
		t;
		RETURN_WIDE_STRING("lmao");
	}

	template<>
	std::wstring ToString<JsonTestParseHelper>(JsonTestParseHelper* t)
	{
		t;
		RETURN_WIDE_STRING("lmao");
	}

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
}