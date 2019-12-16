#pragma once

#define ASOBI_CONSTEXPR_ANY

namespace asobi {

struct do_nothing {};

// コンパイル時配列
template <class T, int N, class Init = do_nothing>
struct constexpr_ary {
	T data_[N];

	constexpr constexpr_ary()
		: data_()
	{
		for (int i = 0; i < N; i++)
			data_[i] = Init()(i);
	}
};
template <class T, int N>
struct constexpr_ary<T, N, do_nothing> {
	T data_[N];

	constexpr constexpr_ary()
		: data_() {}
};

} //namespace my