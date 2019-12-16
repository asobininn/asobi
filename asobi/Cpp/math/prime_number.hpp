#pragma once
#define ASOBI_MATH_PRIME_NUMBER

#include <future>
#include <thread>

#include "isqrt.hpp"

namespace asobi {

namespace detail {
	// ���̒l�ɂ��āA�͈͓��𒲂ׂĊ���؂��l�����邩
	template <class Int>
	struct seek_prime_until_length {
		bool operator ()(const Int& v, const Int&& first, const Int& last, int increment)
		{
			for (Int i = first; i <= last; i += increment) {
				if (v % i == 0)
					return false;
			}
			return true;
		}
	};
}
constexpr int SINGLE_LIMIT = 0;	// �V���O���^�X�N�ŏ�������l�̍ő�l
// ���̒l���f�������肷��
template <class Int>
bool is_prime_num(Int v)
{
	auto task_num = std::thread::hardware_concurrency() * 2;

	if (v <= 1) return false;
	if (v == 2) return true;
	if (v % 2 == 0) return false;

	Int limit = isqrt(v) + 1;
	//if (v <= SINGLE_LIMIT) {
	if (false) {
		return detail::seek_prime_until_length<Int>()(v, 3, limit, 2);
	}
	else {
		std::vector<std::future<bool>> d(task_num);
		for (unsigned int i = 0; i < task_num; i++) {
			d[i] = std::async(std::launch::async, detail::seek_prime_until_length<Int>(), v, 3 + (i * 2), limit, task_num);
		}

		unsigned int result = 0;
		for (unsigned int i = 0; i < task_num; i++)
			result += d[i].get();
		if (result < task_num)
			return false;
		return true;
	}
}

}// namespace asobi