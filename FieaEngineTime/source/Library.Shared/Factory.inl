#pragma once
#include "Factory.h"
namespace FieaGameEngine
{
	template<typename AbstractProductT>
	inline Factory<AbstractProductT>* Factory<AbstractProductT>::Find(const std::string& className)
	{
		typename HashMap<std::string, Factory<AbstractProductT>*>::Iterator it = mFactoryMap.Find(className);
		if (it == mFactoryMap.end())
		{
			return nullptr;
		}
		return (*it).second;
	}

	template<typename AbstractProductT>
	inline gsl::owner<AbstractProductT*> Factory<AbstractProductT>::Create(const std::string& className)
	{
		typename HashMap<std::string, Factory<AbstractProductT>*>::Iterator it = mFactoryMap.Find(className);
		if (it == mFactoryMap.end())
		{
			return nullptr;
		}
		return (*it).second->Create();
	}

	template<typename AbstractProductT>
	inline void Factory<AbstractProductT>::Add(Factory& concreteFactory)
	{
		mFactoryMap.Insert(std::make_pair(concreteFactory.ClassName(), &concreteFactory));
	}

	template<typename AbstractProductT>
	inline void Factory<AbstractProductT>::Remove(Factory& concreteFactory)
	{
		mFactoryMap.Remove(concreteFactory.ClassName());
	}
	template<typename AbstractProductT>
	inline const HashMap<std::string, Factory<AbstractProductT>*>& Factory<AbstractProductT>::GetFactories()
	{
		return mFactoryMap;
	}
}