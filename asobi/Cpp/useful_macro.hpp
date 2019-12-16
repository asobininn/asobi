#pragma once
#define ASOBI_USEFUL_MACRO

#define ITER(x) std::begin(x), std::end(x)
#define CITER(x) std::cbegin(x), std::cend(x)
#define RITER(x) std::rbegin(x), std::rend(x)

#define COUTLN(x) std::cout << x << std::endl

#define RANDOM_INIT(rd, mt) std::random_device rd; std::mt19937 mt(rd());
#define RANDOM_DATA(v, mt, size, max, add) std::vector<int> v(size); for (int i = 0; i < size; i++) v[i] = mt() % max + add; std::shuffle(ITER(v), mt);