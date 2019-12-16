#pragma once
#define ASOBI_MATH_ISQRT

#include <iostream>
#include "isqrt.hpp"

namespace asobi {

constexpr int GAUS_SIZE = 101;
constexpr int SQRT_GAUS = isqrt<int>(GAUS_SIZE);
// ÉKÉEÉXÇÃêÆêîÇï\é¶Ç∑ÇÈ(âº)
void gaussian_integer(char a[][GAUS_SIZE + 1])
{
	int i = 0;
	int j = 0;
	int p = 0;
	int q = 0;
	int x = 0;
	int y = 0;

	std::fill(a[0], a[GAUS_SIZE], 1);
	a[0][0] = a[1][0] = a[0][1] = 0;


	for (i = 1; i <= SQRT_GAUS; i++) {
		for (j = 0; j <= i; j++) {
			if (a[i][j]) {
				p = i; q = j;
				do {
					x = p; y = q;
					do {
						a[x][y] = a[y][x] = 0;
					} while ((x -= j) >= 0 && (y += i) <= GAUS_SIZE);
					p += i; q += j;
				} while (p <= GAUS_SIZE);
				a[i][j] = a[j][i] = 1;
			}
		}
	}
	for (i = -GAUS_SIZE; i <= GAUS_SIZE; i++) {
		for (j = -GAUS_SIZE; j <= GAUS_SIZE; j++) {
			if (a[abs(i)][abs(j)] && i * i + j * j <= GAUS_SIZE * GAUS_SIZE)
				std::cout << "*";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}

}// namespace asobi