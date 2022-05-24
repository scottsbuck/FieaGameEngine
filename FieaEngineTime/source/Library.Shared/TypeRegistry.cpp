#include "pch.h"
#include "TypeRegistry.h"

namespace FieaGameEngine
{
	TypeRegistry& TypeRegistry::GetInstance()
	{
		static TypeRegistry instance;
		return instance;
	}

	const Vector<Signature>& TypeRegistry::GetAttributes(size_t idType)
	{
		return (*mHashmap.Find(idType)).second;
	}

	void TypeRegistry::Clear()
	{
		GetInstance().mHashmap.Clear();
	}

	void TypeRegistry::SetSignatures(const std::pair<size_t, Vector<Signature>>& insertPair)
	{
		mHashmap.Insert(insertPair);
	}
}