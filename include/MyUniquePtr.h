#pragma once
#include <utility>

template <typename T>
class MyUniquePtr
{
private:
	T* m_ptr;
public:
	explicit MyUniquePtr(T* ptr = nullptr) {
		m_ptr = ptr;
	}
	~MyUniquePtr() {
		delete m_ptr;
	}

	MyUniquePtr(const MyUniquePtr& other) = delete;
	MyUniquePtr& operator=(const MyUniquePtr& other) = delete;

	MyUniquePtr(MyUniquePtr&& other)noexcept {
		m_ptr = nullptr;
		std::swap(m_ptr, other.m_ptr);
	}
	MyUniquePtr& operator=(MyUniquePtr&& other)noexcept {
		if (this != &other) {
			this->reset(nullptr);
			std::swap(m_ptr, other.m_ptr);
			//reset(other.release());
		}
		return *this;
	}

	T& operator*()const {
		return *m_ptr;
	}
	T* operator->()const {
		return m_ptr;
	}

	T* get()const {
		return m_ptr;
	}
	T* release() {
		T* temp = m_ptr;
		m_ptr = nullptr;
		return temp;
	}
	void reset(T* ptr = nullptr) {
		delete m_ptr;
		m_ptr = ptr;
	}
};