#pragma once
#include<cstddef>
#include<utility>

template <typename T>
class MySharedPtr
{
private:
	T* m_ptr;
	size_t* m_count;

public:
	explicit MySharedPtr(T* ptr = nullptr) {

	}
	~MySharedPtr() {
		delete m_ptr;
	}

};
