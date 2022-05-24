#include "pch.h"
#include "CppUnitTest.h"
#include "Datum.h"
#include "Foo.h"
#include "ToStringSpecializationsDatum.h"
#include <stdexcept>
#include <crtdbg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopUnitTests
{
	TEST_CLASS(DatumTests)
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

		TEST_METHOD(Constructor)
		{
			{
				Datum datum = 4;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetInt(0), 4);
			}

			{
				Datum datum = 4.0f;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Float);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetFloat(0), 4.0f);
			}

			{
				glm::vec4 vector(4.0f, 4.0f, 4.0f, 4.0f);
				Datum datum = vector;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Vector);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetVector(0), vector);
			}

			{
				glm::mat4 matrix(4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f);
				Datum datum = matrix;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Matrix);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetMatrix(0), matrix);
			}

			{
				std::string string = "Gaming";
				Datum datum = string;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::String);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetString(), string);
			}

			{
				Foo foo{ 10 };
				RTTI* rtti = &foo;
				Datum datum = rtti;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Pointer);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetRTTI(), rtti);
			}

			{
				Datum datum(Datum::DatumTypes::Integer);
				Assert::AreEqual(datum.Size(), size_t(0));
				Assert::AreEqual(datum.Capacity(), size_t(0));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
				Assert::AreEqual(datum.IsExternal(), false);
			}

			{
				Datum datum;
				Assert::AreEqual(datum.Size(), size_t(0));
				Assert::AreEqual(datum.Capacity(), size_t(0));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Unknown);
				Assert::AreEqual(datum.IsExternal(), false);
			}
		}

		TEST_METHOD(Copy)
		{
			{
				Datum datum;
				Assert::AreEqual(datum.Size(), size_t(0));
				Assert::AreEqual(datum.Capacity(), size_t(0));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Unknown);
				Assert::AreEqual(datum.IsExternal(), false);

				datum.PushBack(4);
				datum.PushBack(8);
				datum.PushBack(12);
				Assert::AreEqual(datum.Size(), size_t(3));
				Assert::AreEqual(datum.Capacity(), size_t(4));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetInt(0), 4);
				Assert::AreEqual(datum.GetInt(1), 8);
				Assert::AreEqual(datum.GetInt(2), 12);

				{
					Datum datum2(datum);
					Assert::AreEqual(datum2.Size(), size_t(3));
					Assert::AreEqual(datum2.Capacity(), size_t(4));
					Assert::AreEqual(datum2.Type(), Datum::DatumTypes::Integer);
					Assert::AreEqual(datum2.IsExternal(), false);
					Assert::AreEqual(datum2.GetInt(0), 4);
					Assert::AreEqual(datum2.GetInt(1), 8);
					Assert::AreEqual(datum2.GetInt(2), 12);
				}

				{
					Datum datum2;
					datum2 = datum;
					Assert::AreEqual(datum2.Size(), size_t(3));
					Assert::AreEqual(datum2.Capacity(), size_t(4));
					Assert::AreEqual(datum2.Type(), Datum::DatumTypes::Integer);
					Assert::AreEqual(datum2.IsExternal(), false);
					Assert::AreEqual(datum2.GetInt(0), 4);
					Assert::AreEqual(datum2.GetInt(1), 8);
					Assert::AreEqual(datum2.GetInt(2), 12);
				}
			}

			{
				Datum datum;
				Assert::AreEqual(datum.Size(), size_t(0));
				Assert::AreEqual(datum.Capacity(), size_t(0));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Unknown);
				Assert::AreEqual(datum.IsExternal(), false);

				datum.PushBack("Hello");
				datum.PushBack("Darkness");
				datum.PushBack("MyOldFriend");
				Assert::AreEqual(datum.Size(), size_t(3));
				Assert::AreEqual(datum.Capacity(), size_t(4));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::String);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetString(0), std::string("Hello"));
				Assert::AreEqual(datum.GetString(1), std::string("Darkness"));
				Assert::AreEqual(datum.GetString(2), std::string("MyOldFriend"));

				{
					Datum datum2(datum);
					Assert::AreEqual(datum2.Size(), size_t(3));
					Assert::AreEqual(datum2.Capacity(), size_t(4));
					Assert::AreEqual(datum2.Type(), Datum::DatumTypes::String);
					Assert::AreEqual(datum2.IsExternal(), false);
					Assert::AreEqual(datum2.GetString(0), std::string("Hello"));
					Assert::AreEqual(datum2.GetString(1), std::string("Darkness"));
					Assert::AreEqual(datum2.GetString(2), std::string("MyOldFriend"));
				}

				{
					Datum datum2;
					datum2 = datum;
					Assert::AreEqual(datum2.Size(), size_t(3));
					Assert::AreEqual(datum2.Capacity(), size_t(4));
					Assert::AreEqual(datum2.Type(), Datum::DatumTypes::String);
					Assert::AreEqual(datum2.IsExternal(), false);
					Assert::AreEqual(datum2.GetString(0), std::string("Hello"));
					Assert::AreEqual(datum2.GetString(1), std::string("Darkness"));
					Assert::AreEqual(datum2.GetString(2), std::string("MyOldFriend"));
				}
			}

			{
				{
					int32_t intArray[3] = { 4, 8, 12 };

					Datum datum;
					datum.SetStorage(intArray, 3);
					Assert::AreEqual(datum.Size(), size_t(3));
					Assert::AreEqual(datum.Capacity(), size_t(3));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
					Assert::AreEqual(datum.IsExternal(), true);
					Assert::AreEqual(datum.GetInt(0), 4);
					Assert::AreEqual(datum.GetInt(1), 8);
					Assert::AreEqual(datum.GetInt(2), 12);

					{
						Datum datum2(datum);
						Assert::AreEqual(datum2.Size(), size_t(3));
						Assert::AreEqual(datum2.Capacity(), size_t(3));
						Assert::AreEqual(datum2.Type(), Datum::DatumTypes::Integer);
						Assert::AreEqual(datum2.IsExternal(), true);
						Assert::AreEqual(datum2.GetInt(0), 4);
						Assert::AreEqual(datum2.GetInt(1), 8);
						Assert::AreEqual(datum2.GetInt(2), 12);
					}

					{
						int32_t intArray2[4] = { 6, 12, 18, 24};
						Datum datum2;
						datum2.SetStorage(intArray2, 4);
						datum2 = datum;
						Assert::AreEqual(datum2.Size(), size_t(3));
						Assert::AreEqual(datum2.Capacity(), size_t(3));
						Assert::AreEqual(datum2.Type(), Datum::DatumTypes::Integer);
						Assert::AreEqual(datum2.IsExternal(), true);
						Assert::AreEqual(datum2.GetInt(0), 4);
						Assert::AreEqual(datum2.GetInt(1), 8);
						Assert::AreEqual(datum2.GetInt(2), 12);

						Datum datum3;
						datum3.PushBack(5);
						datum3.PushBack(10);
						Assert::AreEqual(datum3.Size(), size_t(2));
						Assert::AreEqual(datum3.Capacity(), size_t(2));
						Assert::AreEqual(datum3.Type(), Datum::DatumTypes::Integer);
						Assert::AreEqual(datum3.IsExternal(), false);
						Assert::AreEqual(datum3.GetInt(0), 5);
						Assert::AreEqual(datum3.GetInt(1), 10);

						datum2 = datum3;
						Assert::AreEqual(datum2.Size(), size_t(2));
						Assert::AreEqual(datum2.Capacity(), size_t(2));
						Assert::AreEqual(datum2.Type(), Datum::DatumTypes::Integer);
						Assert::AreEqual(datum2.IsExternal(), false);
						Assert::AreEqual(datum2.GetInt(0), 5);
						Assert::AreEqual(datum2.GetInt(1), 10);
 					}
				}
			}
		}

		TEST_METHOD(AssignmentOperators)
		{
			{
				Datum datum;
				datum = 4;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetInt(0), 4);
			}

			{
				Datum datum;
				datum = 4.0f;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Float);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetFloat(0), 4.0f);
			}

			{
				glm::vec4 vector(4.0f, 4.0f, 4.0f, 4.0f);
				Datum datum;
				datum = vector;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Vector);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetVector(0), vector);
			}

			{
				glm::mat4 matrix(4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f);
				Datum datum;
				datum = matrix;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Matrix);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetMatrix(0), matrix);
			}

			{
				std::string string = "Gaming";
				Datum datum;
				datum = string;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::String);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetString(), string);
			}

			{
				Foo foo{ 10 };
				RTTI* rtti = &foo;
				Datum datum;
				datum = rtti;
				Assert::AreEqual(datum.Size(), size_t(1));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Pointer);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetRTTI(), rtti);
			}
		}

		TEST_METHOD(MoveSemantics)	
		{
			{
				Datum datum = 4;
				Datum datum2(std::move(datum));
				Assert::AreEqual(datum2.Size(), size_t(1));
				Assert::AreEqual(datum2.Capacity(), size_t(1));
				Assert::AreEqual(datum2.Type(), Datum::DatumTypes::Integer);
				Assert::AreEqual(datum2.IsExternal(), false);
				Assert::AreEqual(datum2.GetInt(0), 4);
			}

			{
				Datum datum = 4;
				Datum datum2;
				datum2 = std::move(datum);
				Assert::AreEqual(datum2.Size(), size_t(1));
				Assert::AreEqual(datum2.Capacity(), size_t(1));
				Assert::AreEqual(datum2.Type(), Datum::DatumTypes::Integer);
				Assert::AreEqual(datum2.IsExternal(), false);
				Assert::AreEqual(datum2.GetInt(0), 4);
			}
		}

		TEST_METHOD(SetType)
		{
			Datum datum;
			datum.SetType(Datum::DatumTypes::Integer);
			Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
			datum.PushBack(4);

			auto setType = [&datum]()
			{
				datum.SetType(Datum::DatumTypes::Float);
			};
			Assert::ExpectException<std::runtime_error>(setType);
		}

		TEST_METHOD(Resize)	
		{
			{
				Datum datum;

				auto unknown = [&datum]()
				{
					datum.Resize(3);
				};
				Assert::ExpectException<std::runtime_error>(unknown);

				int32_t intArray[3] = { 4, 8, 12 };
				datum.SetStorage(intArray, 3);

				auto external = [&datum]()
				{
					datum.Resize(3);
				};
				Assert::ExpectException<std::runtime_error>(external);
			}

			{
				Datum datum = 4;
				datum.Resize(4);
				Assert::AreEqual(datum.Size(), size_t(4));
				Assert::AreEqual(datum.Capacity(), size_t(4));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetInt(0), 4);
				Assert::AreEqual(datum.GetInt(1), 0);
				Assert::AreEqual(datum.GetInt(2), 0);
				Assert::AreEqual(datum.GetInt(3), 0);
			}

			{
				Datum datum = "LMAO";
				datum.Resize(4);
				Assert::AreEqual(datum.Size(), size_t(4));
				Assert::AreEqual(datum.Capacity(), size_t(4));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::String);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetString(0), std::string("LMAO"));
				Assert::AreEqual(datum.GetString(1), std::string(""));
				Assert::AreEqual(datum.GetString(2), std::string(""));
				Assert::AreEqual(datum.GetString(3), std::string(""));
			}

			{
				Datum datum;
				datum.PushBack(4);
				datum.PushBack(8);
				datum.PushBack(12);
				datum.PushBack(16);
				datum.Resize(2);
				Assert::AreEqual(datum.Size(), size_t(2));
				Assert::AreEqual(datum.Capacity(), size_t(2));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetInt(0), 4);
				Assert::AreEqual(datum.GetInt(1), 8);
			}

			{
				Datum datum;
				datum.PushBack("wtf");
				datum.PushBack("cracked");
				datum.PushBack("gaming");
				datum.PushBack("gottem");
				datum.Resize(2);
				Assert::AreEqual(datum.Size(), size_t(2));
				Assert::AreEqual(datum.Capacity(), size_t(2));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::String);
				Assert::AreEqual(datum.IsExternal(), false);
				Assert::AreEqual(datum.GetString(0), std::string("wtf"));
				Assert::AreEqual(datum.GetString(1), std::string("cracked"));
			}
		}

		TEST_METHOD(Clear)
		{
			{
				Datum datum;
				int32_t intArray[3] = { 4, 8, 12 };
				datum.SetStorage(intArray, 3);

				auto clear = [&datum]()
				{
					datum.Clear();
				};
				Assert::ExpectException<std::runtime_error>(clear);
			}

			{
				Datum datum;
				datum.PushBack("wtf");
				datum.PushBack("cracked");
				datum.PushBack("gaming");
				datum.PushBack("gottem");

				datum.Clear();
				Assert::AreEqual(datum.Size(), size_t(0));
				Assert::AreEqual(datum.Capacity(), size_t(4));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::String);
				Assert::AreEqual(datum.IsExternal(), false);
			}
		}

		TEST_METHOD(SetStorage)
		{
			{
				Datum datum;
				int32_t intArray[3] = { 4, 8, 12 };
				datum.SetStorage(intArray, 3);
				Assert::AreEqual(datum.Size(), size_t(3));
				Assert::AreEqual(datum.Capacity(), size_t(3));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
				Assert::AreEqual(datum.IsExternal(), true);
				Assert::AreEqual(datum.GetInt(0), 4);
				Assert::AreEqual(datum.GetInt(1), 8);
				Assert::AreEqual(datum.GetInt(2), 12);

				auto allocated = [&datum, &intArray]()
				{
					datum.SetStorage(intArray, 3);
				};
				Assert::ExpectException<std::runtime_error>(allocated);
			}

			{
				Datum datum;
				float floatArray[3] = { 4.0f, 8.0f, 12.0f };
				datum.SetStorage(floatArray, 3);
				Assert::AreEqual(datum.Size(), size_t(3));
				Assert::AreEqual(datum.Capacity(), size_t(3));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Float);
				Assert::AreEqual(datum.IsExternal(), true);
				Assert::AreEqual(datum.GetFloat(0), 4.0f);
				Assert::AreEqual(datum.GetFloat(1), 8.0f);
				Assert::AreEqual(datum.GetFloat(2), 12.0f);

				auto allocated = [&datum, &floatArray]()
				{
					datum.SetStorage(floatArray, 3);
				};
				Assert::ExpectException<std::runtime_error>(allocated);
			}

			{
				Datum datum;
				glm::vec4 v1(4, 4, 4, 4);
				glm::vec4 v2(8, 8, 8, 8);
				glm::vec4 v3(12, 12, 12, 12);
				glm::vec4 vectorArray[3] = { v1, v2, v3 };
				datum.SetStorage(vectorArray, 3);
				Assert::AreEqual(datum.Size(), size_t(3));
				Assert::AreEqual(datum.Capacity(), size_t(3));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Vector);
				Assert::AreEqual(datum.IsExternal(), true);
				Assert::AreEqual(datum.GetVector(0), v1);
				Assert::AreEqual(datum.GetVector(1), v2);
				Assert::AreEqual(datum.GetVector(2), v3);

				auto allocated = [&datum, &vectorArray]()
				{
					datum.SetStorage(vectorArray, 3);
				};
				Assert::ExpectException<std::runtime_error>(allocated);
			}

			{
				Datum datum;
				glm::mat4 m1(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
				glm::mat4 m2(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8);
				glm::mat4 m3(12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);
				glm::mat4 matrixArray[3] = { m1, m2, m3 };
				datum.SetStorage(matrixArray, 3);
				Assert::AreEqual(datum.Size(), size_t(3));
				Assert::AreEqual(datum.Capacity(), size_t(3));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Matrix);
				Assert::AreEqual(datum.IsExternal(), true);
				Assert::AreEqual(datum.GetMatrix(0), m1);
				Assert::AreEqual(datum.GetMatrix(1), m2);
				Assert::AreEqual(datum.GetMatrix(2), m3);

				auto allocated = [&datum, &matrixArray]()
				{
					datum.SetStorage(matrixArray, 3);
				};
				Assert::ExpectException<std::runtime_error>(allocated);
			}

			{
				Datum datum;
				std::string s1("gaming");
				std::string s2("im dying");
				std::string s3("fuck");
				std::string stringArray[3] = { s1, s2, s3 };
				datum.SetStorage(stringArray, 3);
				Assert::AreEqual(datum.Size(), size_t(3));
				Assert::AreEqual(datum.Capacity(), size_t(3));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::String);
				Assert::AreEqual(datum.IsExternal(), true);
				Assert::AreEqual(datum.GetString(0), s1);
				Assert::AreEqual(datum.GetString(1), s2);
				Assert::AreEqual(datum.GetString(2), s3);

				auto allocated = [&datum, &stringArray]()
				{
					datum.SetStorage(stringArray, 3);
				};
				Assert::ExpectException<std::runtime_error>(allocated);
			}

			{
				Datum datum;
				Foo f1{ 10 };
				Foo f2{ 20 };
				Foo f3{ 30 };
				RTTI* r1 = &f1;
				RTTI* r2 = &f2;
				RTTI* r3 = &f3;
				RTTI* RTTIArray[3] = { r1, r2, r3 };
				datum.SetStorage(RTTIArray, 3);
				Assert::AreEqual(datum.Size(), size_t(3));
				Assert::AreEqual(datum.Capacity(), size_t(3));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Pointer);
				Assert::AreEqual(datum.IsExternal(), true);
				Assert::AreEqual(datum.GetRTTI(0), r1);
				Assert::AreEqual(datum.GetRTTI(1), r2);
				Assert::AreEqual(datum.GetRTTI(2), r3);

				auto allocated = [&datum, &RTTIArray]()
				{
					datum.SetStorage(RTTIArray, 3);
				};
				Assert::ExpectException<std::runtime_error>(allocated);
			}
		}

		TEST_METHOD(ComparisonOperators)
		{
			{
				Datum datum = 4;
				Datum datum2 = 4.0f;
				bool equal = (datum == datum2);
				Assert::AreEqual(equal, false);
			}

			{
				Datum datum = 4;
				Datum datum2 = 4;
				bool equal = (datum == datum2);
				Assert::AreEqual(equal, true);
			}

			{
				Datum datum = "gaming";
				datum.PushBack("fuck");
				Datum datum2 = "gaming";
				datum2.PushBack("shit");
				bool equal = (datum == datum2);
				Assert::AreEqual(equal, false);
			}

			{
				Datum datum = 4;
				Datum datum2 = 8;
				bool equal = (datum == datum2);
				Assert::AreEqual(equal, false);
			}

			{
				{
					Datum datum;
					auto size = [&datum]()
					{
						bool equal = datum == 4;
						equal;
					};
					Assert::ExpectException<std::runtime_error>(size);

					datum.PushBack(8.0f);

					auto type = [&datum]()
					{
						bool equal = datum == 4;
						equal;
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				Datum datum = 4;
				bool equal = (datum == 4);
				Assert::AreEqual(equal, true);
			}

			{
				{
					Datum datum;
					auto size = [&datum]()
					{
						bool equal = datum == 4.0f;
						equal;
					};
					Assert::ExpectException<std::runtime_error>(size);

					datum.PushBack(8);

					auto type = [&datum]()
					{
						bool equal = datum == 4.0f;
						equal;
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				Datum datum = 4.0f;
				bool equal = (datum == 4.0f);
				Assert::AreEqual(equal, true);
			}

			{
				{
					Datum datum;
					auto size = [&datum]()
					{
						bool equal = datum == glm::vec4(4,4,4,4);
						equal;
					};
					Assert::ExpectException<std::runtime_error>(size);

					datum.PushBack(8);

					auto type = [&datum]()
					{
						bool equal = datum == glm::vec4(4, 4, 4, 4);
						equal;
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				Datum datum = glm::vec4(4, 4, 4, 4);
				bool equal = (datum == glm::vec4(4, 4, 4, 4));
				Assert::AreEqual(equal, true);
			}

			{
				{
					Datum datum;
					auto size = [&datum]()
					{
						bool equal = datum == glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
						equal;
					};
					Assert::ExpectException<std::runtime_error>(size);

					datum.PushBack(8);

					auto type = [&datum]()
					{
						bool equal = datum == glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
						equal;
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
				bool equal = (datum == glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
				Assert::AreEqual(equal, true);
			}

			{
				{
					Datum datum;
					auto size = [&datum]()
					{
						bool equal = datum == std::string("eyyooo");
						equal;
					};
					Assert::ExpectException<std::runtime_error>(size);

					datum.PushBack(8);

					auto type = [&datum]()
					{
						bool equal = datum == std::string("eyyooo");
						equal;
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				Datum datum = std::string("eyyooo");
				bool equal = (datum == std::string("eyyooo"));
				Assert::AreEqual(equal, true);
			}

			{
				Foo f{ 10 };
				RTTI* r = &f;
				{
					Datum datum;
					auto size = [&datum, &r]()
					{
						
						bool equal = datum == r;
						equal;
					};
					Assert::ExpectException<std::runtime_error>(size);

					datum.PushBack(8);

					auto type = [&datum, &r]()
					{
						bool equal = datum == r;
						equal;
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				Datum datum = r;
				bool equal = (datum == r);
				Assert::AreEqual(equal, true);
			}
		}

		TEST_METHOD(Set)
		{
			{
				{
					Datum datum = 4;
					auto size = [&datum]()
					{
						datum.Set(2, 1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					datum.Set(2, 0);
					Assert::AreEqual(datum.GetInt(), 2);
				}

				{
					Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.Set(2, 0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = 4.0f;
					auto size = [&datum]()
					{
						datum.Set(2.0f, 1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					datum.Set(2.0f, 0);
					Assert::AreEqual(datum.GetFloat(), 2.0f);
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Set(2.0f, 0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = glm::vec4(4,4,4,4);
					auto size = [&datum]()
					{
						datum.Set(glm::vec4(4, 4, 4, 4), 1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					datum.Set(glm::vec4(4, 4, 4, 4), 0);
					Assert::AreEqual(datum.GetVector(), glm::vec4(4, 4, 4, 4));
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Set(glm::vec4(4, 4, 4, 4), 0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					auto size = [&datum]()
					{
						datum.Set(glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4), 1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					datum.Set(glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4), 0);
					Assert::AreEqual(datum.GetMatrix(), glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Set(glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4), 0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = std::string("free");
					auto size = [&datum]()
					{
						datum.Set(std::string("free"), 1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					datum.Set(std::string("free"), 0);
					Assert::AreEqual(datum.GetString(), std::string("free"));
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Set(std::string("free"), 0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				Foo f{ 10 };
				RTTI* r = &f;
				{
					Datum datum = r;
					auto size = [&datum, &r]()
					{
						datum.Set(r, 1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					datum.Set(r, 0);
					Assert::AreEqual(datum.GetRTTI(), r);
				}

				{
					Datum datum = 4;
					auto type = [&datum, &r]()
					{
						datum.Set(r, 0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}
		}

		TEST_METHOD(Get)
		{
			{
				{
					Datum datum = 4;
					auto size = [&datum]()
					{
						datum.GetInt(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetInt(), 4);
				}

				{
					Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.GetInt(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = 4.0f;
					auto size = [&datum]()
					{
						datum.GetFloat(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetFloat(), 4.0f);
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.GetFloat(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = glm::vec4(4, 4, 4, 4);
					auto size = [&datum]()
					{
						datum.GetVector(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetVector(), glm::vec4(4, 4, 4, 4));
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.GetVector(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					auto size = [&datum]()
					{
						datum.GetMatrix(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetMatrix(), glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.GetMatrix(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = std::string("free");
					auto size = [&datum]()
					{
						datum.GetString(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetString(), std::string("free"));
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.GetString(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				Foo f{ 10 };
				RTTI* r = &f;
				{
					Datum datum = r;
					auto size = [&datum, &r]()
					{
						datum.GetRTTI(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetRTTI(), r);
				}

				{
					Datum datum = 4;
					auto type = [&datum, &r]()
					{
						datum.GetRTTI(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					const Datum datum = 4;
					auto size = [&datum]()
					{
						datum.GetInt(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetInt(), 4);
				}

				{
					const Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.GetInt(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					const Datum datum = 4.0f;
					auto size = [&datum]()
					{
						datum.GetFloat(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetFloat(), 4.0f);
				}

				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.GetFloat(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					const Datum datum = glm::vec4(4, 4, 4, 4);
					auto size = [&datum]()
					{
						datum.GetVector(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetVector(), glm::vec4(4, 4, 4, 4));
				}

				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.GetVector(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					const Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					auto size = [&datum]()
					{
						datum.GetMatrix(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetMatrix(), glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
				}

				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.GetMatrix(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					const Datum datum = std::string("free");
					auto size = [&datum]()
					{
						datum.GetString(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetString(), std::string("free"));
				}

				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.GetString(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				Foo f{ 10 };
				RTTI* r = &f;
				{
					const Datum datum = r;
					auto size = [&datum, &r]()
					{
						datum.GetRTTI(1);
					};
					Assert::ExpectException<std::out_of_range>(size);

					Assert::AreEqual(datum.GetRTTI(), r);
				}

				{
					const Datum datum = 4;
					auto type = [&datum, &r]()
					{
						datum.GetRTTI(0);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}
		}

		TEST_METHOD(SetFromString)
		{
			{
				Datum datum;
				auto type = [&datum]()
				{
					datum.SetFromString("0", 0);
				};
				Assert::ExpectException<std::runtime_error>(type);
			}

			{
				Datum datum = 4;
				datum.SetFromString("0", 0);
				Assert::AreEqual(datum.GetInt(), 0);
			}

			{
				Datum datum = 4.0f;
				datum.SetFromString("0.0", 0);
				Assert::AreEqual(datum.GetFloat(), 0.000000f);
			}

			{
				Datum datum = glm::vec4(4,4,4,4);
				datum.SetFromString("vec4(0, 0, 0, 0)", 0);
				Assert::AreEqual(datum.GetVector(), glm::vec4(0,0,0,0));
			}

			{
				Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
				datum.SetFromString("mat4x4((0, 0, 0, 0), (0, 0, 0, 0), (0, 0, 0, 0), (0, 0, 0, 0))", 0);
				Assert::AreEqual(datum.GetMatrix(), glm::mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
			}

			{
				Datum datum = "deadge";
				datum.SetFromString("sadge", 0);
				Assert::AreEqual(datum.GetString(), std::string("sadge"));
			}
		}

		TEST_METHOD(ToString)
		{
			{
				Datum datum;
				auto type = [&datum]()
				{
					datum.ToString(0);
				};
				Assert::ExpectException<std::runtime_error>(type);
			}

			{
				Datum datum = 4;
				Assert::AreEqual(datum.ToString(0), std::string("4"));
			}

			{
				Datum datum = 4.0f;
				Assert::AreEqual(datum.ToString(0), std::string("4.000000"));
			}

			{
				Datum datum = glm::vec4(4,4,4,4);
				Assert::AreEqual(datum.ToString(0), std::string("4.000000 4.000000 4.000000 4.000000"));
			}

			{
				Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
				Assert::AreEqual(datum.ToString(0), std::string("4.000000 4.000000 4.000000 4.000000 4.000000 4.000000 4.000000 4.000000 4.000000 4.000000 4.000000 4.000000 4.000000 4.000000 4.000000 4.000000"));
			}

			{
				Datum datum = "lmaowhatamidoing";
				Assert::AreEqual(datum.ToString(0), std::string("lmaowhatamidoing"));
			}
		}

		TEST_METHOD(PushBack)
		{
			{
				{
					int32_t intArray[3] = { 4, 8, 12 };

					Datum datum;
					datum.SetStorage(intArray, 3);
					auto external = [&datum]()
					{
						datum.PushBack(16);
					};
					Assert::ExpectException<std::runtime_error>(external);
				}

				{
					Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.PushBack(16);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum = 4;
					datum.PushBack(4);
					Assert::AreEqual(datum.Size(), size_t(2));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.GetInt(0), 4);
					Assert::AreEqual(datum.GetInt(1), 4);
				}
			}

			{
				{
					int32_t intArray[3] = { 4, 8, 12 };

					Datum datum;
					datum.SetStorage(intArray, 3);
					auto external = [&datum]()
					{
						datum.PushBack(16.0f);
					};
					Assert::ExpectException<std::runtime_error>(external);
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.PushBack(16.0f);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum = 4.0f;
					datum.PushBack(4.0f);
					Assert::AreEqual(datum.Size(), size_t(2));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::Float);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.GetFloat(0), 4.0f);
					Assert::AreEqual(datum.GetFloat(1), 4.0f);
				}
			}

			{
				{
					int32_t intArray[3] = { 4, 8, 12 };

					Datum datum;
					datum.SetStorage(intArray, 3);
					auto external = [&datum]()
					{
						datum.PushBack(glm::vec4(4,4,4,4));
					};
					Assert::ExpectException<std::runtime_error>(external);
				}

				{
					Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.PushBack(glm::vec4(4, 4, 4, 4));
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum = glm::vec4(4, 4, 4, 4);
					datum.PushBack(glm::vec4(4, 4, 4, 4));
					Assert::AreEqual(datum.Size(), size_t(2));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::Vector);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.GetVector(0), glm::vec4(4, 4, 4, 4));
					Assert::AreEqual(datum.GetVector(1), glm::vec4(4, 4, 4, 4));
				}
			}

			{
				{
					int32_t intArray[3] = { 4, 8, 12 };

					Datum datum;
					datum.SetStorage(intArray, 3);
					auto external = [&datum]()
					{
						datum.PushBack(glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
					};
					Assert::ExpectException<std::runtime_error>(external);
				}

				{
					Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.PushBack(glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					datum.PushBack(glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
					Assert::AreEqual(datum.Size(), size_t(2));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::Matrix);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.GetMatrix(0), glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
					Assert::AreEqual(datum.GetMatrix(1), glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
				}
			}

			{
				{
					int32_t intArray[3] = { 4, 8, 12 };

					Datum datum;
					datum.SetStorage(intArray, 3);
					auto external = [&datum]()
					{
						datum.PushBack("ahhhhhhhhhhhhh");
					};
					Assert::ExpectException<std::runtime_error>(external);
				}

				{
					Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.PushBack("ahhhhhhhhhhhhh");
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum = "ahhhhhhhhhhhhh";
					datum.PushBack("ahhhhhhhhhhhhh");
					Assert::AreEqual(datum.Size(), size_t(2));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::String);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.GetString(0), std::string("ahhhhhhhhhhhhh"));
					Assert::AreEqual(datum.GetString(1), std::string("ahhhhhhhhhhhhh"));
				}
			}

			{
				{
					Foo f{ 10 };
					RTTI* r = &f;
					int32_t intArray[3] = { 4, 8, 12 };

					Datum datum;
					datum.SetStorage(intArray, 3);
					auto external = [&datum, &r]()
					{
						datum.PushBack(r);
					};
					Assert::ExpectException<std::runtime_error>(external);
				}

				{
					Foo f{ 10 };
					RTTI* r = &f;
					Datum datum = 4.0f;
					auto type = [&datum, &r]()
					{
						datum.PushBack(r);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Foo f{ 10 };
					RTTI* r = &f;
					Datum datum = r;
					datum.PushBack(r);
					Assert::AreEqual(datum.Size(), size_t(2));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::Pointer);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.GetRTTI(0), r);
					Assert::AreEqual(datum.GetRTTI(1), r);
				}
			}
		}

		TEST_METHOD(PopBack)
		{
			{
				Datum datum = 4;
				datum.PopBack();
				Assert::AreEqual(datum.Size(), size_t(0));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
				Assert::AreEqual(datum.IsExternal(), false);
			}

			{
				Datum datum = "THISISWILD";
				datum.PopBack();
				Assert::AreEqual(datum.Size(), size_t(0));
				Assert::AreEqual(datum.Capacity(), size_t(1));
				Assert::AreEqual(datum.Type(), Datum::DatumTypes::String);
				Assert::AreEqual(datum.IsExternal(), false);
			}

			{
				int32_t intArray[3] = { 4, 8, 12 };

				Datum datum;
				datum.SetStorage(intArray, 3);
				auto external = [&datum]()
				{
					datum.PopBack();
				};
				Assert::ExpectException<std::runtime_error>(external);
			}
		}

		TEST_METHOD(Front)
		{
			{
				{
					Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.FrontInt();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::Integer);
					auto empty = [&datum]()
					{
						datum.FrontInt();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Datum datum = 4;
					Assert::AreEqual(datum.FrontInt(), 4);
				}
			}

			{
				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.FrontFloat();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::Float);
					auto empty = [&datum]()
					{
						datum.FrontFloat();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Datum datum = 4.0f;
					Assert::AreEqual(datum.FrontFloat(), 4.0f);
				}
			}

			{
				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.FrontVector();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::Vector);
					auto empty = [&datum]()
					{
						datum.FrontVector();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Datum datum = glm::vec4(4,4,4,4);
					Assert::AreEqual(datum.FrontVector(), glm::vec4(4, 4, 4, 4));
				}
			}

			{
				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.FrontMatrix();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::Matrix);
					auto empty = [&datum]()
					{
						datum.FrontMatrix();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					Assert::AreEqual(datum.FrontMatrix(), glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
				}
			}

			{
				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.FrontString();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::String);
					auto empty = [&datum]()
					{
						datum.FrontString();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Datum datum = "askldjfaklf";
					Assert::AreEqual(datum.FrontString(), std::string("askldjfaklf"));
				}
			}

			{
				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.FrontRTTI();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::Pointer);
					auto empty = [&datum]()
					{
						datum.FrontRTTI();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Foo f{ 10 };
					RTTI* r = &f;
					Datum datum = r;
					Assert::AreEqual(datum.FrontRTTI(), r);
				}
			}

			{
				{
					const Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.FrontInt();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::Integer);
					auto empty = [&datum]()
					{
						datum.FrontInt();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					const Datum datum = 4;
					Assert::AreEqual(datum.FrontInt(), 4);
				}
			}

			{
				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.FrontFloat();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::Float);
					auto empty = [&datum]()
					{
						datum.FrontFloat();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					const Datum datum = 4.0f;
					Assert::AreEqual(datum.FrontFloat(), 4.0f);
				}
			}

			{
				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.FrontVector();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::Vector);
					auto empty = [&datum]()
					{
						datum.FrontVector();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					const Datum datum = glm::vec4(4, 4, 4, 4);
					Assert::AreEqual(datum.FrontVector(), glm::vec4(4, 4, 4, 4));
				}
			}

			{
				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.FrontMatrix();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::Matrix);
					auto empty = [&datum]()
					{
						datum.FrontMatrix();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					const Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					Assert::AreEqual(datum.FrontMatrix(), glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
				}
			}

			{
				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.FrontString();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::String);
					auto empty = [&datum]()
					{
						datum.FrontString();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					const Datum datum = "askldjfaklf";
					Assert::AreEqual(datum.FrontString(), std::string("askldjfaklf"));
				}
			}

			{
				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.FrontRTTI();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::Pointer);
					auto empty = [&datum]()
					{
						datum.FrontRTTI();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Foo f{ 10 };
					RTTI* r = &f;
					const Datum datum = r;
					Assert::AreEqual(datum.FrontRTTI(), r);
				}
			}
		}

		TEST_METHOD(Back)
		{
			{
				{
					Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.BackInt();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::Integer);
					auto empty = [&datum]()
					{
						datum.BackInt();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Datum datum = 4;
					Assert::AreEqual(datum.BackInt(), 4);
				}
			}

			{
				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.BackFloat();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::Float);
					auto empty = [&datum]()
					{
						datum.BackFloat();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Datum datum = 4.0f;
					Assert::AreEqual(datum.BackFloat(), 4.0f);
				}
			}

			{
				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.BackVector();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::Vector);
					auto empty = [&datum]()
					{
						datum.BackVector();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Datum datum = glm::vec4(4, 4, 4, 4);
					Assert::AreEqual(datum.BackVector(), glm::vec4(4, 4, 4, 4));
				}
			}

			{
				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.BackMatrix();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::Matrix);
					auto empty = [&datum]()
					{
						datum.BackMatrix();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					Assert::AreEqual(datum.BackMatrix(), glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
				}
			}

			{
				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.BackString();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::String);
					auto empty = [&datum]()
					{
						datum.BackString();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Datum datum = "askldjfaklf";
					Assert::AreEqual(datum.BackString(), std::string("askldjfaklf"));
				}
			}

			{
				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.BackRTTI();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum(Datum::DatumTypes::Pointer);
					auto empty = [&datum]()
					{
						datum.BackRTTI();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Foo f{ 10 };
					RTTI* r = &f;
					Datum datum = r;
					Assert::AreEqual(datum.BackRTTI(), r);
				}
			}

			{
				{
					const Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.BackInt();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::Integer);
					auto empty = [&datum]()
					{
						datum.BackInt();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					const Datum datum = 4;
					Assert::AreEqual(datum.BackInt(), 4);
				}
			}

			{
				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.BackFloat();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::Float);
					auto empty = [&datum]()
					{
						datum.BackFloat();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					const Datum datum = 4.0f;
					Assert::AreEqual(datum.BackFloat(), 4.0f);
				}
			}

			{
				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.BackVector();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::Vector);
					auto empty = [&datum]()
					{
						datum.BackVector();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					const Datum datum = glm::vec4(4, 4, 4, 4);
					Assert::AreEqual(datum.BackVector(), glm::vec4(4, 4, 4, 4));
				}
			}

			{
				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.BackMatrix();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::Matrix);
					auto empty = [&datum]()
					{
						datum.BackMatrix();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					const Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					Assert::AreEqual(datum.BackMatrix(), glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
				}
			}

			{
				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.BackString();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::String);
					auto empty = [&datum]()
					{
						datum.BackString();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					const Datum datum = "askldjfaklf";
					Assert::AreEqual(datum.BackString(), std::string("askldjfaklf"));
				}
			}

			{
				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.BackRTTI();
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					const Datum datum(Datum::DatumTypes::Pointer);
					auto empty = [&datum]()
					{
						datum.BackRTTI();
					};
					Assert::ExpectException<std::runtime_error>(empty);
				}

				{
					Foo f{ 10 };
					RTTI* r = &f;
					const Datum datum = r;
					Assert::AreEqual(datum.BackRTTI(), r);
				}
			}
		}

		TEST_METHOD(Remove)
		{
			{
				{
					int32_t intArray[3] = { 4, 8, 12 };

					Datum datum;
					datum.SetStorage(intArray, 3);
					auto external = [&datum]()
					{
						datum.Remove(4);
					};
					Assert::ExpectException<std::runtime_error>(external);
				}

				{
					Datum datum;
					auto type = [&datum]()
					{
						datum.RemoveAt(4);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.RemoveAt(4);
					};
					Assert::ExpectException<std::out_of_range>(type);
				}

				{
					Datum datum = 4;
					datum.PushBack(8);
					datum.Remove(4);
					Assert::AreEqual(datum.Size(), size_t(1));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::Integer);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.FrontInt(), 8);
				}

				{
					Datum datum = 4.0f;
					datum.PushBack(8.0f);
					datum.Remove(4.0f);
					Assert::AreEqual(datum.Size(), size_t(1));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::Float);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.FrontFloat(), 8.0f);
				}

				{
					Datum datum = glm::vec4(4,4,4,4);
					datum.PushBack(glm::vec4(8,8,8,8));
					datum.Remove(glm::vec4(4, 4, 4, 4));
					Assert::AreEqual(datum.Size(), size_t(1));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::Vector);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.FrontVector(), glm::vec4(8, 8, 8, 8));
				}

				{
					Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					datum.PushBack(glm::mat4(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8));
					datum.Remove(glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
					Assert::AreEqual(datum.Size(), size_t(1));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::Matrix);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.FrontMatrix(), glm::mat4(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8));
				}


				{
					Datum datum = "gottem";
					datum.PushBack("lmao");
					datum.Remove("gottem");
					Assert::AreEqual(datum.Size(), size_t(1));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::String);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.FrontString(), std::string("lmao"));
				}

				{
					Foo f1{ 10 };
					Foo f2{ 20 };
					RTTI* r1 = &f1;
					RTTI* r2 = &f2;
					Datum datum = r1;
					datum.PushBack(r2);
					datum.Remove(r1);
					Assert::AreEqual(datum.Size(), size_t(1));
					Assert::AreEqual(datum.Capacity(), size_t(2));
					Assert::AreEqual(datum.Type(), Datum::DatumTypes::Pointer);
					Assert::AreEqual(datum.IsExternal(), false);
					Assert::AreEqual(datum.FrontRTTI(), r2);
				}
			}
		}

		TEST_METHOD(Find)
		{
			{
				{
					Datum datum = 4;
					datum.PushBack(8);
					Assert::AreEqual(datum.Find(8).first, size_t(1));
					Assert::AreEqual(datum.Find(8).second, true);
				}

				{
					Datum datum = 4;
					Assert::AreEqual(datum.Find(8).first, size_t(1));
					Assert::AreEqual(datum.Find(8).second, false);
				}

				{
					Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.Find(4);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = 4.0f;
					datum.PushBack(8.0f);
					Assert::AreEqual(datum.Find(8.0f).first, size_t(1));
					Assert::AreEqual(datum.Find(8.0f).second, true);
				}

				{
					Datum datum = 4.0f;
					Assert::AreEqual(datum.Find(8.0f).first, size_t(1));
					Assert::AreEqual(datum.Find(8.0f).second, false);
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Find(4.0f);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = glm::vec4(4,4,4,4);
					datum.PushBack(glm::vec4(8, 8, 8, 8));
					Assert::AreEqual(datum.Find(glm::vec4(8, 8, 8, 8)).first, size_t(1));
					Assert::AreEqual(datum.Find(glm::vec4(8, 8, 8, 8)).second, true);
				}

				{
					Datum datum = glm::vec4(4,4,4,4);
					Assert::AreEqual(datum.Find(glm::vec4(8, 8, 8, 8)).first, size_t(1));
					Assert::AreEqual(datum.Find(glm::vec4(8, 8, 8, 8)).second, false);
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Find(glm::vec4(4, 4, 4, 4));
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					datum.PushBack(glm::mat4(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8));
					Assert::AreEqual(datum.Find(glm::mat4(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8)).first, size_t(1));
					Assert::AreEqual(datum.Find(glm::mat4(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8)).second, true);
				}

				{
					Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					Assert::AreEqual(datum.Find(glm::mat4(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8)).first, size_t(1));
					Assert::AreEqual(datum.Find(glm::mat4(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8)).second, false);
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Find(glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Datum datum = "gottem";
					datum.PushBack("lmao");
					Assert::AreEqual(datum.Find("lmao").first, size_t(1));
					Assert::AreEqual(datum.Find("lmao").second, true);
				}

				{
					Datum datum = "gottem";
					Assert::AreEqual(datum.Find("lmao").first, size_t(1));
					Assert::AreEqual(datum.Find("lmao").second, false);
				}

				{
					Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Find("gottem");
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Foo f1{ 10 };
					Foo f2{ 20 };
					RTTI* r1 = &f1;
					RTTI* r2 = &f2;
					Datum datum = r1;
					datum.PushBack(r2);
					Assert::AreEqual(datum.Find(r2).first, size_t(1));
					Assert::AreEqual(datum.Find(r2).second, true);
				}

				{
					Foo f1{ 10 };
					Foo f2{ 20 };
					RTTI* r1 = &f1;
					RTTI* r2 = &f2;
					Datum datum = r1;
					Assert::AreEqual(datum.Find(r2).first, size_t(1));
					Assert::AreEqual(datum.Find(r2).second, false);
				}

				{
					Foo f1{ 10 };
					RTTI* r1 = &f1;
					Datum datum = 4;
					auto type = [&datum, &r1]()
					{
						datum.Find(r1);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					const Datum datum = 4;
					Assert::AreEqual(datum.Find(4).first, size_t(0));
					Assert::AreEqual(datum.Find(4).second, true);
				}

				{
					const Datum datum = 4;
					Assert::AreEqual(datum.Find(8).first, size_t(1));
					Assert::AreEqual(datum.Find(8).second, false);
				}

				{
					const Datum datum = 4.0f;
					auto type = [&datum]()
					{
						datum.Find(4);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					const Datum datum = 4.0f;
					Assert::AreEqual(datum.Find(4.0f).first, size_t(0));
					Assert::AreEqual(datum.Find(4.0f).second, true);
				}

				{
					const Datum datum = 4.0f;
					Assert::AreEqual(datum.Find(8.0f).first, size_t(1));
					Assert::AreEqual(datum.Find(8.0f).second, false);
				}

				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Find(4.0f);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					const Datum datum = glm::vec4(4, 4, 4, 4);
					Assert::AreEqual(datum.Find(glm::vec4(4, 4, 4, 4)).first, size_t(0));
					Assert::AreEqual(datum.Find(glm::vec4(4, 4, 4, 4)).second, true);
				}

				{
					const Datum datum = glm::vec4(4, 4, 4, 4);
					Assert::AreEqual(datum.Find(glm::vec4(8, 8, 8, 8)).first, size_t(1));
					Assert::AreEqual(datum.Find(glm::vec4(8, 8, 8, 8)).second, false);
				}

				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Find(glm::vec4(4, 4, 4, 4));
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					const Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					Assert::AreEqual(datum.Find(glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4)).first, size_t(0));
					Assert::AreEqual(datum.Find(glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4)).second, true);
				}

				{
					const Datum datum = glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
					Assert::AreEqual(datum.Find(glm::mat4(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8)).first, size_t(1));
					Assert::AreEqual(datum.Find(glm::mat4(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8)).second, false);
				}

				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Find(glm::mat4(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4));
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					const Datum datum = "gottem";
					Assert::AreEqual(datum.Find("gottem").first, size_t(0));
					Assert::AreEqual(datum.Find("gottem").second, true);
				}

				{
					const Datum datum = "gottem";
					Assert::AreEqual(datum.Find("lmao").first, size_t(1));
					Assert::AreEqual(datum.Find("lmao").second, false);
				}

				{
					const Datum datum = 4;
					auto type = [&datum]()
					{
						datum.Find("gottem");
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}

			{
				{
					Foo f1{ 10 };
					RTTI* r1 = &f1;
					const Datum datum = r1;
					Assert::AreEqual(datum.Find(r1).first, size_t(0));
					Assert::AreEqual(datum.Find(r1).second, true);
				}

				{
					Foo f1{ 10 };
					Foo f2{ 20 };
					RTTI* r1 = &f1;
					RTTI* r2 = &f2;
					const Datum datum = r1;
					Assert::AreEqual(datum.Find(r2).first, size_t(1));
					Assert::AreEqual(datum.Find(r2).second, false);
				}

				{
					Foo f1{ 10 };
					RTTI* r1 = &f1;
					const Datum datum = 4;
					auto type = [&datum, &r1]()
					{
						datum.Find(r1);
					};
					Assert::ExpectException<std::runtime_error>(type);
				}
			}
		}

		TEST_METHOD(Reserve)
		{
			Datum datum;
			int32_t intArray[3] = { 4, 8, 12 };
			datum.SetStorage(intArray, 3);

			auto external = [&datum]()
			{
				datum.Reserve(5);
			};
			Assert::ExpectException<std::runtime_error>(external);
		}

	private:
		static _CrtMemState startMemState;
	};

	_CrtMemState DatumTests::startMemState;
}
