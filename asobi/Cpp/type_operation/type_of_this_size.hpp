#pragma once
#define ASOBI_TYPE_OF_THIS_SIZE

#include <type_traits>

namespace asobi {

// type_of_this_size
template <size_t Size, class Thead, class... Ttail>
struct type_of_this_size {
	using type = typename std::conditional < sizeof(Thead) == Size,
		Thead,
		typename type_of_this_size<Size, Ttail...>::type>
		::type;
};
template <size_t Size, class Thead>
struct type_of_this_size<Size, Thead> {
	using type = typename std::conditional < sizeof(Thead) == Size,
		Thead,
		void>
		::type;
};

}