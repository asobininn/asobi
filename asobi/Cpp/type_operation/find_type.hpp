#pragma once
#define ASOBI_FIND_TYPE

#include <type_traits>
#include <tuple>

namespace asobi {

// find_type
namespace detail {
	template <class FindType, class List>
	struct find_type_impl;

	template <class FindType, class Thead, class... Ttail>
	struct find_type_impl<FindType, std::tuple<Thead, Ttail...>> {
		static const bool value =
			std::is_same<FindType, Thead>::value ?
			true :
			find_type_impl<FindType, std::tuple<Ttail...>>::value;
	};

	template <class FindType>
	struct find_type_impl<FindType, std::tuple<>> {
		static const bool value = false;
	};
}
template <class FindType, class... List>
struct find_type {
	static const bool value = detail::find_type_impl<FindType, std::tuple<List...>>::value;
};

} // namespace my
