#pragma once
#include "Datum.h"
#include "Hashmap.h"

namespace FieaGameEngine
{
	struct Signature
	{
		std::string name;
		Datum::DatumTypes datumType;
		size_t size;
		size_t offset;
	};

	class TypeRegistry
	{
	public:

		TypeRegistry(const TypeRegistry&) = delete;
		TypeRegistry& operator=(const TypeRegistry&) = delete;

		static TypeRegistry& GetInstance();
		const Vector<Signature>& GetAttributes(size_t idType);
		void SetSignatures(const std::pair<size_t, Vector<Signature>>& insertPair);

		static void Clear();

	private:
		TypeRegistry() {};
		HashMap <size_t, Vector<Signature>> mHashmap;
	};

#define RegisterType(Class, Parent)																			\
	{																										\
		TypeRegistry& registry = registry.GetInstance();													\
		Vector<Signature> vector(Class::Signatures());														\
		if (Parent::TypeIdClass() != Attributed::TypeIdClass())												\
		{																									\
			Vector<Signature> parentVector = registry.GetAttributes(Parent::TypeIdClass());					\
			for (size_t i = 0; i < parentVector.Size(); i++)												\
			{																								\
				vector.PushBack(parentVector[i]);															\
			}																								\
		}																									\
		registry.SetSignatures(std::make_pair(Class::TypeIdClass(), vector));								\
	}
}