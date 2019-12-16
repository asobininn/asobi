#pragma once
#define ASOBI_MATH_ISQRT

namespace asobi {

// •½•û”‚Ì®”ˆÊ•”•ª
template <class Int>
constexpr Int isqrt(Int v)
{
	Int s = 0;
	Int t = 0;

	if (v == 0) return 0;
	s = 1; t = v;
	while (s < t) {
		s <<= 1; t >>= 1;
	}
	do {
		t = s;
		s = (v / s + s) >> 1;
	} while (s < t);
	return t;
}

}// namespace asobi
