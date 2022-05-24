#include "pch.h"
#include "Foo.h"

namespace LibraryDesktopUnitTests
{
	RTTI_DEFINITIONS(Foo)

	Foo::Foo(std::int32_t data) :
		mData(new int32_t(data))
	{

	}

	Foo::Foo(const Foo& other) :
		mData(new int32_t(*other.mData))
	{

	}

	Foo& Foo::operator=(const Foo& other)
	{
		if (this != &other)
		{
			*mData = *other.mData;
		}

		return *this;
	}

	Foo::~Foo()
	{
		delete mData;
	}

	std::int32_t& Foo::Data()
	{
		return *mData;
	}

	const std::int32_t& Foo::Data() const
	{
		return *mData;
	}

	bool Foo::Equals(const RTTI* rhs) const
	{
		if (rhs->Is(Foo::TypeIdClass()))
		{ 
			return *mData == *rhs->As<Foo>()->mData;
		}
		return false;
	}
	 
	bool Foo::operator==(const Foo& rhs) const
	{
		//if (mData == rhs.mData)
		//{
		//	return true;
		//}

		return (*mData == *rhs.mData);
	}

	bool Foo::operator!=(const Foo& rhs) const
	{
		return !operator==(rhs);
	}
}