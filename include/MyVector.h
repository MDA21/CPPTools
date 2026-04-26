#pragma once
#include <cstddef>
#include<stdexcept>
#include<utility>

template <typename T>
class MyVector
{
private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;

	void reserve(size_t new_capacity) {
		if (new_capacity <= m_capacity) return;
		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < m_size; ++i) {
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = new_capacity;
	}

public:
	MyVector():m_data(nullptr),m_size(0),m_capacity(0) {
	}

	~MyVector() {
		delete[] m_data;
	}

	MyVector(const MyVector& other):m_data(nullptr), m_size(0), m_capacity(0) {
		this->reserve(other.m_capacity);
		m_size = other.m_size;
		for (size_t i = 0; i < m_size; ++i) {
			m_data[i] = other.m_data[i];
		}
	}
	MyVector& operator=(const MyVector& other) {
		if (this != &other) {
			m_data = new T[other.m_capacity];
			for (size_t i = 0; i < other.m_size; ++i) {
				m_data[i] = other.m_data[i];
			}
			delete[] m_data;
			m_capacity = other.m_capacity;
			m_size = other.m_size;
		}
		return *this;
	}

	MyVector(MyVector&& other)noexcept {
		m_data = nullptr;
		std::swap(m_data, other.m_data);
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	MyVector& operator=(MyVector&& other)noexcept {
		if (this != &other) {
			delete[] m_data;
			m_data = nullptr;
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			std::swap(m_data, other.m_data);
			other.m_size = 0;
			other.m_capacity = 0;
		}
		return *this;
	}

	void push_back(const T& value) {
		if (m_size == m_capacity) {
			size_t new_cap = (m_capacity == 0) ? 1 : m_capacity * 2;
			reserve(new_cap);
		}
		m_data[m_size] = value;
		m_size++;
	}
	void pop_back() {
		if(m_size>0) m_size--;
	}

	T& operator[](size_t index) {
		return m_data[index];
	}
	const T& operator[](size_t index)const {
		return m_data[index];
	}

	size_t size()const {
		return m_size;
	}
	size_t capacity()const {
		return m_capacity;
	}
};
