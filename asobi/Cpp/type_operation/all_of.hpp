#pragma once
#define ASOBI_ALL_OF

#include <tuple>

namespace asobi {
namespace detail {
	template <template <class> class Pred, class List>
	struct all_of_impl;

	template <template <class> class Pred,
		class Head, class... Tail>
		struct all_of_impl<Pred, std::tuple<Head, Tail...>> {
		static const bool value =
			Pred<Head>::value ?
			all_of_impl<Pred, std::tuple<Tail...>>::value :
			false;
	};

	template <template <class> class Pred>
	struct all_of_impl<Pred, std::tuple<>> {
		static const bool value = true;
	};
} // namespace detail
// all_of
template <template <class> class Pred, class... List>
struct all_of {
	static const bool value = detail::all_of_impl<Pred, std::tuple<List...>>::value;
};

} //namespace my