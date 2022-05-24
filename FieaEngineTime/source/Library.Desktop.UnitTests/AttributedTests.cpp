#include "pch.h"
#include "CppUnitTest.h"
#include "AttributedFoo.h"
#include "AttributedBar.h"
#include "Foo.h"
#include "ToStringSpecializationsAttributed.h"
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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopUnitTests
{
	TEST_MODULE_INITIALIZE(TestModuleInitialize)
	{
		RegisterType(AttributedFoo, Attributed);
		RegisterType(AttributedBar, Attributed);
		RegisterType(GameObject, Attributed);
		RegisterType(Avatar, GameObject);
		RegisterType(Action, Attributed);
		RegisterType(ActionIncrement, Action);
		RegisterType(ActionCreateAction, Action);
		RegisterType(ActionDestroyAction, Action);
		RegisterType(ActionList, Action);
		RegisterType(ActionListIf, ActionList);
	}

	TEST_MODULE_CLEANUP(TestModuleCleanup)
	{
		TypeRegistry::Clear();
	}

	TEST_CLASS(AttributeTests)
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
			AttributedFoo foo;

			Assert::IsTrue(foo.IsAttribute("ExternalInteger"));
			Assert::IsTrue(foo.IsAttribute("ExternalFloat"));
			Assert::IsTrue(foo.IsAttribute("ExternalString"));
			Assert::IsTrue(foo.IsAttribute("ExternalVector"));
			Assert::IsTrue(foo.IsAttribute("ExternalMatrix"));
			Assert::IsTrue(foo.IsAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(foo.IsAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo.IsAttribute("ExternalMatrixArray"));
			Assert::IsTrue(foo.IsAttribute("NestedScope"));
			Assert::IsTrue(foo.IsAttribute("NestedScopeArray"));

			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalMatrix"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalMatrixArray"));
			Assert::IsTrue(foo.IsPrescribedAttribute("NestedScope"));
			Assert::IsTrue(foo.IsPrescribedAttribute("NestedScopeArray"));

			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalFloat"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalString"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalVector"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalMatrix"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalIntegerArray"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalStringArray"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalVectorArray"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalMatrixArray"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScope"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScopeArray"));

			Assert::IsFalse(foo.IsAttribute("NotAnAttribute"));
		}

		TEST_METHOD(AppendAuxiliary)
		{
			AttributedFoo foo;
			foo.AppendAuxiliaryAttribute("AuxiliaryAttribute");

			Assert::IsTrue(foo.IsAttribute("AuxiliaryAttribute"));
			Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxiliaryAttribute"));
			Assert::IsFalse(foo.IsPrescribedAttribute("AuxiliaryAttribute"));

			auto append = [&foo]()
			{
				foo.AppendAuxiliaryAttribute("ExternalMatrix");
			};
			Assert::ExpectException<std::runtime_error>(append);
		}

		TEST_METHOD(Populate)
		{
			auto unknown = []()
			{
				AttributedBar bar;
			};
			Assert::ExpectException<std::runtime_error>(unknown);
		}

		TEST_METHOD(CopyShenanigans)
		{
			AttributedFoo foo;
			foo.AppendAuxiliaryAttribute("AuxiliaryAttribute");
			Assert::IsTrue(foo.IsAttribute("AuxiliaryAttribute"));
			Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxiliaryAttribute"));
			Assert::IsFalse(foo.IsPrescribedAttribute("AuxiliaryAttribute"));

			AttributedFoo foo1(foo);

			Assert::IsTrue(foo1.IsAttribute("ExternalInteger"));
			Assert::IsTrue(foo1.IsAttribute("ExternalFloat"));
			Assert::IsTrue(foo1.IsAttribute("ExternalString"));
			Assert::IsTrue(foo1.IsAttribute("ExternalVector"));
			Assert::IsTrue(foo1.IsAttribute("ExternalMatrix"));
			Assert::IsTrue(foo1.IsAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo1.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo1.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(foo1.IsAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo1.IsAttribute("ExternalMatrixArray"));
			Assert::IsTrue(foo1.IsAttribute("NestedScope"));
			Assert::IsTrue(foo1.IsAttribute("NestedScopeArray"));

			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalMatrix"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalMatrixArray"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("NestedScope"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("NestedScopeArray"));

			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalFloat"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalString"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalVector"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalMatrix"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalIntegerArray"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalStringArray"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalVectorArray"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalMatrixArray"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("NestedScope"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("NestedScopeArray"));

			Assert::IsFalse(foo1.IsAttribute("NotAnAttribute"));

			Assert::IsTrue(foo1.IsAttribute("AuxiliaryAttribute"));
			Assert::IsTrue(foo1.IsAuxiliaryAttribute("AuxiliaryAttribute"));
			Assert::IsFalse(foo1.IsPrescribedAttribute("AuxiliaryAttribute"));

			Assert::AreEqual(&foo1.ExternalFloat, &foo1.Find("ExternalFloat")->GetFloat());
			Assert::AreEqual(foo, foo1);

			AttributedFoo foo2;
			foo2 = foo;

			Assert::IsTrue(foo2.IsAttribute("ExternalInteger"));
			Assert::IsTrue(foo2.IsAttribute("ExternalFloat"));
			Assert::IsTrue(foo2.IsAttribute("ExternalString"));
			Assert::IsTrue(foo2.IsAttribute("ExternalVector"));
			Assert::IsTrue(foo2.IsAttribute("ExternalMatrix"));
			Assert::IsTrue(foo2.IsAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo2.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo2.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(foo2.IsAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo2.IsAttribute("ExternalMatrixArray"));
			Assert::IsTrue(foo2.IsAttribute("NestedScope"));
			Assert::IsTrue(foo2.IsAttribute("NestedScopeArray"));

			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalMatrix"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalMatrixArray"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("NestedScope"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("NestedScopeArray"));

			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalFloat"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalString"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalVector"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalMatrix"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalIntegerArray"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalStringArray"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalVectorArray"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalMatrixArray"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("NestedScope"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("NestedScopeArray"));

			Assert::IsFalse(foo2.IsAttribute("NotAnAttribute"));

			Assert::IsTrue(foo2.IsAttribute("AuxiliaryAttribute"));
			Assert::IsTrue(foo2.IsAuxiliaryAttribute("AuxiliaryAttribute"));
			Assert::IsFalse(foo2.IsPrescribedAttribute("AuxiliaryAttribute"));

			Assert::AreEqual(&foo2.ExternalFloat, &foo2.Find("ExternalFloat")->GetFloat());
			Assert::AreEqual(foo, foo2);
		}

		TEST_METHOD(MoveShenanigans)
		{
			AttributedFoo foo;
			foo.AppendAuxiliaryAttribute("AuxiliaryAttribute");
			Assert::IsTrue(foo.IsAttribute("AuxiliaryAttribute"));
			Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxiliaryAttribute"));
			Assert::IsFalse(foo.IsPrescribedAttribute("AuxiliaryAttribute"));

			AttributedFoo foo1(std::move(foo));

			Assert::IsTrue(foo1.IsAttribute("ExternalInteger"));
			Assert::IsTrue(foo1.IsAttribute("ExternalFloat"));
			Assert::IsTrue(foo1.IsAttribute("ExternalString"));
			Assert::IsTrue(foo1.IsAttribute("ExternalVector"));
			Assert::IsTrue(foo1.IsAttribute("ExternalMatrix"));
			Assert::IsTrue(foo1.IsAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo1.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo1.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(foo1.IsAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo1.IsAttribute("ExternalMatrixArray"));
			Assert::IsTrue(foo1.IsAttribute("NestedScope"));
			Assert::IsTrue(foo1.IsAttribute("NestedScopeArray"));

			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalMatrix"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("ExternalMatrixArray"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("NestedScope"));
			Assert::IsTrue(foo1.IsPrescribedAttribute("NestedScopeArray"));

			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalFloat"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalString"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalVector"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalMatrix"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalIntegerArray"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalStringArray"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalVectorArray"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("ExternalMatrixArray"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("NestedScope"));
			Assert::IsFalse(foo1.IsAuxiliaryAttribute("NestedScopeArray"));

			Assert::IsFalse(foo1.IsAttribute("NotAnAttribute"));

			Assert::IsTrue(foo1.IsAttribute("AuxiliaryAttribute"));
			Assert::IsTrue(foo1.IsAuxiliaryAttribute("AuxiliaryAttribute"));
			Assert::IsFalse(foo1.IsPrescribedAttribute("AuxiliaryAttribute"));

			Assert::AreEqual(&foo1.ExternalFloat, &foo1.Find("ExternalFloat")->GetFloat());

			AttributedFoo foo2;
			foo2 = std::move(foo1);

			Assert::IsTrue(foo2.IsAttribute("ExternalInteger"));
			Assert::IsTrue(foo2.IsAttribute("ExternalFloat"));
			Assert::IsTrue(foo2.IsAttribute("ExternalString"));
			Assert::IsTrue(foo2.IsAttribute("ExternalVector"));
			Assert::IsTrue(foo2.IsAttribute("ExternalMatrix"));
			Assert::IsTrue(foo2.IsAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo2.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo2.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(foo2.IsAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo2.IsAttribute("ExternalMatrixArray"));
			Assert::IsTrue(foo2.IsAttribute("NestedScope"));
			Assert::IsTrue(foo2.IsAttribute("NestedScopeArray"));

			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalMatrix"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("ExternalMatrixArray"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("NestedScope"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("NestedScopeArray"));

			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalFloat"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalString"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalVector"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalMatrix"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalIntegerArray"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalStringArray"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalVectorArray"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("ExternalMatrixArray"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("NestedScope"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("NestedScopeArray"));

			Assert::IsFalse(foo2.IsAttribute("NotAnAttribute"));

			Assert::IsTrue(foo2.IsAttribute("AuxiliaryAttribute"));
			Assert::IsTrue(foo2.IsAuxiliaryAttribute("AuxiliaryAttribute"));
			Assert::IsFalse(foo2.IsPrescribedAttribute("AuxiliaryAttribute"));

			Assert::AreEqual(&foo2.ExternalFloat, &foo2.Find("ExternalFloat")->GetFloat());		
		}

	private:
		static _CrtMemState startMemState;
	};
	_CrtMemState AttributeTests::startMemState;
}