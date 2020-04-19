#pragma once
#define ASOBI_PROPERTY

#include "property/property_detail.hpp"

namespace asobi {

/*
property
 getter, setterを自動生成する
 First, Secondにアクセサを指定する（省略可）
 アクセサ
  asobi::ac::get・・・オブジェクトへの読込みを許可
  asobi::ac::set・・・オブジェクトへの書込みを許可
*/
template <class T, class First = nothing, class Second = nothing>
class property
	: virtual public detail::none_access_property<T>
	, public detail::property_options<T, First, Second> {
	using detail::none_access_property<T>::none_access_property;
};

} // namespace asobi
