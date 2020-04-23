#pragma once
#define ASOBI_ANY_OF

#include <tuple>

namespace asobi {
namespace detail {
	template <template <class> class Pred, class List>
	struct any_of_impl;

	template <template <class> class Pred,
	class Head, class... Tail>
	struct any_of_impl<Pred, std::tuple<Head, Tail...>> {
		static const bool value =
			Pred<Head>::value ?
			true :
			any_of_impl<Pred, std::tuple<Tail...>>::value;
	};

	template <template <class> class Pred>
	struct any_of_impl<Pred, std::tuple<>> {
		static const bool value = false;
	};
} // namespace detail
// any_of
template <template <class> class Pred, class... List>
struct any_of {
	static const bool value = detail::any_of_impl<Pred, std::tuple<List...>>::value;
};

} //namespace my