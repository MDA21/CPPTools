#include <MyString.h>
#include <cstring>
#include <utility>

MyString::MyString() {
	m_length = 0;
	m_data = new char[1];
	m_data[0] = '\0';
}

MyString::MyString(const char* str) {
	m_length = str ? strlen(str) : 0;
	m_data = new char[m_length + 1];
	 if (str) {
		strcpy(m_data, str);
	}
	else {
		m_data[0] = '\0';
	}
}

MyString::~MyString() {
	delete[] m_data;
}

MyString::MyString(const MyString& other) {
	m_length = other.m_length;
	m_data = new char[m_length + 1];
	strcpy(m_data, other.m_data);
}

MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		delete[] m_data;
		m_data = new char[other.m_length + 1];
		strcpy(m_data, other.m_data);
		m_length = other.m_length;
	}
	return *this;
}

MyString::MyString(MyString&& other)noexcept {
	m_data = nullptr;
	m_length = other.m_length;
	std::swap(m_data, other.m_data);
}

MyString& MyString::operator=(MyString&& other)noexcept {
	if(this != &other){
		delete[] m_data;
		m_data = nullptr;
		m_length = other.m_length;
		other.m_length = 0;
		std::swap(m_data, other.m_data);
	}
	return *this;
}

size_t MyString::size() const {
	return m_length;
}

const char* MyString::c_str()const {
	return m_data;
}