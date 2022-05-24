#include "pch.h"
#include "CppUnitTest.h"
#include "ToStringSpecializationsAction.h"
#include "Action.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionIncrement.h"
#include "ActionList.h"
#include "ActionListIf.h"
#include "JsonTestParseHelper.h"
#include "JsonIntegerParseHelper.h"
#include "JsonTableParseHelper.h"
#include "json\json.h"
#include "AttributedFoo.h"
#include "Factory.h"
#include "GameObject.h"
#include "Avatar.h"
#include <stdexcept>
#include <crtdbg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopUnitTests
{
	TEST_CLASS(ActionTests)
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

		TEST_METHOD(Parser)
		{
			JsonTableParseHelper::SharedData sharedData;
			JsonParseCoordinator parser(sharedData);

			JsonTableParseHelper tableParseHelper;
			Assert::AreEqual(size_t(0), parser.Helpers().Size());
			parser.AddHelper(tableParseHelper);
			Assert::AreEqual(size_t(1), parser.Helpers().Size());

			parser.Initialize();

			const FactoryScope scopeFactory;
			const FactoryAttributedFoo afFactory;
			const FactoryGameObject gameObjectFactory;
			const FactoryAvatar avatarFactory;
			const FactoryActionCreateAction acaFactory;
			const FactoryActionDestroyAction adaFactory;
			const FactoryActionIncrement actionIncrementFactory;
			const FactoryActionList actionListFactory;
			const FactoryActionListIf actionListIfFactory;

			Assert::AreEqual(size_t(9), Factory<Scope>::GetFactories().Size());

			const Factory<Scope>* foundFactory;

			foundFactory = Factory<Scope>::Find("Scope");
			Assert::AreEqual(&scopeFactory, static_cast<const FactoryScope*>(foundFactory));

			foundFactory = Factory<Scope>::Find("AttributedFoo");
			Assert::AreEqual(&afFactory, static_cast<const FactoryAttributedFoo*>(foundFactory));

			foundFactory = Factory<Scope>::Find("GameObject");
			Assert::AreEqual(&gameObjectFactory, static_cast<const FactoryGameObject*>(foundFactory));

			foundFactory = Factory<Scope>::Find("Avatar");
			Assert::AreEqual(&avatarFactory, static_cast<const FactoryAvatar*>(foundFactory));

			foundFactory = Factory<Scope>::Find("ActionCreateAction");
			Assert::AreEqual(&acaFactory, static_cast<const FactoryActionCreateAction*>(foundFactory));

			foundFactory = Factory<Scope>::Find("ActionDestroyAction");
			Assert::AreEqual(&adaFactory, static_cast<const FactoryActionDestroyAction*>(foundFactory));

			foundFactory = Factory<Scope>::Find("ActionIncrement");
			Assert::AreEqual(&actionIncrementFactory, static_cast<const FactoryActionIncrement*>(foundFactory));

			foundFactory = Factory<Scope>::Find("ActionList");
			Assert::AreEqual(&actionListFactory, static_cast<const FactoryActionList*>(foundFactory));

			foundFactory = Factory<Scope>::Find("ActionListIf");
			Assert::AreEqual(&actionListIfFactory, static_cast<const FactoryActionListIf*>(foundFactory));

			parser.ParseObjectFromFile("Content/TestScope.json");

			Assert::AreEqual("Test Name", sharedData.GetData().Find("Name")->GetString().c_str());
			Assert::AreEqual(100, sharedData.GetData().Find("Health")->GetInt());
			Assert::AreEqual(glm::vec4(1, 0, 0, 1), sharedData.GetData().Find("Direction")->GetVector());
			Assert::AreEqual(glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), sharedData.GetData().Find("Transform")->GetMatrix());
			Assert::AreEqual("Bob", sharedData.GetData().Find("Aliases")->GetString(0).c_str());
			Assert::AreEqual("Jim", sharedData.GetData().Find("Aliases")->GetString(1).c_str());
			Assert::AreEqual("Fred", sharedData.GetData().Find("Aliases")->GetString(2).c_str());
			Assert::AreEqual("123 Anystreet St.", sharedData.GetData().Find("Address")->GetScope()->Find("Street")->GetString().c_str());
			Assert::AreEqual("Orlando", sharedData.GetData().Find("Address")->GetScope()->Find("City")->GetString().c_str());
			Assert::AreEqual(12345, sharedData.GetData().Find("Address")->GetScope()->Find("Postal Code")->GetScope()->Find("Zip Code")->GetInt());
			Assert::AreEqual(6789, sharedData.GetData().Find("Address")->GetScope()->Find("Postal Code")->GetScope()->Find("Zip Code+4")->GetInt());
			Assert::AreEqual("Laser Vision", sharedData.GetData().Find("Powers")->GetScope()->Find("Powers")->GetScope(0)->Find("Name")->GetString().c_str());
			Assert::AreEqual(1.5f, sharedData.GetData().Find("Powers")->GetScope()->Find("Powers")->GetScope(0)->Find("Dps")->GetFloat());
			Assert::AreEqual("Big daddy strength", sharedData.GetData().Find("Powers")->GetScope()->Find("Powers")->GetScope(1)->Find("Name")->GetString().c_str());
			Assert::AreEqual(420.69f, sharedData.GetData().Find("Powers")->GetScope()->Find("Powers")->GetScope(1)->Find("Dps")->GetFloat());
			Assert::AreEqual("Please god work", sharedData.GetData().Find("AAtributedTest")->GetScope()->Find("GamersRiseUp")->GetString().c_str());

			Assert::IsNotNull(sharedData.GetData().Find("AAtributedTest")->GetScope());
			AttributedFoo* af = sharedData.GetData().Find("AAtributedTest")->GetScope()->As<AttributedFoo>();
			Assert::IsNotNull(af);

			GameTime gameTimeObject;

			sharedData.GetData().Find("AAAAvatar")->GetScope()->As<Avatar>()->Update(gameTimeObject);
			Assert::AreEqual(sharedData.GetData().Find("AAAAvatar")->GetScope()->Find("HitPoints")->GetInt(), 90);
			Assert::AreEqual(sharedData.GetData().Find("AAAAvatar")->GetScope()->Find("Children")->GetScope()->Find("Children")->GetScope(0)->Find("HitPoints")->GetInt(), 90);
			Assert::AreEqual(sharedData.GetData().Find("AAAAvatar")->GetScope()->Find("Children")->GetScope()->Find("Children")->GetScope(1)->Find("HitPoints")->GetInt(), 90);

			Assert::AreEqual(sharedData.GetData().Find("ActionTimeGamer")->GetScope()->Find("MovementSpeed")->GetFloat(), 2.5f);
			sharedData.GetData().Find("ActionTimeGamer")->GetScope()->As<Avatar>()->Update(gameTimeObject);
			Assert::AreEqual(sharedData.GetData().Find("ActionTimeGamer")->GetScope()->Find("MovementSpeed")->GetFloat(), 5.0f);
			sharedData.GetData().Find("ActionTimeGamer")->GetScope()->As<Avatar>()->Update(gameTimeObject);
			Assert::AreEqual(sharedData.GetData().Find("ActionTimeGamer")->GetScope()->Find("MovementSpeed")->GetFloat(), 6.5f);

			sharedData.GetData().Find("ActionListGaming")->GetScope()->As<ActionList>()->Update(gameTimeObject);
			Assert::AreEqual("DestroyThePepegas", sharedData.GetData().Find("ActionListGaming")->GetScope()->Find("Actions")->GetScope()->Find("Actions")->GetScope(0)->Find("Name")->GetString().c_str());
		}

	private:
		static _CrtMemState startMemState;
	};
	_CrtMemState ActionTests::startMemState;
}