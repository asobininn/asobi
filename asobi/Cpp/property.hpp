#pragma once
#define ASOBI_PROPERTY

#include "property/property_detail.hpp"

#define GET_OP asobi::options::get
#define SET_OP asobi::options::set
#define FULL_OP asobi::options::get, asobi::options::set

namespace asobi {

// property
template <class T, class... Options>
class property final : virtual public detail::none_options_property<T>, public detail::property_options<T, Options...> {
public:
	using detail::none_options_property<T>::none_options_property;
};

} // namespace asobi
