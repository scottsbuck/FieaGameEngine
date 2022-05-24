#pragma once
#include "HashMap.h"
#include <string>
#include <gsl/pointers>
namespace FieaGameEngine
{
	template <typename AbstractProductT>
	class Factory
	{
	public:
		/// <summary>
		/// Finds classname in the static hashmap
		/// </summary>
		/// <param name="className">string of class to find</param>
		/// <returns>a factory pointer pointing to the factory related to that class</returns>
		static Factory* Find(const std::string& className);
		/// <summary>
		/// Creates an object of classname
		/// </summary>
		/// <param name="className">class to create object of</param>
		/// <returns>object created</returns>
		static gsl::owner<AbstractProductT*> Create(const std::string& className);
		
		/// <summary>
		/// Adds a concreteFactory to the factory hashmap
		/// </summary>
		/// <param name="concreteFactory">concrete factory to add</param>
		static void Add(Factory& concreteFactory);
		/// <summary>
		/// Removes a concreteFactory from the factory hashmap
		/// </summary>
		/// <param name="concreteFactory">concrete factory to remove</param>
		static void Remove(Factory& concreteFactory);
		/// <summary>
		/// function to return a const reference to the factories
		/// </summary>
		/// <returns>a const reference to the factories hashmap</returns>
		static const HashMap<std::string, Factory<AbstractProductT>*>& GetFactories();

		/// <summary>
		/// pure virtual function overriden by the ConcreteFactory macro. Creates an object of the concrete products type
		/// </summary>
		/// <returns>a base class pointer to the concrete product</returns>
		virtual gsl::owner<AbstractProductT*> Create() const = 0;
		/// <summary>
		/// pure virtual function overriden by the ConcreteFactory macro. 
		/// </summary>
		/// <returns>returns the class name as a string</returns>
		virtual std::string ClassName() = 0;

	private:
		inline static HashMap<std::string, Factory<AbstractProductT>*> mFactoryMap;
	};
}

#define ConcreteFactory(ConcreteProductType, AbstractProductType)						\
	class Factory##ConcreteProductType : public FieaGameEngine::Factory<AbstractProductType>			\
	{																					\
	public:																				\
		Factory##ConcreteProductType()													\
		{																				\
			Add(*this);																	\
		}																				\
																						\
		~Factory##ConcreteProductType()													\
		{																				\
			Remove(*this);																\
		}																				\
																						\
		gsl::owner<AbstractProductType*> Create() const override									\
		{																				\
			return new ConcreteProductType;												\
		}																				\
																						\
		std::string ClassName() override												\
		{																				\
			return #ConcreteProductType;												\
		}																				\
	};																						

#include "Factory.inl"