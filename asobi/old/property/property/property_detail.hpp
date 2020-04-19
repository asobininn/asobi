#pragma once
#define ASOBI_PROPERTY_DETAIL

#include <type_traits>
#include "../type_operation.hpp"
#include "../helper.hpp"


namespace asobi {

namespace options {
	struct get {};
	struct set {};
}

namespace detail {
	// 非アクセスプロパティ(基底クラス)
	template <class T>
	class none_options_property {
	protected: // member variable
		T* m_pvalue;
	public: // constructor, destructor
		none_options_property() : m_pvalue(nullptr) {};
		none_options_property(none_options_property& other) = delete;
		none_options_property(none_options_property&& other) = delete;
		none_options_property(T& lvalue) : m_pvalue(&lvalue) {}
		virtual ~none_options_property() = default;
	};

	// getオプション付きプロパティ
	template <class T>
	class get_options_property : virtual public none_options_property<T> {
	public: // constructor, destructor
		using none_options_property<T>::none_options_property;
	public: // functions
		inline const T& get() const { return *(this->m_pvalue); }
		inline operator const T& () const { return *(this->m_pvalue); }
	};

	// setオプション付きプロパティ
	template <class T>
	class set_options_property : virtual public none_options_property<T> {
	public: // constructor, destructor
		using none_options_property<T>::none_options_property;
	public: // functions
		inline auto& set(const T& value) { *(this->m_pvalue) = value; return *this; }
		inline auto& set(T&& value) { *(this->m_pvalue) = std::move(value); return *this; }
		inline auto& operator =(const T& value) { *(this->m_pvalue) = value; return *this; }
		inline auto& operator =(T&& value) { *(this->m_pvalue) = std::move(value); return *this; }
		inline auto& operator +=(T&& value) { *(this->m_pvalue) += value; return *this; }
		inline auto& operator +=(const T& value) { *(this->m_pvalue) += value; return *this; }
		inline auto& operator -=(T&& value) { *(this->m_pvalue) -= value; return *this; }
		inline auto& operator -=(const T& value) { *(this->m_pvalue) -= value; return *this; }
		inline auto& operator *=(T&& value) { *(this->m_pvalue) *= value; return *this; }
		inline auto& operator *=(const T& value) { *(this->m_pvalue) *= value; return *this; }
		inline auto& operator /=(T&& value) { *(this->m_pvalue) /= value; return *this; }
		inline auto& operator /=(const T& value) { *(this->m_pvalue) /= value; return *this; }
		inline auto& operator |=(T&& value) { *(this->m_pvalue) |= value; return *this; }
		inline auto& operator |=(const T& value) { *(this->m_pvalue) |= value; return *this; }
		inline auto& operator &=(T&& value) { *(this->m_pvalue) &= value; return *this; }
		inline auto& operator &=(const T& value) { *(this->m_pvalue) &= value; return *this; }
		inline auto& operator ^=(T&& value) { *(this->m_pvalue) ^= value; return *this; }
		inline auto& operator ^=(const T& value) { *(this->m_pvalue) ^= value; return *this; }
	};

	// getがあるか
	template<class T, class... Options>
	struct has_get : public std::conditional<find_type<options::get, Options...>::value, get_options_property<T>, nothing>::type {};

	// setがあるか
	template<class T, class... Options>
	struct has_set : public std::conditional<find_type<options::set, Options...>::value, set_options_property<T>, nothing>::type {};

	// propertyが継承するもの
	template <class T, class... Options>
	struct property_options
		: public has_get<T, Options...>,
		  public has_set<T, Options...>
	{};

} // namespace detail

} // namespace asobi
