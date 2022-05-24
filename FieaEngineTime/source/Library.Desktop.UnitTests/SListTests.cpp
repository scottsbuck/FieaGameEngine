#include "pch.h"
#include "CppUnitTest.h"
#include "SList.h"
#include "Foo.h"
#include "ToStringSpecializationsSList.h"
#include <stdexcept>
#include <crtdbg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopUnitTests
{
	TEST_CLASS(SListTests)
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
			SList<Foo> sList;
			Assert::AreEqual(size_t(0), sList.Size());
		}

		TEST_METHOD(PushFront)
		{
			SList<Foo> sList;
			
			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			sList.PushFront(foo1);

			Assert::AreEqual(foo1, sList.Front());
			Assert::AreEqual(foo1, sList.Back());
			Assert::AreEqual(size_t(1), sList.Size());

			sList.PushFront(foo2);

			Assert::AreEqual(foo2, sList.Front());
			Assert::AreEqual(foo1, sList.Back());
			Assert::AreEqual(size_t(2), sList.Size());

			sList.PushFront(foo3);

			Assert::AreEqual(foo3, sList.Front());
			Assert::AreEqual(foo1, sList.Back());
			Assert::AreEqual(size_t(3), sList.Size());

		}

		TEST_METHOD(PopFront)
		{
			SList<Foo> sList;

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			sList.PopFront();

			sList.PushFront(foo1);

			sList.PopFront();

			Assert::AreEqual(size_t(0), sList.Size());

			auto Front = [&sList]()
			{
				sList.Front();
			};

			Assert::ExpectException<std::runtime_error>(Front);

			auto Back = [&sList]()
			{
				sList.Back();
			};

			Assert::ExpectException<std::runtime_error>(Back);

			sList.PushFront(foo1);
			sList.PushFront(foo2);
			sList.PushFront(foo3);

			sList.PopFront();

			Assert::AreEqual(foo2, sList.Front());
			Assert::AreEqual(size_t(2), sList.Size());

			sList.PopFront();

			Assert::AreEqual(foo1, sList.Front());
			Assert::AreEqual(size_t(1), sList.Size());
		}

		TEST_METHOD(PushBack)
		{
			SList<Foo> sList;

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			sList.PushBack(foo1);

			Assert::AreEqual(size_t(1), sList.Size());
			Assert::AreEqual(foo1, sList.Front());
			Assert::AreEqual(foo1, sList.Back());

			sList.PushBack(foo2);

			Assert::AreEqual(foo1, sList.Front());
			Assert::AreEqual(foo2, sList.Back());
			Assert::AreEqual(size_t(2), sList.Size());

			sList.PushBack(foo3);

			Assert::AreEqual(foo1, sList.Front());
			Assert::AreEqual(foo3, sList.Back());
			Assert::AreEqual(size_t(3), sList.Size());
		}

		TEST_METHOD(PopBack)
		{
			SList<Foo> sList;

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			sList.PopBack();

			sList.PushFront(foo1);

			sList.PopBack();

			Assert::AreEqual(size_t(0), sList.Size());

			auto Front = [&sList]()
			{
				sList.Front();
			};

			Assert::ExpectException<std::runtime_error>(Front);

			auto Back = [&sList]()
			{
				sList.Back();
			};

			Assert::ExpectException<std::runtime_error>(Back);

			sList.PushFront(foo1);
			sList.PushFront(foo2);
			sList.PushFront(foo3);

			sList.PopBack();

			Assert::AreEqual(foo2, sList.Back());
			Assert::AreEqual(size_t(2), sList.Size());

			sList.PopBack();

			Assert::AreEqual(foo3, sList.Back());
			Assert::AreEqual(size_t(1), sList.Size());
		}

		TEST_METHOD(IsEmpty)
		{
			SList<Foo> sList;
			Assert::AreEqual(true, sList.IsEmpty());

			Foo foo1{ 10 };
			sList.PushBack(foo1);
			Assert::AreEqual(false, sList.IsEmpty());
			sList.PopBack();
			Assert::AreEqual(true, sList.IsEmpty());

			SList<Foo> sList2;
			Assert::AreEqual(true, sList2.IsEmpty());

			sList.PushFront(foo1);
			Assert::AreEqual(false, sList.IsEmpty());
			sList.PopFront();
			Assert::AreEqual(true, sList2.IsEmpty());
		}


		TEST_METHOD(Clear)
		{

			SList<Foo> sList;

			sList.Clear();

			Assert::AreEqual(true, sList.IsEmpty());
			Assert::AreEqual(size_t(0), sList.Size());

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			sList.PushFront(foo1);

			sList.Clear();

			Assert::AreEqual(true, sList.IsEmpty());
			Assert::AreEqual(size_t(0), sList.Size());

			sList.PushFront(foo1);
			sList.PushFront(foo2);
			sList.PushFront(foo3);

			sList.Clear();

			Assert::AreEqual(true, sList.IsEmpty());
			Assert::AreEqual(size_t(0), sList.Size());
		}

		TEST_METHOD(IteratorConstructor)
		{
			
			SList<Foo>::Iterator it;

			auto nullOwner = [&it]()
			{
				++it;
			};
			Assert::ExpectException<std::runtime_error>(nullOwner);

			auto nullNode = [&it]()
			{
				*it;
			};
			Assert::ExpectException<std::runtime_error>(nullNode);
		}

		TEST_METHOD(ConstIteratorConstructors)
		{
			SList<Foo>::ConstIterator it;

			auto nullOwner = [&it]()
			{
				++it;
			};
			Assert::ExpectException<std::runtime_error>(nullOwner);

			auto nullNode = [&it]()
			{
				*it;
			};
			Assert::ExpectException<std::runtime_error>(nullNode);
		}

		TEST_METHOD(InsertAfter)
		{
			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };
			Foo foo4{ 40 };

			SList<Foo> list{ foo1, foo2, foo3 };
			SList<Foo> list2{ foo1, foo2, foo3 };

			SList<Foo>::Iterator it = list.begin();
			SList<Foo>::Iterator it2 = list2.begin();

			auto ownerCheck = [&it2, &list, &foo4]()
			{
				list.InsertAfter(foo4, it2);
			};
			
			Assert::ExpectException<std::runtime_error>(ownerCheck);

			for (it = list.begin(); it != list.end(); ++it)
			{
				if (*it == list.Back())
				{
					break;
				}
			}

			list.InsertAfter(foo4, it);

			Assert::AreEqual(foo4, list.Back());

			it = list.end();

			list.InsertAfter(foo2, it);

			Assert::AreEqual(foo2, list.Back());

			it = list.begin();

			list.InsertAfter(foo4, it);
			it++;

			Assert::AreEqual(foo4, *it);
			Assert::AreEqual(list.Size(), size_t(6));
			it++;
			Assert::AreEqual(list.Front(), foo1);
			Assert::AreEqual(*it, foo2);


		}

		TEST_METHOD(Find)
		{
			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };
			Foo foo4{ 40 };

			SList<Foo> list;

			SList<Foo>::Iterator it = list.Find(foo1);
			Assert::AreEqual(it, list.end());

			SList<Foo> list2{ foo1, foo2, foo3 };
			it = list2.Find(foo1);

			Assert::AreEqual(*it, foo1);

			it = list2.Find(foo3);
			Assert::AreEqual(*it, foo3);

			it = list2.Find(foo4);
			Assert::AreEqual(it, list2.end());

			const SList<Foo> list3;

			SList<Foo>::ConstIterator it2 = list3.Find(foo1);
			Assert::AreEqual(it2, list3.end());

			const SList<Foo> list4{ foo1, foo2, foo3 };
			it2 = list4.Find(foo2);
			Assert::AreEqual(*it2, foo2);

			it2++;
			Assert::AreEqual(*it2, foo3);

			it2 = list4.Find(foo4);
			Assert::AreEqual(it2, list4.end());
		}

		TEST_METHOD(Remove)
		{
			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			SList<Foo> list;

			list.Remove(foo1);

			Assert::AreEqual(list.Size(), size_t(0));
			Assert::AreEqual(list.begin(), list.end());

			SList<Foo> list2{ foo1, foo2, foo3 };

			list2.Remove(foo1);

			Assert::AreEqual(list2.Size(), size_t(2));
			Assert::AreEqual(list2.Front(), foo2);
			Assert::AreEqual(list2.Back(), foo3);

			list2.PushFront(foo1);

			list2.Remove(foo3);

			Assert::AreEqual(list2.Size(), size_t(2));
			Assert::AreEqual(list2.Front(), foo1);
			Assert::AreEqual(list2.Back(), foo2);

			list2.PushBack(foo3);

			list2.Remove(foo2);

			Assert::AreEqual(list2.Size(), size_t(2));
			Assert::AreEqual(list2.Front(), foo1);
			Assert::AreEqual(list2.Back(), foo3);

			list2.Remove(foo1);

			Assert::AreEqual(list2.Size(), size_t(1));
			Assert::AreEqual(list2.Front(), foo3);
			Assert::AreEqual(list2.Back(), foo3);

			list2.Remove(foo3);

			Assert::AreEqual(list2.Size(), size_t(0));
		}

		TEST_METHOD(Iterator)
		{
			SList<Foo> list;

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			Assert::AreEqual(list.begin(), list.end());

			list.PushBack(foo1);

			Assert::AreNotEqual(list.begin(), list.end());
			SList<Foo>::Iterator it = list.begin();
			Assert::AreEqual(*it, list.Front());
			Assert::AreEqual(*it, list.Back());

			SList<Foo>::Iterator it2;

			Assert::AreNotEqual(it, it2);

			SList<Foo> list2;

			list2.PushBack(foo1);

			Assert::AreNotEqual(list.begin(), list2.begin());

			list.PushBack(foo2);
			list.PushBack(foo3);

			Assert::AreEqual(*it, list.Front());

			size_t count = 0;
			for (it = list.begin(); it != list.end(); ++it, ++count)
			{
				;
			}
			Assert::AreEqual(list.Size(), count);

			count = 0;
			for (const Foo& value : list)
			{
				value;
				count++;
			}
			Assert::AreEqual(list.Size(), count);
		}

		TEST_METHOD(ConstIterator)
		{
			const SList<Foo> list;

			Assert::AreEqual(list.begin(), list.end());

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			const SList<Foo> list2{ foo1 };
			
			Assert::AreNotEqual(list2.begin(), list2.end());
			SList<Foo>::ConstIterator it = list2.begin();
			Assert::AreEqual(*it, list2.Front());
			Assert::AreEqual(*it, list2.Back());

			const SList<Foo> list3{ foo1 , foo2, foo3 };

			Assert::AreEqual(*it, list3.Front());
			
			Assert::AreNotEqual(list2.begin(), list3.begin());

			size_t count = 0;
			for (it = list3.begin(); it != list3.end(); ++it, ++count)
			{
				;
			}
			Assert::AreEqual(list3.Size(), count);

			count = 0;
			for (const Foo& value : list3)
			{
				value;
				count++;
			}
			Assert::AreEqual(list3.Size(), count);

			SList<Foo> list4{ foo1, foo2, foo3 };

			SList<Foo>::Iterator it4 = list4.begin();
			SList<Foo>::ConstIterator cIterator(it4);

			Assert::AreEqual(*cIterator, *list4.begin());

		}

		TEST_METHOD(CBeginCEnd)
		{
			const SList<Foo> list;

			Assert::AreEqual(list.cbegin(), list.cend());

			Foo foo1{ 10 };

			const SList<Foo> list2{ foo1 };

			Assert::AreNotEqual(list2.cbegin(), list2.cend());
			Assert::AreEqual(*list2.cbegin(), list2.Front());
		}
		
	private: 
		static _CrtMemState startMemState;
	};
	_CrtMemState SListTests::startMemState;
}
