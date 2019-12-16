#pragma once

#define ASOBI_ANY

#include <typeinfo>

namespace asobi {

class any {
	struct holder_base {
		virtual ~holder_base() {}
		virtual holder_base* clone() const = 0;
		virtual const std::type_info& type_id() const = 0;
	};
	template <class T>
	struct holder : public holder_base {
		T m_value;

		holder(const T& value)
			: m_value(value) {}

		virtual holder_base* clone() const override {
			return new holder(m_value);
		}

		virtual const std::type_info& type_id() const override {
			return typeid(T);
		}
	};
	holder_base* m_content;

public:
	any() : m_content(0) {}
	template <class T>
	any(const T& value) : m_content(new holder<T>(value)) { }
	any(const any& other) : m_content(other.m_content ? other.m_content->clone() : 0) {}
	~any() { delete m_content; }

	template <class T>
	any& operator =(const T& value) {
		delete m_content;
		m_content = new holder<T>(value);
		return *this;
	}
	any& operator =(const any& other) {
		delete m_content;
		m_content = other.m_content ? other.m_content->clone() : 0;
		return *this;
	}

	const std::type_info& type_id() const {
		return m_content ? m_content->type_id() : typeid(void);
	}

	template <class T>
	const T& cast() const {
		return dynamic_cast<holder<T>&>(*m_content).m_value;
	}

	template <class T>
	operator T () const
	{
		return dynamic_cast<holder<T>&>(*m_content).m_value;
	}
};

} // namespace my