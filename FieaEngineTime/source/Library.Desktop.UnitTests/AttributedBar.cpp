#include "pch.h"
#include "AttributedBar.h"

using namespace FieaGameEngine;

namespace LibraryDesktopUnitTests
{
    RTTI_DEFINITIONS(AttributedBar)

        AttributedBar::AttributedBar() :
        Attributed(AttributedBar::TypeIdClass())
    {

    }

    gsl::owner<AttributedBar*> AttributedBar::Clone() const
    {
        return new AttributedBar(*this);
    }

    bool AttributedBar::Equals(const FieaGameEngine::RTTI* rhs) const
    {
        const auto rhsFoo = rhs->As<AttributedBar>();
        if (rhsFoo == nullptr)
        {
            return false;
        }

        return ExternalInteger == rhsFoo->ExternalInteger &&
            ExternalFloat == rhsFoo->ExternalFloat &&
            ExternalString == rhsFoo->ExternalString &&
            ExternalVector == rhsFoo->ExternalVector &&
            ExternalMatrix == rhsFoo->ExternalMatrix &&
            std::equal(std::begin(ExternalIntegerArray), std::end(ExternalIntegerArray), std::begin(rhsFoo->ExternalIntegerArray)) &&
            std::equal(std::begin(ExternalFloatArray), std::end(ExternalFloatArray), std::begin(rhsFoo->ExternalFloatArray)) &&
            std::equal(std::begin(ExternalStringArray), std::end(ExternalStringArray), std::begin(rhsFoo->ExternalStringArray)) &&
            std::equal(std::begin(ExternalVectorArray), std::end(ExternalVectorArray), std::begin(rhsFoo->ExternalVectorArray)) &&
            std::equal(std::begin(ExternalMatrixArray), std::end(ExternalMatrixArray), std::begin(rhsFoo->ExternalMatrixArray)) &&
            *Find("NestedScope") == *(*rhsFoo).Find("NestedScope");
    }

    std::string AttributedBar::ToString() const
    {
        return "AttributedFoo";
    }

    const Vector<Signature> AttributedBar::Signatures()
    {
        return Vector<FieaGameEngine::Signature>
        {
            { "ExternalInteger", Datum::DatumTypes::Integer, 1, offsetof(AttributedBar, ExternalInteger) },
            { "ExternalFloat", Datum::DatumTypes::Float, 1, offsetof(AttributedBar, ExternalFloat) },
            { "ExternalString", Datum::DatumTypes::String, 1, offsetof(AttributedBar, ExternalString) },
            { "ExternalVector", Datum::DatumTypes::Vector, 1, offsetof(AttributedBar, ExternalVector) },
            { "ExternalMatrix", Datum::DatumTypes::Matrix, 1, offsetof(AttributedBar, ExternalMatrix) },
            { "ExternalIntegerArray", Datum::DatumTypes::Integer, ArraySize, offsetof(AttributedBar, ExternalIntegerArray) },
            { "ExternalFloatArray", Datum::DatumTypes::Float, ArraySize, offsetof(AttributedBar, ExternalFloatArray) },
            { "ExternalStringArray", Datum::DatumTypes::String, ArraySize, offsetof(AttributedBar, ExternalStringArray) },
            { "ExternalVectorArray", Datum::DatumTypes::Vector, ArraySize, offsetof(AttributedBar, ExternalVectorArray) },
            { "ExternalMatrixArray", Datum::DatumTypes::Matrix, ArraySize, offsetof(AttributedBar, ExternalMatrixArray) },
            { "NestedScope", Datum::DatumTypes::Table, 1, 0 },
            { "NestedScopeArray", Datum::DatumTypes::Table, ArraySize, 0 },
            { "UnknownTest", Datum::DatumTypes::Unknown, 1, 0}
        };
    }
}