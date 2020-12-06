#include "String.h"

String::String(size_t size) :str(std::make_shared<std::string>(size, ' ')) {
	//str = std::make_shared<std::string>(size, ' ');
	std::cout << "constructor of empty string size " << size << "\n";
}

String::String(const char* s) :str(std::make_shared<std::string>(s)) {
	//str.reset(new std::string(s));
	std::cout << "constructor from c-string of '" << *str << "'\n";
}

String::String(const String& s) :str(s.str){
	//str = s.str; //shared pointer
	std::cout << "shared ptr copy constructor of '" << *str << "'\n";
}

String String::operator=(const String& s) {
	if (this != &s)
		str = s.str; //just increasing reference count
	std::cout << "assigment operator of '" << *str << "'\n";
	return *this;
}

char& String::operator[](int i) {
	if (!str.unique()) {
		std::cout << "[] copy\n";
		str = std::make_shared<std::string>(*str);
	}
	return (*str)[i];
}

char String::operator[](int i) const {
	return (*str)[i];
}

String operator+(String a, String b) {
	if (!(*a.str).empty() && !(*b.str).empty()) {
		//std::string s = (*a.str) + (*b.str);
		return String(((*a.str) + (*b.str)).c_str());
	}
	if (!(*a.str).empty()) return a;
	return b;
}

std::ostream& operator<<(std::ostream& out, String s) {
	out << *s.str;
	return out;
}
