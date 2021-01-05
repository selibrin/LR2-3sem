#pragma once
#include <string>

class Exception
{
private:
	std::string m_error;

public:
	Exception(std::string error)
		: m_error(error) {}

	const char* getError() { return m_error.c_str(); }
};