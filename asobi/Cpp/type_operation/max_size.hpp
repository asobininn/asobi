#pragma once
#define ASOBI_MAX_SIZE

#include "type_of_this_size.hpp"

namespace asobi {

// search_max_size
template <class Thead, class... Ttail>
struct search_max_size {
	static const size_t size =
		sizeof(Thead) > search_max_size<Ttail...>::size ?
		sizeof(Thead) : search_max_size<Ttail...>::size;
};
template <class Thead>
struct search_max_size<Thead> {
	static const size_t size = sizeof(Thead);
};

// max_size
template <class Thead, class... Ttail>
using max_size = typename
	type_of_this_size<search_max_size<Thead, Ttail...>::size, Thead, Ttail...>::type;

} // namespace my