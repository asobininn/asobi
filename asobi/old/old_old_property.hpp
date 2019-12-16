#pragma once

#define ASOBI_OLD_PROPERTY

#include <utility>
#include "type_operation.hpp"

#define FREE_ACCESS asobi::option::get, asobi::option::set
#define GET asobi::option::get
#define SET asobi::option::set

namespace asobi {

namespace option {
	struct get {};
	struct set {};
}

template <class T, class... Options>
class property final {
	T m_value;
public:
	constexpr property() = default;
	constexpr property(property&&) = default;

	template <class U>
	constexpr property(U&& value)
		: m_value(std::forward<U>(value)) {}

	constexpr property(const property& other)
		: m_value(other.m_value) {}

	constexpr operator T() const
	{
		static_assert(find_type<option::get, Options...>::value, "this property does not allow get an option");
		return m_value; 
	}

	constexpr T get() const
	{
		static_assert(find_type<option::get, Options...>::value, "this property does not allow get an option");
		return m_value;
	}

	template <class U>
	constexpr property& operator=(U&& value)
	{
		static_assert(asobi::find_type<option::set, Options...>::value, "this property does not allow set an option");
		m_value = std::forward<U>(value);
		return *this;
	}

	constexpr property& operator=(const property& other)
	{
		static_assert(find_type<option::set, Options...>::value, "this property does not allow set an option");
		m_value = other.m_value;
		return *this;
	}

	template <class U>
	constexpr property& set(U&& value)
	{
		static_assert(asobi::find_type<option::set, Options...>::value, "this property does not allow set an option");
		m_value = std::forward<U>(value);
		return *this;
	}

	constexpr property& set(const property& other)
	{
		static_assert(find_type<option::set, Options...>::value, "this property does not allow set an option");
		m_value = other.m_value;
		return *this;
	}
};

} // namespace asobi