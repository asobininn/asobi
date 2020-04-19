﻿#pragma once
#define ASOBI_PROPERTY_DETAIL

#include <type_traits>
#include "../helper.hpp"

namespace asobi {

// accessor
namespace ac {
	struct get {};
	struct set {};
}

namespace detail {

// 非アクセスプロパティ（基底クラス）
template <class T>
class none_access_property {
protected:
	T* _object;
public:
	none_access_property() : _object(nullptr) {}
	none_access_property(T& object) : _object(&object) {}
	none_access_property(T&& object) : _object(&object) {}
	virtual ~none_access_property() = default;
};

// get accessorプロパティ
template <class T>
class get_access_property : virtual public none_access_property<T> {
public:
	using none_access_property<T>::none_access_property;
public:
	inline const T& get() const { return *this->_object; }
	inline operator const T& () const { return *this->_object; }
};

// set accessorプロパティ
template <class T>
class set_access_property : virtual public none_access_property<T> {
public:
	using none_access_property<T>::none_access_property;
public:
	inline auto& set(const T& object) {*this->_object = object; return *this;}
	inline auto& set(T&& object) {*this->_object = std::move(object); return *this;}
	inline auto& operator =(const T& object) {*this->_object = object; return *this;}
	inline auto& operator =(T&& object) {*this->_object = std::move(object); return *this;}
};

// accessor型ならそれに対応したものを、そうでないならnothing型を返す
template <class T, class Accessor>
struct get_accessor {
	using type = typename std::conditional<std::is_same<Accessor, ac::get>::value, get_access_property<T>,
		typename std::conditional<std::is_same<Accessor, ac::set>::value, set_access_property<T>, nothing>::type>::type;
};

template <class T, class Accessor>
struct wrap_get_accessor : public get_accessor<T, Accessor>::type {};

template <class T, class Accessor>
struct wrap_get_accessor2 : public get_accessor<T, Accessor>::type {};

template <class T, class First = nothing, class Second = nothing>
class property_options :
	public wrap_get_accessor<T, First>,
	public wrap_get_accessor2<T, Second>
{};

}// namespace detail
} // namespace asobi
