#pragma once
#define ASOBI_CALC_HPP

#include <iostream>

#include <string>
#include <map>
#include <vector>
#include <stack>
#include <utility>
#include <cmath>
#include <memory>
#include "useful_macro.hpp"

namespace asobi {

template <class T>
class calc {
private:	// constant
	constexpr static int NUMBER_TYPE = 1;
	constexpr static int OPERATOR_TYPE = 2;
	constexpr static int BBRACES_TYPE = 3;
	constexpr static int EBRACES_TYPE = 4;
	constexpr static int COMMA_TYPE = 5;
	constexpr static int FUNCTION_TYPE = 6;
	constexpr static int CONSTANT_FUNCTION_TYPE = 7;
	constexpr static int OTHER_TYPE = 0;

	constexpr static int FUNCTION_PRIORITY = 100000;
	const std::map<std::string, int> PRIORITY = {
		{"+", 2},
		{"-", 2},
		{"*", 3},
		{"/", 3},
		{"%", 3},
		{"^", 4},

		{"(", 30},
		{")", -30},
		{"{", 20},
		{"}", -20},
		{"[", 10},
		{"]", -10},

		{",", 1},
		{"pow", FUNCTION_PRIORITY}
	};
	
	// 仮
	const std::map<std::string, int> ARGS_NUMBER = {
		{"pow", 2}
		//{"", }
	};
private: // variable
	T m_answer;
	std::vector<std::string> m_formula;
	std::vector<std::string> m_reverse_polish_terms;
public:	// constructor
	constexpr calc() : m_answer(0) {}
	constexpr calc(const std::vector<std::string>& formula);
	constexpr calc(const std::string& formula);
//private: // private_method
	constexpr int check_type(const std::string& word);
	inline constexpr bool parse_formla(const std::string& formla);
	inline constexpr int count_braces_num_in_formla();
	inline constexpr void make_reverse_polish();
	inline constexpr void calc_reverse_polish();
public:
	void debug() {
		for (auto i : m_formula) {
			std::cout << i;
		}
		std::cout << std::endl;
		make_reverse_polish();
		for (auto i : m_reverse_polish_terms) {
			std::cout << i << " ";
		}
		std::cout << std::endl;

		calc_reverse_polish();
		std::cout << "= " << m_answer << std::endl;
	}
};

// constructor===================================
template <class T>
constexpr calc<T>::calc(const std::vector<std::string>& formula)
	: m_answer(0)
{
	for (auto i : formula) {
		m_formula.push_back(i);
	}
}

template <class T>
constexpr calc<T>::calc(const std::string& formula)
	: m_answer(0)
{

}
// ==============================================

// private_method================================
//wordのタイプ
template <class T>
constexpr int calc<T>::check_type(const std::string& word) {
	if (asobi::is_double(std::move(word)))
		return NUMBER_TYPE;
	else if (PRIORITY.find(word) == PRIORITY.end())
		return OTHER_TYPE;
	else if (PRIORITY.at("+") <= PRIORITY.at(word)
		&& PRIORITY.at(word) <= PRIORITY.at("^"))
		return OPERATOR_TYPE;
	else if (PRIORITY.at("{") <= PRIORITY.at(word)
		&& PRIORITY.at(word) <= PRIORITY.at("("))
		return BBRACES_TYPE;
	else if (PRIORITY.at(")") <= PRIORITY.at(word)
		&& PRIORITY.at(word) <= PRIORITY.at("}"))
		return EBRACES_TYPE;
	else if (PRIORITY.at(word) == PRIORITY.at(","))
		return COMMA_TYPE;
	else if (!ARGS_NUMBER.at(word))
		return CONSTANT_FUNCTION_TYPE;
	else if (PRIORITY.at(word) == FUNCTION_PRIORITY)
		return FUNCTION_TYPE;

	return OTHER_TYPE;
}

// 式を解析し、m_formlaを構築する
template <class T>
constexpr bool calc<T>::parse_formla(const std::string& formla) {

	return true;
}

// カッコの数をカウント
template <class T>
constexpr int calc<T>::count_braces_num_in_formla() {
	int count = 0;
	for (auto i : m_formula) {
		switch (check_type(i)) {
			case BBRACES_TYPE:
			case EBRACES_TYPE:
				count++;
				break;
			default:
				break;
		}
	}
	return count;
}

// 数式を逆ポーランドに変換
template <class T>
constexpr void calc<T>::make_reverse_polish() {
	int add_priority = 0;
	if (!m_reverse_polish_terms.empty())
		m_reverse_polish_terms.clear();
	m_reverse_polish_terms.resize(m_formula.size() - count_braces_num_in_formla());
	int elem = 0;
	std::stack<std::pair<std::string, int>> ops; // スタックする演算子
	int braces_count = 0;					// 関数の終わりを確認するためのもの
	std::stack<std::pair<std::string, int>> func_begin;	// 関数の終わりに優先度を調整する用
	bool func_flag = false;
	
	for (auto term : m_formula) {
		//COUTLN(term);
		switch (check_type(term)) {
			case NUMBER_TYPE:
				// 数字はそのまま付け足す
				m_reverse_polish_terms[elem++] = term;
				break;
			case BBRACES_TYPE:
				add_priority += PRIORITY.at(term);
				braces_count++;
				break;
			case EBRACES_TYPE:
				add_priority += PRIORITY.at(term);
				braces_count--;
				// 関数の終わりだったら
				if (func_begin.size() && braces_count == func_begin.top().second) {
					add_priority -= PRIORITY.at(func_begin.top().first);
					func_begin.pop();
				}
				break;
			case FUNCTION_TYPE:
				add_priority += PRIORITY.at(term);
				func_begin.push(std::make_pair(term, braces_count));
				func_flag = true;
			case COMMA_TYPE:
			case OPERATOR_TYPE: 
			{
				// 関数と演算子はスタックに入れる
				int now = ((func_flag ? 0 : PRIORITY.at(term)) + add_priority);

				//COUTLN(term << now);
				// 現在の演算子の優先度が、前の演算子の優先度より低い間、前の優先度をpopする
				while (ops.size() && now < ops.top().second) {
					m_reverse_polish_terms[elem++] = ops.top().first;
					ops.pop();
				}
				ops.push(std::make_pair(term, now));
				break;

			}
			default:
				break;
		}
	}
	// 残った演算子を末尾に付け足す
	while (ops.size()) {
		m_reverse_polish_terms[elem++] = ops.top().first;
		ops.pop();
	}
}

// 逆ポーランド記法で計算する
template <class T>
constexpr void calc<T>::calc_reverse_polish() {
	m_answer = 0;

	if (!m_reverse_polish_terms.size())
		return;
	if (m_reverse_polish_terms.size() == 1) {
		m_answer = static_cast<T>(std::stold(m_reverse_polish_terms[0]));
		return;
	}

	std::stack<std::unique_ptr<T>> nums; // 数値をスタック

	for (auto i : m_reverse_polish_terms) {
		//COUTLN("i:" << i);
		switch (check_type(i)) {
			case NUMBER_TYPE: {
				T num = asobi::to_number<T>(std::move(i));
				nums.push(std::make_unique<T>(std::move(num)));	
				break;
			}
			case OPERATOR_TYPE: {
				T b = *nums.top();
				nums.pop();
				T a = *nums.top();
				nums.pop();
				//COUTLN(a << i << b);
				T num = 0;
				if (i == "+")
					num = a + b;
				else if (i == "-")
					num = a - b;
				else if (i == "*")
					num = a * b;
				else if (i == "/")
					num = a / b;
				else if (i == "%")
					num = a % b;
				else if (i == "^")
					num = static_cast<T>(std::powl(a, b));
				nums.push(std::make_unique<T>(std::move(num)));	
				break;
			}
			case COMMA_TYPE:
				nums.push(nullptr);
				break;
			case FUNCTION_TYPE: {
				T num;
				std::vector<T> args;
				while (!nums.empty() && !nums.top()) {
					nums.pop();
					args.emplace_back(std::move(*nums.top()));
					nums.pop();
				}
				args.emplace_back(std::move(*nums.top()));
				nums.pop();

				if (i == "pow") {
					num = static_cast<T>(std::powl(args[1], args[0]));
				}
				/*else if (i == "prime_num") {
				/COUTLN
					nums.push(static_cast<T>(asobi::is_prime_num(args[0]) );
				}*/
				//else if (i == "pi")
				nums.push(std::make_unique<T>(std::move(num)));
				break;
			}
			case CONSTANT_FUNCTION_TYPE: {
				T num = *nums.top();
				nums.pop();
				if (i == "pi") {
					//nums.push()
				}
				nums.push(std::make_unique<T>(std::move(num)));
				break;
			}
			default:
				return;
		}
	}
	m_answer = *nums.top();
}

// ==============================================

// public_method=================================

// ==============================================

}// namespace asobi
