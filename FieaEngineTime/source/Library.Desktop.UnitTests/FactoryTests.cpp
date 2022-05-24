#include "pch.h"
#include "CppUnitTest.h"
#include "Factory.h"
#include "Foo.h"
#include "AttributedFoo.h"
#include "Scope.h"
#include "ToStringSpecializationsFactory.h"
#include <stdexcept>
#include <crtdbg.h>
#include <string>
#include <gsl/pointers>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std::string_literals;

namespace LibraryDesktopUnitTests
{
	TEST_CLASS(FactoryTests)
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
			Assert::AreEqual(size_t(0), Factory<RTTI>::GetFactories().Size());
		}

		TEST_METHOD(AddRemoveFactory)
		{
			const Factory<RTTI>* foundFactory = Factory<RTTI>::Find("Foo");
			Assert::IsNull(foundFactory);
			Assert::AreEqual(size_t(0), Factory<RTTI>::GetFactories().Size());
			
			{
				const FactoryFoo fooFactory;
				Assert::AreEqual(size_t(1), Factory<RTTI>::GetFactories().Size());
				foundFactory = Factory<RTTI>::Find("Foo");
				Assert::AreEqual(&fooFactory, static_cast<const FactoryFoo*>(foundFactory));
			}

			Assert::AreEqual(size_t(0), Factory<RTTI>::GetFactories().Size());
			foundFactory = Factory<RTTI>::Find("Foo");
		}

		TEST_METHOD(ProductCreation)
		{
			RTTI* rtti = Factory<RTTI>::Create("Foo");
			Assert::IsNull(rtti);

			{
				FactoryFoo fooFactory;
				rtti = Factory<RTTI>::Create("Foo");
				Assert::IsNotNull(rtti);
				Foo* foo = rtti->As<Foo>();
				Assert::IsNotNull(foo);

				delete foo;
			}

			rtti = Factory<RTTI>::Create("Foo");
			Assert::IsNull(rtti);
		}

		TEST_METHOD(AttributedFooTest)
		{
			Scope* scope = Factory<Scope>::Create("AttributedFoo");
			Assert::IsNull(scope);

			{
				FactoryAttributedFoo afFactory;
				scope = Factory<Scope>::Create("AttributedFoo");
				Assert::IsNotNull(scope);
				AttributedFoo* af = scope->As<AttributedFoo>();
				Assert::IsNotNull(af);

				delete af;
			}

			scope = Factory<Scope>::Create("Foo");
			Assert::IsNull(scope);
		}

	private:
		static _CrtMemState startMemState;
	};
	_CrtMemState FactoryTests::startMemState;
}