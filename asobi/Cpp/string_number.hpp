#pragma once
#define ASOBI_STRING_NUMBER

#include <string>
#include <cctype>
#include <cmath>


namespace asobi {

//StringÇ™Integerå^Ç©
bool is_integer(const std::string&& str) {
	if (str.empty() || str == "")
		return false;
	auto i = str.begin();
	if (*i == '-' && str.length() > 1)
		i++;
	for (; i != str.end(); i++) {
		if (!std::isdigit(*i))
			return false;
	}

	return true;
}
//Stringå^Ç™ïÇìÆè¨êîå^Ç©
bool is_double(const std::string&& str) {
	if (str.empty() || str == "")
		return false;

	auto i = str.begin();
	bool fraction_flag = false;
	if (*i == '-' && str.length() > 1)
		i++;
	for (; i != str.end(); i++) {
		if (!std::isdigit(*i) || fraction_flag && *i == '.')
			return false;
		if (*i == '.')
			fraction_flag = true;
	}

	return true;
}

// êîílå^Ç…ïœä∑Ç∑ÇÈ
template <class T>
T to_number(const std::string&& str) {
	T num = 0;
	bool minus = false;
	bool fraction = false;
	int fraction_digit = 0;
	
	auto i = str.begin();

	if (*i == '-') {
		minus = true;
		i++;
	}
	for (; i != str.end(); i++) {
		if (*i == '.')
			fraction = true;
		else if (fraction) {
			fraction_digit--;
			//num += 
			auto n =
				static_cast<T>(
					std::powl(10, fraction_digit) 
					* static_cast<int>(static_cast<int>(*i) - '0')
				);
			num += n;
		}
		else {
			num *= 10;
			num += static_cast<int>(static_cast<int>(*i) - '0');
		}
	}
	if (minus)
		num *= -1;
	return num;
}

}// namespace asobi