#pragma once
#define ASOBI_MATH_POW

namespace asobi {

template <class T>
constexpr auto ipow(T x, int y) {
	auto value = x;
	for (auto i = 1; i < y; i) {
		value *= x;
	}
	return value;
}

}