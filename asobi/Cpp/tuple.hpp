#pragma once

#define ASOBI_TUPLE

namespace asobi {

template <int N, class ...T>
struct tuple_data;

template <int N>
struct tuple_data<N> {};

template <int N, class Thead, class... Tbody>
struct tuple_data<N, Thead, Tbody...>
	: public tuple_data<N + 1, Tbody...>
{
	Thead value;
};

template <class... T>
struct tuple : public tuple_data<0, T...> {};

template <int N, class Thead, class... Tbody>
Thead& get_tuple_data(tuple_data<N, Thead, Tbody...>& t)
{
	return t.value;
}

template <int N, class... T>
decltype(auto) get(tuple<T...>& t)
{
	return get_tuple_data<N>(t);
}

template <int... N, class... T>
decltype(auto) gets(tuple<T...>& t)
{
	return 0;
}

} // namespace my