#include "pch.h"
#include "CppUnitTest.h"
#include "HashMap.h"
#include "Foo.h"
#include "ToStringSpecializationsHashMap.h"
#include <stdexcept>
#include <crtdbg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopUnitTests
{
	TEST_CLASS(HashMapTests)
	{
	public:

		struct EqualityFunctor
		{
			bool operator()(Foo foo1, Foo foo2)
			{
				return foo1 == foo2;
			}
		};

		std::function<bool(Foo foo1, Foo foo2)> equalityFunctor = EqualityFunctor();

		struct FooHash
		{
			std::size_t operator()(Foo foo)
			{
				return (size_t(67) + size_t(foo.Data()));
			}
		};

		std::function<std::size_t(Foo foo)> fooHash = FooHash();

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
				HashMap<Foo, int> hashmap;
				Assert::AreEqual(hashmap.Size(), size_t(0));
			}

			{
				HashMap<Foo, int> hashmap(8);
				Assert::AreEqual(hashmap.Size(), size_t(0));
			}

			{
				HashMap<Foo, int> hashmap(8, fooHash, equalityFunctor);
				Assert::AreEqual(hashmap.Size(), size_t(0));
			}
		}

		TEST_METHOD(Insert)
		{
			{
				Foo foo(10);
				Foo foo2(20);
				Foo foo3(30);
				Foo foo4(6);

				HashMap<Foo, int> hashmap(8, fooHash, equalityFunctor);

				auto p1 = std::make_pair(foo, 15);
				auto p2 = std::make_pair(foo2, 25);
				auto p3 = std::make_pair(foo3, 35);
				auto p4 = std::make_pair(foo4, 45);
				auto p5 = std::make_pair(foo, 55);

				{
					HashMap<Foo, int>::Iterator it = hashmap.Insert(p1);
					HashMap<Foo, int>::Iterator it2 = hashmap.Insert(p2);
					HashMap<Foo, int>::Iterator it3 = hashmap.Insert(p3);

					Assert::AreEqual((*it), p1);
					Assert::AreEqual((*it2), p2);
					Assert::AreEqual((*it3), p3);
				}

				{
					HashMap<Foo, int>::Iterator it = hashmap.begin();
					Assert::AreEqual((*it), p3);
					it++;
					Assert::AreEqual((*it), p1);
					it++;
					Assert::AreEqual((*it), p2);
				}

				{
					hashmap.Insert(p4);
					HashMap<Foo, int>::Iterator it = hashmap.begin();
					Assert::AreEqual((*it), p3);
					it++;
					Assert::AreEqual((*it), p4);
					it++;
					Assert::AreEqual((*it), p1);
					it++;
					Assert::AreEqual((*it), p2);

					Assert::AreEqual((*it).first, foo2);
					Assert::AreEqual((*it).second, 25);
				}

				{
					HashMap<Foo, int>::Iterator it = hashmap.Insert(p5);
					Assert::AreEqual((*it), p1);
				}
			}
		}

		TEST_METHOD(Find)
		{
			{
				Foo foo(10);
				Foo foo2(20);
				Foo foo3(30);
				Foo foo4(6);

				HashMap<Foo, int> hashmap(8, fooHash, equalityFunctor);

				auto p1 = std::make_pair(foo, 15);
				auto p2 = std::make_pair(foo2, 25);
				auto p3 = std::make_pair(foo3, 35);
				auto p4 = std::make_pair(foo4, 45);

				{
					HashMap<Foo, int>::Iterator it = hashmap.Insert(p1);
					HashMap<Foo, int>::Iterator it2 = hashmap.Insert(p2);
					HashMap<Foo, int>::Iterator it3 = hashmap.Insert(p3);

					HashMap<Foo, int>::Iterator it4 = hashmap.Find(foo2);
					Assert::AreEqual(it4, it2);
				}

				{
					HashMap<Foo, int>::Iterator it = hashmap.Find(foo4);
					Assert::AreEqual(it, hashmap.end());
				}
			}

			{
				Foo foo(10);
				Foo foo2(20);
				Foo foo3(30);
				Foo foo4(6);

				auto p1 = std::make_pair(foo, 15);
				auto p2 = std::make_pair(foo2, 25);
				auto p3 = std::make_pair(foo3, 35);
				auto p4 = std::make_pair(foo4, 45);

				const HashMap<Foo, int> hashmap({ p1, p2, p3 }, fooHash, equalityFunctor);
				{
					HashMap<Foo, int>::ConstIterator it = hashmap.Find(foo2);
					Assert::AreEqual(*it, p2);
				}

				{
					HashMap<Foo, int>::ConstIterator it = hashmap.Find(foo4);
					Assert::AreEqual(it, hashmap.end());
				}
			}
		}

		TEST_METHOD(IndexOperator)
		{
			{
				Foo foo(10);
				Foo foo2(20);
				Foo foo3(30);
				Foo foo4(6);

				HashMap<Foo, int> hashmap(8, fooHash, equalityFunctor);

				auto p1 = std::make_pair(foo, 15);
				auto p2 = std::make_pair(foo2, 25);
				auto p3 = std::make_pair(foo3, 35);
				auto p4 = std::make_pair(foo4, 45);

				hashmap.Insert(p1);
				hashmap.Insert(p2);
				hashmap.Insert(p3);

				Assert::AreEqual(hashmap[foo2], 25);
				hashmap[foo4];

				HashMap<Foo, int>::Iterator it = hashmap.begin();
				it++;

				Assert::AreEqual((*it).second, int());
				Assert::AreEqual((*it).first, foo4);
			}

			{
				Foo foo(10);
				Foo foo2(20);
				Foo foo3(30);
				Foo foo4(6);

				auto p1 = std::make_pair(foo, 15);
				auto p2 = std::make_pair(foo2, 25);
				auto p3 = std::make_pair(foo3, 35);
				auto p4 = std::make_pair(foo4, 45);

				const HashMap<Foo, int> hashmap({ p1, p2, p3 }, fooHash, equalityFunctor);

				Assert::AreEqual(hashmap[foo2], 25);

				auto index = [&hashmap, &foo4]()
				{
					hashmap[foo4];
				};

				Assert::ExpectException<std::out_of_range>(index);
			}
		}

		TEST_METHOD(Remove)
		{
			Foo foo(10);
			Foo foo2(20);
			Foo foo3(30);
			Foo foo4(6);

			HashMap<Foo, int> hashmap(8, fooHash, equalityFunctor);

			auto p1 = std::make_pair(foo, 15);
			auto p2 = std::make_pair(foo2, 25);
			auto p3 = std::make_pair(foo3, 35);
			auto p4 = std::make_pair(foo4, 45);

			hashmap.Remove(foo3);

			hashmap.Insert(p1);
			hashmap.Insert(p2);
			hashmap.Insert(p3);
			hashmap.Insert(p4);

			hashmap.Remove(foo4);

			auto index = [&hashmap, &foo4]()
			{
				hashmap.At(foo4);
			};

			Assert::ExpectException<std::out_of_range>(index);
		}

		TEST_METHOD(Clear)
		{
			Foo foo(10);
			Foo foo2(20);
			Foo foo3(30);
			Foo foo4(6);

			HashMap<Foo, int> hashmap(8, fooHash, equalityFunctor);

			auto p1 = std::make_pair(foo, 15);
			auto p2 = std::make_pair(foo2, 25);
			auto p3 = std::make_pair(foo3, 35);
			auto p4 = std::make_pair(foo4, 45);

			hashmap.Insert(p1);
			hashmap.Insert(p2);
			hashmap.Insert(p3);

			hashmap.Clear();

			auto index = [&hashmap, &foo]()
			{
				hashmap.At(foo);
			};

			Assert::ExpectException<std::out_of_range>(index);

			auto index2 = [&hashmap, &foo2]()
			{
				hashmap.At(foo2);
			};

			Assert::ExpectException<std::out_of_range>(index2);

			auto index3 = [&hashmap, &foo3]()
			{
				hashmap.At(foo3);
			};

			Assert::ExpectException<std::out_of_range>(index3);

			HashMap<Foo, int>::Iterator it = hashmap.Insert(p1);
			HashMap<Foo, int>::Iterator it2 = hashmap.Insert(p2);
			HashMap<Foo, int>::Iterator it3 = hashmap.Insert(p3);

			HashMap<Foo, int>::Iterator it4 = hashmap.Find(foo2);
			Assert::AreEqual(it4, it2);
		}

		TEST_METHOD(ContainsKey)
		{
			Foo foo(10);
			Foo foo2(20);
			Foo foo3(30);
			Foo foo4(6);

			HashMap<Foo, int> hashmap(8, fooHash, equalityFunctor);

			auto p1 = std::make_pair(foo, 15);
			auto p2 = std::make_pair(foo2, 25);
			auto p3 = std::make_pair(foo3, 35);
			auto p4 = std::make_pair(foo4, 45);

			
			hashmap.Insert(p1);
			hashmap.Insert(p2);
			hashmap.Insert(p3);

			Assert::AreEqual(true, hashmap.ContainsKey(foo2));
			Assert::AreEqual(false, hashmap.ContainsKey(foo4));
		}

		TEST_METHOD(At)
		{
			{
				Foo foo(10);
				Foo foo2(20);
				Foo foo3(30);
				Foo foo4(6);

				HashMap<Foo, int> hashmap(8, fooHash, equalityFunctor);

				auto p1 = std::make_pair(foo, 15);
				auto p2 = std::make_pair(foo2, 25);
				auto p3 = std::make_pair(foo3, 35);
				auto p4 = std::make_pair(foo4, 45);

				hashmap.Insert(p1);
				hashmap.Insert(p2);
				hashmap.Insert(p3);

				Assert::AreEqual(hashmap.At(foo), 15);
				Assert::AreEqual(hashmap.At(foo2), 25);
				Assert::AreEqual(hashmap.At(foo3), 35);

				auto index = [&hashmap, &foo4]()
				{
					hashmap.At(foo4);
				};

				Assert::ExpectException<std::out_of_range>(index);
			}

			{
				Foo foo(10);
				Foo foo2(20);
				Foo foo3(30);
				Foo foo4(6);

				auto p1 = std::make_pair(foo, 15);
				auto p2 = std::make_pair(foo2, 25);
				auto p3 = std::make_pair(foo3, 35);
				auto p4 = std::make_pair(foo4, 45);

				HashMap<Foo, int> hashmap({ p1, p2, p3 }, fooHash, equalityFunctor);

				Assert::AreEqual(hashmap.At(foo), 15);
				Assert::AreEqual(hashmap.At(foo2), 25);
				Assert::AreEqual(hashmap.At(foo3), 35);

				auto index = [&hashmap, &foo4]()
				{
					hashmap.At(foo4);
				};

				Assert::ExpectException<std::out_of_range>(index);
			}
		}
		
		TEST_METHOD(BeginEnd)
		{
			{
				Foo foo(10);
				Foo foo2(20);
				Foo foo3(30);
				Foo foo4(6);

				HashMap<Foo, int> hashmap(8, fooHash, equalityFunctor);

				auto p1 = std::make_pair(foo, 15);
				auto p2 = std::make_pair(foo2, 25);
				auto p3 = std::make_pair(foo3, 35);
				auto p4 = std::make_pair(foo4, 45);

				Assert::AreEqual(hashmap.begin(), hashmap.end());
			}

			{
				Foo foo(10);
				Foo foo2(20);
				Foo foo3(30);
				Foo foo4(6);

				const HashMap<Foo, int> hashmap(8, fooHash, equalityFunctor);

				auto p1 = std::make_pair(foo, 15);
				auto p2 = std::make_pair(foo2, 25);
				auto p3 = std::make_pair(foo3, 35);
				auto p4 = std::make_pair(foo4, 45);

				Assert::AreEqual(hashmap.begin(), hashmap.end());
				Assert::AreEqual(hashmap.cbegin(), hashmap.cend());
			}

			{
				Foo foo(10);
				Foo foo2(20);
				Foo foo3(30);
				Foo foo4(6);

				auto p1 = std::make_pair(foo, 15);
				auto p2 = std::make_pair(foo2, 25);
				auto p3 = std::make_pair(foo3, 35);
				auto p4 = std::make_pair(foo4, 45);

				const HashMap<Foo, int> hashmap({ p1, p2, p3 }, fooHash, equalityFunctor);

				Assert::AreNotEqual(hashmap.begin(), hashmap.end());
				Assert::AreNotEqual(hashmap.cbegin(), hashmap.end());
			}
		}

		TEST_METHOD(Iterator)
		{
			Foo foo(10);
			Foo foo2(20);
			Foo foo3(30);
			Foo foo4(6);

			auto p1 = std::make_pair(foo, 15);
			auto p2 = std::make_pair(foo2, 25);
			auto p3 = std::make_pair(foo3, 35);
			auto p4 = std::make_pair(foo4, 45);

			HashMap<Foo, int> hashmap({ p1, p2, p3 }, fooHash, equalityFunctor);

			{

				HashMap<Foo, int>::Iterator it;

				auto iterator = [&it]()
				{
					it++;
				};

				Assert::ExpectException<std::runtime_error>(iterator);
			}

			{
				HashMap<Foo, int>::Iterator it;

				auto iterator = [&it]()
				{
					*it;
				};

				Assert::ExpectException<std::runtime_error>(iterator);
			}

			{
				HashMap<Foo, int>::Iterator it;

				auto iterator = [&it]()
				{
					it->first;
				};

				Assert::ExpectException<std::runtime_error>(iterator);
			}

			{
				HashMap<Foo, int>::Iterator it;

				it = hashmap.begin();
				it++;
				it++;

				auto iterator = [&it]()
				{
					it++;
					it->first;
				};

				Assert::ExpectException<std::runtime_error>(iterator);
			}

			HashMap<Foo, int>::Iterator it = hashmap.begin();

			Assert::AreEqual(25, it->second);

			HashMap<Foo, int>::ConstIterator cIterator(it);
			Assert::AreEqual(25, cIterator->second);

			HashMap<Foo, int>::Iterator it2 = hashmap.begin();
			it2++;

			Assert::AreNotEqual(it2, it);
		}

		TEST_METHOD(ConstIterator)
		{
			Foo foo(10);
			Foo foo2(20);
			Foo foo3(30);
			Foo foo4(6);

			auto p1 = std::make_pair(foo, 15);
			auto p2 = std::make_pair(foo2, 25);
			auto p3 = std::make_pair(foo3, 35);
			auto p4 = std::make_pair(foo4, 45);

			const HashMap<Foo, int> hashmap({ p1, p2, p3 }, fooHash, equalityFunctor);

			{

				HashMap<Foo, int>::ConstIterator it;

				auto iterator = [&it]()
				{
					it++;
				};

				Assert::ExpectException<std::runtime_error>(iterator);
			}

			{
				HashMap<Foo, int>::ConstIterator it;

				auto iterator = [&it]()
				{
					*it;
				};

				Assert::ExpectException<std::runtime_error>(iterator);
			}

			{
				HashMap<Foo, int>::ConstIterator it;

				auto iterator = [&it]()
				{
					it->first;
				};

				Assert::ExpectException<std::runtime_error>(iterator);
			}

			{
				HashMap<Foo, int>::ConstIterator it;

				it = hashmap.begin();
				it++;
				it++;

				auto iterator = [&it]()
				{
					it++;
					it->first;
				};

				Assert::ExpectException<std::runtime_error>(iterator);
			}

			HashMap<Foo, int>::ConstIterator it = hashmap.begin();

			Assert::AreEqual(25, it->second);

			HashMap<Foo, int>::ConstIterator it2 = hashmap.begin();
			it2++;

			Assert::AreNotEqual(it2, it);
		}

	private:
		static _CrtMemState startMemState;
	};
	_CrtMemState HashMapTests::startMemState;
}