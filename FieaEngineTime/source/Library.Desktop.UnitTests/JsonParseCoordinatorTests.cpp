#include "pch.h"
#include "CppUnitTest.h"
#include "JsonParseCoordinator.h"
#include "ToStringSpecializationsJson.h"
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
#include <fstream>
#include <iostream>
#include <string>
#include <gsl/pointers>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std::string_literals;

namespace LibraryDesktopUnitTests
{
	TEST_CLASS(JsonParseCoordinatorTests)
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

		//TEST_METHOD(JsonParseTestHelperRTTI)
		//{

		//}

		TEST_METHOD(Constructor)
		{
			JsonTestParseHelper::SharedData data;
			JsonParseCoordinator parser(data);
			
			Assert::AreEqual(&data, parser.GetSharedData()->As<JsonTestParseHelper::SharedData>());

			JsonTestParseHelper testParseHelper;
			parser.AddHelper(testParseHelper);
			
			Assert::AreEqual(&data, parser.GetSharedData()->As<JsonTestParseHelper::SharedData>());
			Assert::AreEqual(&parser, data.GetJsonParseCoordinator());

			JsonTestParseHelper::SharedData anotherSharedData;
			parser.SetSharedData(&anotherSharedData);
			Assert::AreEqual(&anotherSharedData, parser.GetSharedData()->As<JsonTestParseHelper::SharedData>());
		}

		TEST_METHOD(MoveSemantics)
		{
			JsonTestParseHelper::SharedData sharedData;
			JsonTestParseHelper testParseHelper;

			{
				JsonParseCoordinator parser(sharedData);
				parser.AddHelper(testParseHelper);

				JsonParseCoordinator otherParser = std::move(parser);
				Assert::AreEqual(&sharedData, otherParser.GetSharedData()->As<JsonTestParseHelper::SharedData>());
				Assert::AreEqual(&otherParser, sharedData.GetJsonParseCoordinator());
			}

			{
				JsonParseCoordinator parser(sharedData);
				parser.AddHelper(testParseHelper);

				JsonTestParseHelper::SharedData otherSharedData;
				JsonParseCoordinator otherParser(otherSharedData);
				otherParser = std::move(parser);
				Assert::AreEqual(&sharedData, otherParser.GetSharedData()->As<JsonTestParseHelper::SharedData>());
				Assert::AreEqual(&otherParser, sharedData.GetJsonParseCoordinator());
			}
		}

		TEST_METHOD(ParseFromString)
		{
			const std::string inputString = R"(
			{
				"Address":
				{
					"type": "table",
					"value":
					{
						"Street":
						{
							"type": "string",
							"value": "123 Anystreet St."
						}
					}
				}
			})";


			JsonTestParseHelper::SharedData sharedData;
			JsonTestParseHelper testParseHelper;
			JsonParseCoordinator parser(sharedData);
			parser.AddHelper(testParseHelper);

			Assert::IsFalse(testParseHelper.InitializeCalled);
			parser.Initialize();
			Assert::IsTrue(testParseHelper.InitializeCalled);

			Assert::AreEqual(size_t(0), testParseHelper.startHandlerCount);
			Assert::AreEqual(size_t(0), testParseHelper.endHandlerCount);
			Assert::AreEqual(size_t(0), sharedData.Depth());
			Assert::AreEqual(size_t(0), sharedData.maxDepth);

			parser.ParseObject(inputString);

