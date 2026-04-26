#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstddef>

class MyString
{
public:
	MyString();
	MyString(const char* str);
	~MyString();

	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	MyString(MyString&& other)noexcept;
	MyString& operator=(MyString&& other)noexcept;

	size_t size() const;
	const char* c_str() const;

private:
	char* m_data;
	size_t m_length;
};