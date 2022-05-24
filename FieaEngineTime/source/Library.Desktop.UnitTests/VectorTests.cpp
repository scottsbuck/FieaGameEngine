#include "pch.h"
#include "CppUnitTest.h"
#include "Vector.h"
#include "Foo.h"
#include "ToStringSpecializationsVector.h"
#include <stdexcept>
#include <crtdbg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopUnitTests
{
	TEST_CLASS(VectorTests)
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
			Vector<Foo> vector;
			Assert::AreEqual(size_t(0), vector.Size());
			Assert::AreEqual(size_t(8), vector.Capacity());
		}

		TEST_METHOD(PushBack)
		{
			Vector<Foo> vector;

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };
			Foo foo4{ 40 };
			Foo foo5{ 50 };
			Foo foo6{ 60 };
			Foo foo7{ 70 };
			Foo foo8{ 80 };
			Foo foo9{ 90 };

			vector.PushBack(foo1);

			Assert::AreEqual(size_t(1), vector.Size());
			Assert::AreEqual(foo1, vector.Front());
			Assert::AreEqual(foo1, vector.Back());

			vector.PushBack(foo2);

			Assert::AreEqual(foo1, vector.Front());
			Assert::AreEqual(foo2, vector.Back());
			Assert::AreEqual(size_t(2), vector.Size());

			vector.PushBack(foo3);

			Assert::AreEqual(foo1, vector.Front());
			Assert::AreEqual(foo3, vector.Back());
			Assert::AreEqual(size_t(3), vector.Size());

			vector.PushBack(foo4);
			vector.PushBack(foo5);
			vector.PushBack(foo6);
			vector.PushBack(foo7);
			vector.PushBack(foo8);
			vector.PushBack(foo9);

			Assert::AreEqual(foo1, vector.Front());
			Assert::AreEqual(foo9, vector.Back());
			Assert::AreEqual(size_t(9), vector.Size());
			Assert::AreEqual(size_t(16), vector.Capacity());
		}

		TEST_METHOD(PopBack)
		{
			Vector<Foo> vector;

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			vector.PopBack();

			Assert::AreEqual(size_t(0), vector.Size());

			vector.PushBack(foo1);

			vector.PopBack();

			Assert::AreEqual(size_t(0), vector.Size());

			auto Front = [&vector]()
			{
				vector.Front();
			};

			Assert::ExpectException<std::runtime_error>(Front);

			auto Back = [&vector]()
			{
				vector.Back();
			};

			Assert::ExpectException<std::runtime_error>(Back);

			vector.PushBack(foo1);
			vector.PushBack(foo2);
			vector.PushBack(foo3);

			vector.PopBack();

			Assert::AreEqual(foo2, vector.Back());
			Assert::AreEqual(size_t(2), vector.Size());

			vector.PopBack();

			Assert::AreEqual(foo1, vector.Back());
			Assert::AreEqual(foo1, vector.Front());
			Assert::AreEqual(size_t(1), vector.Size());
		}

		TEST_METHOD(IsEmpty)
		{
			Vector<Foo> vector;
			Assert::AreEqual(true, vector.IsEmpty());

			Foo foo1{ 10 };
			vector.PushBack(foo1);
			Assert::AreEqual(false, vector.IsEmpty());
			vector.PopBack();
			Assert::AreEqual(true, vector.IsEmpty());
			vector.PopBack();
			Assert::AreEqual(true, vector.IsEmpty());
		}


		TEST_METHOD(Clear)
		{
			Vector<Foo> vector;

			vector.Clear();

			Assert::AreEqual(true, vector.IsEmpty());
			Assert::AreEqual(size_t(0), vector.Size());

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			vector.PushBack(foo1);

			vector.Clear();

			Assert::AreEqual(true, vector.IsEmpty());
			Assert::AreEqual(size_t(0), vector.Size());

			vector.PushBack(foo1);
			vector.PushBack(foo2);
			vector.PushBack(foo3);

			vector.Clear();

			Assert::AreEqual(true, vector.IsEmpty());
			Assert::AreEqual(size_t(0), vector.Size());
		}

		TEST_METHOD(CopyConstructor)
		{
			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };
			Foo foo4{ 40 };
			Foo foo5{ 50 };
			Foo foo6{ 60 };
			Foo foo7{ 70 };
			Foo foo8{ 80 };
			Foo foo9{ 90 };

			Vector<Foo> vector{ foo1, foo2, foo3, foo4, foo5, foo6, foo7, foo8, foo9};

			Assert::AreEqual(size_t(9), vector.Size());
			Assert::AreEqual(size_t(9), vector.Capacity());

			Vector<Foo> vector2(vector);

			Assert::AreEqual(size_t(9), vector2.Size());
			Assert::AreEqual(size_t(9), vector2.Capacity());
			Assert::AreEqual(foo1, vector2[0]);
			Assert::AreEqual(foo2, vector2[1]);
			Assert::AreEqual(foo3, vector2[2]);
			Assert::AreEqual(foo4, vector2[3]);
			Assert::AreEqual(foo5, vector2[4]);
			Assert::AreEqual(foo6, vector2[5]);
			Assert::AreEqual(foo7, vector2[6]);
			Assert::AreEqual(foo8, vector2[7]);
			Assert::AreEqual(foo9, vector2[8]);

		}

		TEST_METHOD(CopyAssignment)
		{
			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };
			Foo foo4{ 40 };
			Foo foo5{ 50 };
			Foo foo6{ 60 };
			Foo foo7{ 70 };
			Foo foo8{ 80 };
			Foo foo9{ 90 };

			Vector<Foo> vector{ foo1, foo2, foo3, foo4, foo5, foo6, foo7, foo8, foo9 };

			Assert::AreEqual(size_t(9), vector.Size());
			Assert::AreEqual(size_t(9), vector.Capacity());

			Vector<Foo> vector2;

			vector2 = vector;

			Assert::AreEqual(size_t(9), vector2.Size());
			Assert::AreEqual(size_t(9), vector2.Capacity());
			Assert::AreEqual(foo1, vector2[0]);
			Assert::AreEqual(foo2, vector2[1]);
			Assert::AreEqual(foo3, vector2[2]);
			Assert::AreEqual(foo4, vector2[3]);
			Assert::AreEqual(foo5, vector2[4]);
			Assert::AreEqual(foo6, vector2[5]);
			Assert::AreEqual(foo7, vector2[6]);
			Assert::AreEqual(foo8, vector2[7]);
			Assert::AreEqual(foo9, vector2[8]);
		}

		TEST_METHOD(AccessOperators)
		{
			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			Vector<Foo> vector{ foo1, foo2, foo3 };

			Assert::AreEqual(foo1, vector[0]);
			Assert::AreEqual(foo2, vector[1]);
			Assert::AreEqual(foo3, vector[2]);

			Assert::AreEqual(foo1, vector.At(0));
			Assert::AreEqual(foo2, vector.At(1));
			Assert::AreEqual(foo3, vector.At(2));


			auto brackets = [&vector]()
			{
				vector[3];
			};

			Assert::ExpectException<std::out_of_range>(brackets);


			auto At = [&vector]()
			{
				vector.At(3);
			};

			Assert::ExpectException<std::out_of_range>(At);

			const Vector<Foo> vector2{ foo1, foo2, foo3 };

			Assert::AreEqual(foo1, vector2[0]);
			Assert::AreEqual(foo2, vector2[1]);
			Assert::AreEqual(foo3, vector2[2]);

			Assert::AreEqual(foo1, vector2.At(0));
			Assert::AreEqual(foo2, vector2.At(1));
			Assert::AreEqual(foo3, vector2.At(2));


			auto brackets2 = [&vector2]()
			{
				vector2[3];
			};

			Assert::ExpectException<std::out_of_range>(brackets2);


			auto At2 = [&vector2]()
			{
				vector2.At(3);
			};

			Assert::ExpectException<std::out_of_range>(At2);
		}

		TEST_METHOD(MoveSemantics)
		{
			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };
			Foo foo4{ 40 };
			Foo foo5{ 50 };
			Foo foo6{ 60 };
			Foo foo7{ 70 };
			Foo foo8{ 80 };
			Foo foo9{ 90 };

			Vector<Foo> vector{ foo1, foo2, foo3, foo4, foo5, foo6, foo7, foo8, foo9 };

			Vector<Foo> vector2 = std::move(vector);

			Assert::AreEqual(size_t(9), vector2.Size());
			Assert::AreEqual(size_t(9), vector2.Capacity());
			Assert::AreEqual(foo1, vector2[0]);
			Assert::AreEqual(true, vector.IsEmpty());

			Vector<Foo> vector3{ foo9, foo8, foo7 };
			vector3 = std::move(vector2);

			Assert::AreEqual(size_t(9), vector3.Size());
			Assert::AreEqual(size_t(9), vector3.Capacity());
			Assert::AreEqual(foo1, vector3[0]);
			Assert::AreEqual(true, vector2.IsEmpty());
		}

		TEST_METHOD(ConstFrontAndBack)
		{

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };
			const Vector<Foo> vector;

			auto Front = [&vector]()
			{
				vector.Front();
			};

			Assert::ExpectException<std::runtime_error>(Front);

			auto Back = [&vector]()
			{
				vector.Back();
			};

			Assert::ExpectException<std::runtime_error>(Back);

			const Vector<Foo> vector2{ foo1, foo2, foo3 };

			Assert::AreEqual(foo1, vector2.Front());
			Assert::AreEqual(foo3, vector2.Back());
		}


		TEST_METHOD(IteratorConstructor)
		{

			Vector<Foo>::Iterator it;

			auto nullOwner = [&it]()
			{
				++it;
			};
			Assert::ExpectException<std::runtime_error>(nullOwner);

			auto ImproperIndex = [&it]()
			{
				*it;
			};
			Assert::ExpectException<std::runtime_error>(ImproperIndex);
		}

		TEST_METHOD(ConstIteratorConstructors)
		{
			Vector<Foo>::ConstIterator it;

			auto nullOwner = [&it]()
			{
				++it;
			};
			Assert::ExpectException<std::runtime_error>(nullOwner);

			auto ImproperIndex = [&it]()
			{
				*it;
			};
			Assert::ExpectException<std::runtime_error>(ImproperIndex);
		}

		TEST_METHOD(Find)
		{
			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };
			Foo foo4{ 40 };

			Vector<Foo> vector;

			Vector<Foo>::Iterator it = vector.Find(foo1);
			Assert::AreEqual(it, vector.end());

			Vector<Foo> vector2{ foo1, foo2, foo3 };
			it = vector2.Find(foo1);

			Assert::AreEqual(*it, foo1);

			it = vector2.Find(foo3);
			Assert::AreEqual(*it, foo3);

			it = vector2.Find(foo4);
			Assert::AreEqual(it, vector2.end());

			const Vector<Foo> vector3;

			Vector<Foo>::ConstIterator it2 = vector3.Find(foo1);
			Assert::AreEqual(it2, vector3.end());

			const Vector<Foo> vector4{ foo1, foo2, foo3 };
			it2 = vector4.Find(foo2);
			Assert::AreEqual(*it2, foo2);

			it2++;
			Assert::AreEqual(*it2, foo3);

			it2 = vector4.Find(foo4);
			Assert::AreEqual(it2, vector4.end());
		}

		TEST_METHOD(Remove)
		{
			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			Vector<Foo> vector;

			vector.Remove(foo1);

			Assert::AreEqual(vector.Size(), size_t(0));
			Assert::AreEqual(vector.begin(), vector.end());

			Vector<Foo> vector2{ foo1, foo2, foo3 };

			vector2.Remove(foo1);

			Assert::AreEqual(vector2.Size(), size_t(2));
			Assert::AreEqual(vector2.Front(), foo2);
			Assert::AreEqual(vector2.Back(), foo3);

			vector2.PushBack(foo1);
			
			vector2.Remove(foo3);

			Assert::AreEqual(vector2.Size(), size_t(2));
			Assert::AreEqual(vector2.Front(), foo2);
			Assert::AreEqual(vector2.Back(), foo1);

			vector2.PushBack(foo3);

			vector2.Remove(foo2);

			Assert::AreEqual(vector2.Size(), size_t(2));
			Assert::AreEqual(vector2.Front(), foo1);
			Assert::AreEqual(vector2.Back(), foo3);

			vector2.Remove(foo1);

			Assert::AreEqual(vector2.Size(), size_t(1));
			Assert::AreEqual(vector2.Front(), foo3);
			Assert::AreEqual(vector2.Back(), foo3);

			vector2.Remove(foo3);

			Assert::AreEqual(vector2.Size(), size_t(0));
		}

		TEST_METHOD(RangeRemove)
		{
			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };
			Foo foo4{ 40 };
			Foo foo5{ 50 };
			Foo foo6{ 60 };
			Foo foo7{ 70 };
			Foo foo8{ 80 };
			Foo foo9{ 90 };

			Vector<Foo> vector{ foo1, foo2, foo3, foo4, foo5, foo6, foo7, foo8, foo9 };

			Vector<Foo>::Iterator first = vector.begin();
			Vector<Foo>::Iterator last = vector.begin();

			first++;
			first++;

			Assert::AreEqual(*first, foo3);

			last++;
			last++;
			last++;
			last++;
			last++;

			Assert::AreEqual(*last, foo6);

			vector.Remove(last, first);

			Assert::AreEqual(vector[0], foo1);
			Assert::AreEqual(vector[8], foo9);
			Assert::AreEqual(size_t(9), vector.Size());

			vector.Remove(first, last);

			Assert::AreEqual(vector[0], foo1);
			Assert::AreEqual(vector[1], foo2);
			Assert::AreEqual(vector[2], foo6); 
			Assert::AreEqual(vector[3], foo7);
			Assert::AreEqual(vector[4], foo8);
			Assert::AreEqual(vector[5], foo9);
			Assert::AreEqual(size_t(6), vector.Size());

			Vector<Foo> vector2{ foo1, foo2, foo3, foo4, foo5, foo6, foo7, foo8, foo9 };

			Vector<Foo>::Iterator first2 = vector2.begin();
			Vector<Foo>::Iterator last2 = vector2.begin();
			last2++;

			vector2.Remove(first2, last2);
			Assert::AreEqual(foo2, vector2[0]);
			Assert::AreEqual(foo9, vector2[7]);
			Assert::AreEqual(size_t(8), vector2.Size());

			Vector<Foo> vector3{ foo1, foo2, foo3, foo4, foo5, foo6, foo7, foo8, foo9 };

			Vector<Foo>::Iterator first3 = vector3.begin();
			Vector<Foo>::Iterator last3 = vector3.end();

			first3++;
			first3++;

			vector3.Remove(first3, last3);

			Assert::AreEqual(foo1, vector3[0]);
			Assert::AreEqual(foo2, vector3[1]);
			Assert::AreEqual(size_t(2), vector3.Size());
		}

		TEST_METHOD(Iterator)
		{
			Vector<Foo> vector;

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			Assert::AreEqual(vector.begin(), vector.end());

			vector.PushBack(foo1);

			Assert::AreNotEqual(vector.begin(), vector.end());
			Vector<Foo>::Iterator it = vector.begin();
			Assert::AreEqual(*it, vector.Front());
			Assert::AreEqual(*it, vector.Back());

			Vector<Foo>::Iterator it2;

			Assert::AreNotEqual(it, it2);

			Vector<Foo> vector2;

			vector2.PushBack(foo1);

			Assert::AreNotEqual(vector.begin(), vector2.begin());

			vector.PushBack(foo2);
			vector.PushBack(foo3);

			Assert::AreEqual(*it, vector.Front());

			size_t count = 0;
			for (it = vector.begin(); it != vector.end(); ++it, ++count)
			{
				;
			}
			Assert::AreEqual(vector.Size(), count);

			count = 0;
			for (const Foo& value : vector)
			{
				value;
				count++;
			}
			Assert::AreEqual(vector.Size(), count);

			Vector<Foo> vector3{ foo1, foo2, foo3 };

			Vector<Foo>::Iterator it3 = vector3.begin();
			it3++;
			Assert::AreEqual(*it3, foo2);
		}

		TEST_METHOD(ConstIterator)
		{
			const Vector<Foo> vector;

			Assert::AreEqual(vector.begin(), vector.end());

			Foo foo1{ 10 };
			Foo foo2{ 20 };
			Foo foo3{ 30 };

			const Vector<Foo> vector2{ foo1 };

			Assert::AreNotEqual(vector2.begin(), vector2.end());
			Vector<Foo>::ConstIterator it = vector2.begin();
			Assert::AreEqual(*it, vector2.Front());
			Assert::AreEqual(*it, vector2.Back());

			const Vector<Foo> vector3{ foo1 , foo2, foo3 };

			Assert::AreEqual(*it, vector3.Front());

			Assert::AreNotEqual(vector2.begin(), vector3.begin());

			size_t count = 0;
			for (it = vector3.begin(); it != vector3.end(); ++it, ++count)
			{
				;
			}
			Assert::AreEqual(vector3.Size(), count);

			count = 0;
			for (const Foo& value : vector3)
			{
				value;
				count++;
			}
			Assert::AreEqual(vector3.Size(), count);

			Vector<Foo> vector4{ foo1, foo2, foo3 };

			Vector<Foo>::Iterator it4 = vector4.begin();
			Vector<Foo>::ConstIterator cIterator(it4);
			
			Assert::AreEqual(*cIterator, *vector4.begin());

		}

		TEST_METHOD(CBeginCEnd)
		{
			const Vector<Foo> vector;

			Assert::AreEqual(vector.cbegin(), vector.cend());

			Foo foo1{ 10 };

			const Vector<Foo> vector2{ foo1 };

			Assert::AreNotEqual(vector2.cbegin(), vector2.cend());
			Assert::AreEqual(*vector2.cbegin(), vector2.Front());
		}

		TEST_METHOD(SpecialReserve)
		{
			Foo foo1{ 10 };

			Vector<Foo> vector;
			vector.Reserve(20);

			Assert::AreEqual(size_t(20), vector.Capacity());

			for (int i = 0; i < 22; i++)
			{
				vector.PushBack(foo1);
			}

			Assert::AreEqual(size_t(40), vector.Capacity());
		}

	private:
		static _CrtMemState startMemState;	
	};

	_CrtMemState VectorTests::startMemState;
}