			Assert::AreEqual(size_t(6), testParseHelper.startHandlerCount);
			Assert::AreEqual(size_t(6), testParseHelper.endHandlerCount);
			Assert::AreEqual(size_t(0), sharedData.Depth());
			Assert::AreEqual(size_t(4), sharedData.maxDepth);
		}

		TEST_METHOD(ParseFromStream)
		{
			std::stringstream inputStream;
			inputStream << R"({"integer": 5})";

			JsonTestParseHelper::SharedData sharedData;
			JsonTestParseHelper testParseHelper;
			JsonParseCoordinator parser(sharedData);
			parser.AddHelper(testParseHelper);

			Assert::IsFalse(testParseHelper.InitializeCalled);
			parser.Initialize();
			Assert::IsTrue(testParseHelper.InitializeCalled);

			parser.ParseObject(inputStream);

			Assert::AreEqual(size_t(1), testParseHelper.startHandlerCount);
			Assert::AreEqual(size_t(1), testParseHelper.endHandlerCount);
			Assert::AreEqual(size_t(0), sharedData.Depth());
			Assert::AreEqual(size_t(1), sharedData.maxDepth);
		}

		TEST_METHOD(FileParsing)
		{
			const std::string filename = "Content/TestFile.json";
			const std::string inputString = R"({"Health": { "type": "integer", "value": 100} })";

			std::ofstream outputFile(filename);
			Assert::IsTrue(outputFile.good());

			outputFile << inputString;
			outputFile.close();

			JsonTestParseHelper::SharedData sharedData;
			JsonTestParseHelper testParseHelper;
			JsonParseCoordinator parser(sharedData);
			parser.AddHelper(testParseHelper);

			Assert::IsFalse(testParseHelper.InitializeCalled);
			parser.Initialize();
			Assert::IsTrue(testParseHelper.InitializeCalled);

			parser.ParseObjectFromFile(filename);

			Assert::AreEqual(size_t(3), testParseHelper.startHandlerCount);
			Assert::AreEqual(size_t(3), testParseHelper.endHandlerCount);
			Assert::AreEqual(size_t(0), sharedData.Depth());
			Assert::AreEqual(size_t(2), sharedData.maxDepth);
		}

		TEST_METHOD(Clone)
		{
			JsonTestParseHelper::SharedData sharedData;
			JsonTestParseHelper testParseHelper;
			JsonParseCoordinator parser(sharedData);
			Assert::IsFalse(parser.IsClone());
			parser.AddHelper(testParseHelper);

			JsonIntegerParseHelper integerParseHelper;
			parser.AddHelper(integerParseHelper);

			auto clone = parser.Clone();
			Assert::AreNotEqual(clone, &parser);
			Assert::IsTrue(clone->IsClone());
			Assert::AreEqual(size_t(2), clone->Helpers().Size());


			auto clonedHelper = clone->Helpers()[0]->As<JsonTestParseHelper>();
			Assert::IsNotNull(clonedHelper);
			Assert::AreNotEqual(clonedHelper, parser.Helpers()[0]->As<JsonTestParseHelper>());
			Assert::AreNotSame(clone->GetSharedData(), parser.GetSharedData());

			Assert::ExpectException<std::runtime_error>([&clone] {JsonTestParseHelper helper; clone->AddHelper(helper); });

			clone->RemoveHelper(*clonedHelper);
			Assert::AreEqual(size_t(1), clone->Helpers().Size());

			delete clone;
		}

		TEST_METHOD(ParsingInvalidJson)
		{
			JsonTestParseHelper::SharedData sharedData;
			JsonTestParseHelper testParseHelper;
			JsonParseCoordinator parser(sharedData);
			parser.AddHelper(testParseHelper);

			Assert::ExpectException<std::exception>([&parser]
			{
				const std::string inputString = R"({"integer": { 100 } })";
				parser.ParseObject(inputString);
			});
		}

		TEST_METHOD(IntegerParsing)
		{
			std::string inputString = R"({"integer": 100})";

			JsonIntegerParseHelper::SharedData sharedData;
			JsonIntegerParseHelper integerParseHelper;
			JsonParseCoordinator parser(sharedData);
			parser.AddHelper(integerParseHelper);

			parser.ParseObject(inputString);
			Assert::AreEqual(size_t(1), sharedData.data.Size());
			Assert::AreEqual(100, sharedData.data.Front());
		}

		TEST_METHOD(IntegerArrayParsing)
		{
			std::string inputString = R"({ "integer": [ 10, 20, 30, 40 ] })";

			JsonIntegerParseHelper::SharedData sharedData;
			JsonIntegerParseHelper integerParseHelper;
			JsonParseCoordinator parser(sharedData);
			parser.AddHelper(integerParseHelper);

			parser.ParseObject(inputString);
			Assert::AreEqual(size_t(4), sharedData.data.Size());
			Assert::AreEqual(10, sharedData.data[0]);
			Assert::AreEqual(20, sharedData.data[1]);
			Assert::AreEqual(30, sharedData.data[2]);
			Assert::AreEqual(40, sharedData.data[3]);
		}

		TEST_METHOD(ValueArrayParsing)
		{
			std::string inputString = R"({ "integer": [ 10, 20, 30 ] })";

			JsonTestParseHelper::SharedData sharedData;
			JsonTestParseHelper testParseHelper;
			JsonParseCoordinator parser(sharedData);
			parser.AddHelper(testParseHelper);

			Assert::IsFalse(testParseHelper.InitializeCalled);
			parser.Initialize();
			Assert::IsTrue(testParseHelper.InitializeCalled);

			Assert::AreEqual(size_t(0), testParseHelper.startHandlerCount);
			Assert::AreEqual(size_t(0), testParseHelper.endHandlerCount);
			Assert::AreEqual(size_t(0), sharedData.Depth());
			Assert::AreEqual(size_t(0), sharedData.maxDepth);

			parser.ParseObject(inputString);

			Assert::AreEqual(size_t(3), testParseHelper.startHandlerCount);
			Assert::AreEqual(size_t(3), testParseHelper.endHandlerCount);
			Assert::AreEqual(size_t(0), sharedData.Depth());
			Assert::AreEqual(size_t(1), sharedData.maxDepth);
		}

		TEST_METHOD(ObjectArrayParsing)
		{
			const std::string inputString = R"(
			{
				"Objects":
				[
					{
						"1": 1,
						"2": 1,
						"3": 1,
						"4": 1
					},
					{ "2": 2 },
					{ "3": 3 }
				]
			})";

			JsonTestParseHelper::SharedData sharedData;
			JsonTestParseHelper testParseHelper;
			JsonParseCoordinator parser(sharedData);
			parser.AddHelper(testParseHelper);

			Assert::IsFalse(testParseHelper.InitializeCalled);
			parser.Initialize();
			Assert::IsTrue(testParseHelper.InitializeCalled);

			Assert::AreEqual(size_t(0), testParseHelper.startHandlerCount);
			Assert::AreEqual(size_t(0), testParseHelper.endHandlerCount);
			Assert::AreEqual(size_t(0), sharedData.Depth());
			Assert::AreEqual(size_t(0), sharedData.maxDepth);

			parser.ParseObject(inputString);

			Assert::AreEqual(size_t(6), testParseHelper.startHandlerCount);
			Assert::AreEqual(size_t(6), testParseHelper.endHandlerCount);
			Assert::AreEqual(size_t(0), sharedData.Depth());
			Assert::AreEqual(size_t(2), sharedData.maxDepth);
		}

		TEST_METHOD(AddRemoveHelpers)
		{
			JsonTestParseHelper::SharedData sharedData;
			JsonParseCoordinator parser(sharedData);

			JsonTestParseHelper testParseHelper;
			Assert::AreEqual(size_t(0), parser.Helpers().Size());
			parser.AddHelper(testParseHelper);
			Assert::AreEqual(size_t(1), parser.Helpers().Size());

			parser.AddHelper(testParseHelper);
			Assert::AreEqual(size_t(1), parser.Helpers().Size());

			JsonTestParseHelper helper; 
			parser.AddHelper(helper);
			Assert::AreEqual(size_t(1), parser.Helpers().Size());

			JsonIntegerParseHelper integerParseHelper;
			parser.AddHelper(integerParseHelper);
			Assert::AreEqual(size_t(2), parser.Helpers().Size());

			parser.RemoveHelper(testParseHelper);
			Assert::AreEqual(size_t(1), parser.Helpers().Size());

			parser.RemoveHelper(integerParseHelper);
			Assert::AreEqual(size_t(0), parser.Helpers().Size());
		}

		TEST_METHOD(JsonTableParser)
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

			Assert::AreEqual(size_t(4), Factory<Scope>::GetFactories().Size());

			const Factory<Scope>* foundFactory;

			foundFactory = Factory<Scope>::Find("Scope");
			Assert::AreEqual(&scopeFactory, static_cast<const FactoryScope*>(foundFactory));

			foundFactory = Factory<Scope>::Find("AttributedFoo");
			Assert::AreEqual(&afFactory, static_cast<const FactoryAttributedFoo*>(foundFactory));

			foundFactory = Factory<Scope>::Find("GameObject");
			Assert::AreEqual(&gameObjectFactory, static_cast<const FactoryGameObject*>(foundFactory));

			foundFactory = Factory<Scope>::Find("Avatar");
			Assert::AreEqual(&avatarFactory, static_cast<const FactoryAvatar*>(foundFactory));

			parser.ParseObjectFromFile("Content/TestJsonParser.json");

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

		}

	private:
		static _CrtMemState startMemState;
	};
	_CrtMemState JsonParseCoordinatorTests::startMemState;
}