#include "pch.h"
#include "AttributedFoo.h"

using namespace FieaGameEngine;

namespace LibraryDesktopUnitTests
{
    RTTI_DEFINITIONS(AttributedFoo)

    AttributedFoo::AttributedFoo() :
        Attributed(AttributedFoo::TypeIdClass())
    {
        
    }

    gsl::owner<AttributedFoo*> AttributedFoo::Clone() const
    {
        return new AttributedFoo(*this);
    }

    bool AttributedFoo::Equals(const FieaGameEngine::RTTI* rhs) const
    {
        const auto rhsFoo = rhs->As<AttributedFoo>();
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

    std::string AttributedFoo::ToString() const
    {
        return "AttributedFoo";
    }

    const Vector<Signature> AttributedFoo::Signatures()
    {
        return Vector<FieaGameEngine::Signature>
        {
            { "ExternalInteger", Datum::DatumTypes::Integer, 1, offsetof(AttributedFoo, ExternalInteger) },
            { "ExternalFloat", Datum::DatumTypes::Float, 1, offsetof(AttributedFoo, ExternalFloat) },
            { "ExternalString", Datum::DatumTypes::String, 1, offsetof(AttributedFoo, ExternalString) },
            { "ExternalVector", Datum::DatumTypes::Vector, 1, offsetof(AttributedFoo, ExternalVector) },
            { "ExternalMatrix", Datum::DatumTypes::Matrix, 1, offsetof(AttributedFoo, ExternalMatrix) },
            { "ExternalIntegerArray", Datum::DatumTypes::Integer, ArraySize, offsetof(AttributedFoo, ExternalIntegerArray) },
            { "ExternalFloatArray", Datum::DatumTypes::Float, ArraySize, offsetof(AttributedFoo, ExternalFloatArray) },
            { "ExternalStringArray", Datum::DatumTypes::String, ArraySize, offsetof(AttributedFoo, ExternalStringArray) },
            { "ExternalVectorArray", Datum::DatumTypes::Vector, ArraySize, offsetof(AttributedFoo, ExternalVectorArray) },
            { "ExternalMatrixArray", Datum::DatumTypes::Matrix, ArraySize, offsetof(AttributedFoo, ExternalMatrixArray) },
            { "NestedScope", Datum::DatumTypes::Table, 1, 0 },
            { "NestedScopeArray", Datum::DatumTypes::Table, ArraySize, 0 }
        };
    }
}