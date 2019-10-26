#pragma once
#ifndef exception_h
#define exception_h

#include <exception>

class outOfRange: public std::exception
{
public:
	const char* what() const throw()
	{
		return "Index is out of range";
	}
	
	const int code = 10;
};

class containerIsEmpty: public std::exception
{
public:
	const char* what() const throw()
	{
		return "Can't get data from an empty container";
	}

	const int code = 11;
};

class errorInTest: public std::exception
{
public:
	const char* what() const throw()
	{
		return "Can't run test";
	}

	const int code = 33;
};

#endif
