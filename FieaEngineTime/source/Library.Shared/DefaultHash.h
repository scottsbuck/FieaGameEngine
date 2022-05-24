#pragma once
#include <string>
#include <cstddef>
#include <cstdint>
#include <cstdlib>


namespace FieaGameEngine
{
	/// <summary>
	/// Basic Additivehash for primitive data types
	/// </summary>
	/// <param name="data">takes in the memory address</param>
	/// <param name="size">size of the data</param>
	/// <returns>returns a size_t index to be modded in the hashmap for placement</returns>
	inline size_t AdditiveHash(const std::uint8_t* data, std::size_t size)
	{
		std::size_t hash = 67;

		for (std::size_t i = 0; i < size; i++)
		{
			hash += data[i];
		}

		return hash;
	}

	/// <summary>
	/// defaulthash struct that contains operator()
	/// </summary>
	/// <typeparam name="TKey">takes in a key value and passes it through the additive hash</typeparam>
	template <typename TKey>
	struct DefaultHash
	{
		std::size_t operator()(const TKey& key)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(&key), sizeof(TKey));
		}
	};

	/// <summary>
	/// default hash for a string
	/// </summary>
	template <>
	struct DefaultHash<std::string>
	{
		std::size_t	operator()(const std::string& value)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(value.c_str()), value.size());
		}
	};

	template <>
	struct DefaultHash<const std::string>
	{
		std::size_t	operator()(const std::string& value)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(value.c_str()), value.size());
		}
	};

	/// <summary>
	/// defauly hash for a char*
	/// </summary>
	template <>
	struct DefaultHash<char*>
	{
		std::size_t	operator()(const char* value)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(value), strlen(value));
		}
	};
}