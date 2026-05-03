#pragma once
#include<cstddef>
#include<utility>

template <typename T>
class MySharedPtr
{
private:
	T* m_ptr;
	size_t* m_count;

	void release() {
		if (m_count && --(*m_count) == 0) {
			delete m_ptr;
			delete m_count;
		}
	}
public:
	explicit MySharedPtr(T* ptr = nullptr): m_ptr(ptr),m_count(new size_t(1)) {

	}
	~MySharedPtr() {
		release();
	}

	MySharedPtr(const MySharedPtr& other) {
		m_ptr = other.m_ptr;
		m_count = other.m_count;
		(*m_count)++;
	}

	MySharedPtr& operator=(const MySharedPtr& other) {
		if (this == &other) return *this;

		release();

		m_ptr = other.m_ptr;
		m_count = other.m_count;
		(*m_count)++;
	}

	MySharedPtr(MySharedPtr&& other) noexcept {
		m_count = nullptr;
		m_ptr = nullptr;
		std::swap(m_count, other.m_count);
		std::swap(m_ptr, other.m_ptr);
	}

	MySharedPtr& operator=(MySharedPtr&& other) noexcept {
		if (this == &other) return *this;
		release();
		m_count = nullptr;
		m_ptr = nullptr;
		std::swap(m_count, other.m_count);
		std::swap(m_ptr, other.m_ptr);
	}

	size_t use_count() const {
		return *m_count;
	}

	T& operator*() const {
		return *m_ptr;
	}
	T* operator->() const {
		return m_ptr;
	}
};
