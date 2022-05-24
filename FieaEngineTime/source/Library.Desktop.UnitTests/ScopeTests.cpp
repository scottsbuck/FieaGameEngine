#include "pch.h"
#include "CppUnitTest.h"
#include "Scope.h"
#include "Foo.h"
#include "ToStringSpecializationsScope.h"
#include <stdexcept>
#include <crtdbg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopUnitTests
{
	TEST_CLASS(ScopeTests)
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

		TEST_METHOD(Constructors)
		{
			{
				Scope scope;
				bool booleman;
				if (scope.Find("pepega") == nullptr)
				{
					booleman = true;
				}
				Assert::AreEqual(booleman, true);
			}
		}

		TEST_METHOD(FindAndAppend)
		{
			Scope scope;
			Datum* d = &scope.Append("GAMING");
			d->PushBack(8);
			Datum* d1 = &scope.Append("poog");
			d1->PushBack(8.0f);
			Datum* d2 = &scope.Append("fucking tilted lmao");
			d2->PushBack("lmao");

			Datum* d3 = scope.Find("GAMING");
			Assert::AreEqual(d3->GetInt(), 8);

			d3 = &scope.Append("fucking tilted lmao");
			Assert::AreEqual(d3->GetString(), std::string("lmao"));

			d3 = scope.Find("poog");
			Assert::AreEqual(d3, d1);
			Assert::AreEqual(d3->Type(), d1->Type());
			Assert::AreEqual(d3->GetFloat(), d1->GetFloat());

			Datum* d4 = scope.Find("banana");
			Datum* d5 = nullptr;
			Assert::AreEqual(d4, d5);

			const Scope* scope1 = &scope;

			const Datum* d6 = scope1->Find("poog");
			Assert::AreEqual(d6->GetFloat(), 8.0f);

			d6 = scope1->Find("banana");
			const Datum* d7 = nullptr;
			Assert::AreEqual(d6, d7);
		}

		TEST_METHOD(AppendScope)
		{
			{
				Scope scope;
				Datum* d = new Datum;
				*d = scope.AppendScope("GAMING");
				Datum* da = &d->GetScope()->Append("lumao");
				da->PushBack(8);
				Datum* d1 = new Datum;
				*d1 = scope.AppendScope("GAMING");
				Datum* da2 = &d1->GetScope()->Append("gottem");
				da2->PushBack(8.0f);
				Assert::AreEqual(scope.Find("GAMING")->GetScope(0)->Find("lumao")->GetInt(), 8);
				Assert::AreEqual(scope.Find("GAMING")->GetScope(1)->Find("gottem")->GetFloat(), 8.0f);
				delete d;
				delete d1;
			}

			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Datum* d1 = &scope.Append("poog");
				d1->PushBack(8.0f);
				Datum* d2 = &scope.Append("fucking tilted lmao");
				d2->PushBack("lmao");

				auto append = [&scope]()
				{
					scope.AppendScope("GAMING");
				};
				Assert::ExpectException<std::runtime_error>(append);
			}
		}

		TEST_METHOD(Adopt)
		{
			{
				Scope scope;
				Scope* scope1 = new Scope;
				Datum& d = scope1->Append("GAMING");
				d.PushBack(8);
				scope.Adopt("GORTED", *scope1);
				
				Assert::AreEqual(scope.Find("GORTED")->GetScope()->Find("GAMING")->GetInt(), 8);

				Scope scope2;
				scope2.Adopt("GORTEM", *scope1);
				Assert::AreEqual(scope2.Find("GORTEM")->GetScope()->Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scope1->GetParent(), &scope2);
			}

			{
				Scope scope;
				Scope* scope1 = new Scope;
				Datum* d = &scope1->Append("GAMING");
				d->PushBack(8);
				scope.Adopt("GORTED", *scope1);

				Assert::AreEqual(scope.Find("GORTED")->GetScope()->Find("GAMING")->GetInt(), 8);

				Scope* scope2 = new Scope;
				Datum* d1 = &scope2->Append("baanan");
				d1->PushBack(8);
				scope.Adopt("GORTED", *scope2);

				Assert::AreEqual(scope.Find("GORTED")->GetScope(1)->Find("baanan")->GetInt(), 8);
			}

			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Scope* scope1 = new Scope;
				Datum* d1 = &scope1->Append("BABABA");
				d1->PushBack(8);

				auto adopt = [&scope, &scope1]()
				{
					scope.Adopt("GAMING", *scope1);
				};
				Assert::ExpectException<std::runtime_error>(adopt);
				delete scope1;
			}
		}

		TEST_METHOD(Search)
		{
			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Datum* d1 = &scope.Append("poog");
				d1->PushBack(8.0f);
				Datum* d2 = &scope.Append("fucking tilted lmao");
				d2->PushBack("lmao");

				Datum* d3 = scope.Search("poog");
				Assert::AreEqual(d1, d3);

				Datum* d4 = new Datum;
				*d4 = scope.AppendScope("pogfish");
				
				Datum* d5 = d4->GetScope()->Search("fucking tilted lmao");
				Assert::AreEqual(d5, d2);

				Datum* d6 = scope.Search("brUther");
				Assert::IsNull(d6);

				delete d4;
			}

			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Datum* d1 = &scope.Append("poog");
				d1->PushBack(8.0f);
				Datum* d2 = &scope.Append("fucking tilted lmao");
				d2->PushBack("lmao");

				Scope* scope1;

				Datum* d3 = scope.Search("poog", scope1);
				Assert::AreEqual(d1, d3);
				Assert::AreEqual(scope1, &scope);

				Datum* d4 = new Datum;
				*d4 = scope.AppendScope("pogfish");

				Datum* d5 = d4->GetScope()->Search("fucking tilted lmao", scope1);
				Assert::AreEqual(d5, d2);
				Assert::AreEqual(scope1, &scope);

				Datum* d6 = scope.Search("brUther", scope1);
				Assert::IsNull(d6);
				Assert::IsNull(scope1);

				delete d4;
			}

			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Datum* d1 = &scope.Append("poog");
				d1->PushBack(8.0f);
				Datum* d2 = &scope.Append("fucking tilted lmao");
				d2->PushBack("lmao");

				const Scope* scopePtr = &scope;

				const Datum* d3 = scopePtr->Search("poog");
				Assert::AreEqual(d3->GetFloat(), 8.0f);

				Datum* d4 = new Datum;
				*d4 = scope.AppendScope("pogfish");

				const Datum* d7 = d4;
				scopePtr = &scope;

				const Datum* d5 = d7->GetScope()->Search("fucking tilted lmao");
				Assert::AreEqual(d5->GetString(), std::string("lmao"));

				const Datum* d6 = scopePtr->Search("brUther");
				Assert::IsNull(d6);

				delete d4;
			}

			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Datum* d1 = &scope.Append("poog");
				d1->PushBack(8.0f);
				Datum* d2 = &scope.Append("fucking tilted lmao");
				d2->PushBack("lmao");

				const Scope* scope1;

				const Scope* scopePtr = &scope;

				const Datum* d3 = scopePtr->Search("poog", scope1);
				Assert::AreEqual(d3->GetFloat(), 8.0f);
				Assert::AreEqual(scope1, scopePtr);

				Datum* d4 = new Datum;
				*d4 = scope.AppendScope("pogfish");

				const Datum* d7 = d4;

				const Datum* d5 = d7->GetScope()->Search("fucking tilted lmao", scope1);
				Assert::AreEqual(d5->GetString(), std::string("lmao"));
				Assert::AreEqual(scope1, scopePtr);

				const Datum* d6 = scope.Search("brUther", scope1);
				Assert::IsNull(d6);
				Assert::IsNull(scope1);

				delete d4;
			}
		}

		TEST_METHOD(FindContainedScope)
		{
			Scope scope;
			Datum* d = &scope.Append("GAMING");
			d->PushBack(8);
			Datum* d1 = &scope.Append("poog");
			d1->PushBack(8.0f);
			Datum* d2 = &scope.Append("fucking tilted lmao");
			d2->PushBack("lmao");

			Scope* scoped = new Scope;

			auto[gaming, datum] = scope.FindContainedScope(scoped);

			Assert::IsNull(datum);
			delete scoped;
		}

		TEST_METHOD(CopyShenanigans)
		{
			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Datum* d1 = &scope.Append("poog");
				d1->PushBack(8.0f);
				Datum* d2 = &scope.Append("fucking tilted lmao");
				d2->PushBack("lmao");

				Scope* s;
				s = &scope.AppendScope("pogGaming");
				Datum* da = &s->Append("lumao");
				da->PushBack(8);

				Assert::AreEqual(scope.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scope.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scope.Find("fucking tilted lmao")->GetString(), std::string("lmao"));
				Assert::AreEqual(scope.Find("pogGaming")->GetScope()->Find("lumao")->GetInt(), 8);

				Scope scopeCopy(scope);

				Assert::AreEqual(scopeCopy.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scopeCopy.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scopeCopy.Find("fucking tilted lmao")->GetString(), std::string("lmao"));
				Assert::AreEqual(scopeCopy.Find("pogGaming")->GetScope()->Find("lumao")->GetInt(), 8);
			}


			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Datum* d1 = &scope.Append("poog");
				d1->PushBack(8.0f);
				Datum* d2 = &scope.Append("fucking tilted lmao");
				d2->PushBack("lmao");

				Scope* s;
				s = &scope.AppendScope("pogGaming");
				Datum* da = &s->Append("lumao");
				da->PushBack(8);

				Assert::AreEqual(scope.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scope.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scope.Find("fucking tilted lmao")->GetString(), std::string("lmao"));
				Assert::AreEqual(scope.Find("pogGaming")->GetScope()->Find("lumao")->GetInt(), 8);

				Scope scopeCopy;
				scopeCopy = scope;

				Assert::AreEqual(scopeCopy.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scopeCopy.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scopeCopy.Find("fucking tilted lmao")->GetString(), std::string("lmao"));
				Assert::AreEqual(scopeCopy.Find("pogGaming")->GetScope()->Find("lumao")->GetInt(), 8);
			}
		}

		TEST_METHOD(MoveShenanigans)
		{
			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Datum* d1 = &scope.Append("poog");
				d1->PushBack(8.0f);
				Datum* d2 = &scope.Append("fucking tilted lmao");
				d2->PushBack("lmao");
				Scope* s;
				s = &scope.AppendScope("pogGaming");
				Datum* da = &s->Append("lumao");
				da->PushBack(8);

				Assert::AreEqual(scope.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scope.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scope.Find("fucking tilted lmao")->GetString(), std::string("lmao"));
				Assert::AreEqual(scope.Find("pogGaming")->GetScope()->Find("lumao")->GetInt(), 8);

				Scope scopeMove(std::move(scope));

				Assert::AreEqual(scopeMove.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scopeMove.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scopeMove.Find("fucking tilted lmao")->GetString(), std::string("lmao"));
				Assert::AreEqual(scopeMove.Find("pogGaming")->GetScope()->Find("lumao")->GetInt(), 8);
			}

			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Datum* d1 = &scope.Append("poog");
				d1->PushBack(8.0f);
				Datum* d2 = &scope.Append("fucking tilted lmao");
				d2->PushBack("lmao");
				Scope& s = scope.AppendScope("pogGaming");
				Datum* da = &s.Append("lumao");
				da->PushBack(8);

				Assert::AreEqual(scope.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scope.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scope.Find("fucking tilted lmao")->GetString(), std::string("lmao"));
				Assert::AreEqual(scope.Find("pogGaming")->GetScope()->Find("lumao")->GetInt(), 8);

				Scope* scopeMove = new Scope(std::move(s));

				Assert::AreEqual(scopeMove->Find("lumao")->GetInt(), 8);
				delete &s;
			}

			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Datum* d1 = &scope.Append("poog");
				d1->PushBack(8.0f);
				Datum* d2 = &scope.Append("fucking tilted lmao");
				d2->PushBack("lmao");
				Scope* s;
				s = &scope.AppendScope("pogGaming");
				Datum* da = &s->Append("lumao");
				da->PushBack(8);

				Assert::AreEqual(scope.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scope.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scope.Find("fucking tilted lmao")->GetString(), std::string("lmao"));
				Assert::AreEqual(scope.Find("pogGaming")->GetScope()->Find("lumao")->GetInt(), 8);

				Scope scopeMove;
				scopeMove = std::move(scope);

				Assert::AreEqual(scopeMove.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scopeMove.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scopeMove.Find("fucking tilted lmao")->GetString(), std::string("lmao"));
				Assert::AreEqual(scopeMove.Find("pogGaming")->GetScope()->Find("lumao")->GetInt(), 8);
			}

			{
				Scope scope;
				Datum* d = &scope.Append("GAMING");
				d->PushBack(8);
				Datum* d1 = &scope.Append("poog");
				d1->PushBack(8.0f);
				Datum* d2 = &scope.Append("fucking tilted lmao");
				d2->PushBack("lmao");
				Scope& s = scope.AppendScope("pogGaming");
				Datum* da = &s.Append("lumao");
				da->PushBack(8);

				Assert::AreEqual(scope.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scope.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scope.Find("fucking tilted lmao")->GetString(), std::string("lmao"));
				Assert::AreEqual(scope.Find("pogGaming")->GetScope()->Find("lumao")->GetInt(), 8);

				Scope* scopeMove = new Scope();
				*scopeMove = std::move(s);

				Assert::AreEqual(scopeMove->Find("lumao")->GetInt(), 8);
				delete& s;
			}
		}

		TEST_METHOD(Operators)
		{
			{
				Scope scope;
				Datum* d = &scope["GAMING"];
				d->PushBack(8);
				Datum* d1 = &scope["poog"];
				d1->PushBack(8.0f);
				Datum* d2 = &scope["fucking tilted lmao"];
				d2->PushBack("lmao");

				Assert::AreEqual(scope.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scope.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scope.Find("fucking tilted lmao")->GetString(), std::string("lmao"));

				Datum d3 = scope[0];
				Assert::AreEqual(d3.GetInt(), 8);

				const Scope* scope1 = &scope;
				const Datum d4 = scope1->operator[](0);

				scope.AppendScope("pepega");

				Scope scopeCopy(scope);

				bool garbage = false;
				if (scopeCopy == scope)
				{
					garbage = true;
				}
				Assert::IsTrue(garbage);
			}

			{
				Scope scope;
				Datum* d = &scope["GAMING"];
				d->PushBack(8);
				Datum* d1 = &scope["poog"];
				d1->PushBack(8.0f);
				Datum* d2 = &scope["fucking tilted lmao"];
				d2->PushBack("lmao");

				Assert::AreEqual(scope.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scope.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scope.Find("fucking tilted lmao")->GetString(), std::string("lmao"));

				scope.AppendScope("pepega");

				Scope scopeCopy(scope);

				scopeCopy.AppendScope("pepega");

				bool garbage = false;
				if (scopeCopy != scope)
				{
					garbage = true;
				}
				Assert::IsTrue(garbage);
			}

			{
				Scope scope;
				Datum* d = &scope["GAMING"];
				d->PushBack(8);
				Datum* d1 = &scope["poog"];
				d1->PushBack(8.0f);
				Datum* d2 = &scope["fucking tilted lmao"];
				d2->PushBack("lmao");

				Assert::AreEqual(scope.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scope.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scope.Find("fucking tilted lmao")->GetString(), std::string("lmao"));

				scope.AppendScope("pepega");

				Scope scopeCopy(scope);

				scopeCopy.Find("pepega")->GetScope(0)->Append("dumpster");

				bool garbage = false;
				if (scopeCopy != scope)
				{
					garbage = true;
				}
				Assert::IsTrue(garbage);
			}

			{
				Scope scope;
				Datum* d = &scope["GAMING"];
				d->PushBack(8);
				Datum* d1 = &scope["poog"];
				d1->PushBack(8.0f);
				Datum* d2 = &scope["fucking tilted lmao"];
				d2->PushBack("lmao");

				Assert::AreEqual(scope.Find("GAMING")->GetInt(), 8);
				Assert::AreEqual(scope.Find("poog")->GetFloat(), 8.0f);
				Assert::AreEqual(scope.Find("fucking tilted lmao")->GetString(), std::string("lmao"));

				scope.AppendScope("pepega");

				Scope scopeCopy(scope);

				d1 = scopeCopy.Find("poog");
				d1->PushBack(8.1f);

				bool garbage = false;
				if (scopeCopy != scope)
				{
					garbage = true;
				}
				Assert::IsTrue(garbage);
			}
		}

		TEST_METHOD(Ancestor)
		{
			Scope scope;
			Datum* d = &scope["GAMING"];
			d->PushBack(8);
			Datum* d1 = &scope["poog"];
			d1->PushBack(8.0f);
			Datum* d2 = &scope["fucking tilted lmao"];
			d2->PushBack("lmao");

			Scope* scoped = &scope.AppendScope("pepega");
			Scope* scopeder = &scoped->AppendScope("anotherone");

			Assert::IsTrue(scope.IsAncestorOf(*scopeder));
		}

		TEST_METHOD(Equals)
		{
			Scope scope;
			Datum* d = &scope["GAMING"];
			d->PushBack(8);
			Datum* d1 = &scope["poog"];
			d1->PushBack(8.0f);
			Datum* d2 = &scope["fucking tilted lmao"];
			d2->PushBack("lmao");

			Assert::AreEqual(scope.Find("GAMING")->GetInt(), 8);
			Assert::AreEqual(scope.Find("poog")->GetFloat(), 8.0f);
			Assert::AreEqual(scope.Find("fucking tilted lmao")->GetString(), std::string("lmao"));

			Datum d3 = scope[0];
			Assert::AreEqual(d3.GetInt(), 8);

			const Scope* scope1 = &scope;
			const Datum d4 = scope1->operator[](0);

			scope.AppendScope("pepega");

			Scope scopeCopy(scope);

			bool garbage = false;
			if (scopeCopy.Equals(&scope))
			{
				garbage = true;
			}
			Assert::IsTrue(garbage);
		}

	private:
		static _CrtMemState startMemState;
	};
	_CrtMemState ScopeTests::startMemState;
}
