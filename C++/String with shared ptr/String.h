#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>


class String {
	std::shared_ptr<std::string> str;
public:
	String(size_t size = 0); // creates an empty string
	String(const char* str); // copy C-string
	String(const String&); // no copy
	String operator=(const String&); // no copy
	 // makes a copy of a string if it has more than one reference.
	char& operator[](int i);
	// no copy
	char operator[](int i) const;
	// concatenation creates a new string only if both strings are non empty
	friend String operator+(String a, String b);
	// no copy*/
	friend std::ostream& operator<< (std::ostream& out, String s);
};
