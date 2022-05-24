#pragma once

#include <cstdint>
#include "RTTI.h"
#include "Factory.h"

namespace LibraryDesktopUnitTests
{
	class Foo : public FieaGameEngine::RTTI
	{

		RTTI_DECLARATIONS(Foo, RTTI)

	public:
		Foo() = default;
		Foo(std::int32_t data);
		Foo(const Foo& other);
		Foo& operator=(const Foo& other);
		virtual ~Foo();

		std::int32_t& Data();
		const std::int32_t& Data() const;

		bool Equals(const RTTI* rhs) const override;

		bool operator==(const Foo& rhs) const;
		bool operator!=(const Foo& rhs) const;

	private:
		std::int32_t* mData{ nullptr };
	};

	ConcreteFactory(Foo, FieaGameEngine::RTTI)
}