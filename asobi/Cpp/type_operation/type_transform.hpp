#pragma once
#define ASOBI_TYPE_TRANSFORM

#include <tuple>

namespace asobi {

// type_transform
template <template <class> class UnaryOperation, class... List>
struct type_transform {
	using type = std::tuple<typename UnaryOperation<List>::type...>;
};

}