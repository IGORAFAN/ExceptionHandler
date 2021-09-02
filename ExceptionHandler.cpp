#include <iostream>
#include <string>
#include <fileapi.h>

enum ErrorType
{
	ErrorType_runtime_error = 1,
	ErrorType_range_error = 2,
	ErrorType_overflow_error = 3,
	ErrorType_underflow_error = 4,
	ErrorType_logic_error = 5,
	ErrorType_domain_error = 6,
	ErrorType_invalid_argument = 7,
	ErrorType_length_error = 8,
	ErrorType_out_of_range = 9
};

class WinException
{
public:
	WinException(ErrorType GetLastError, const std::string &FormatMessage)
		: m_errorCode(GetLastError), m_errorMessage(FormatMessage)
	{
	}
	const ErrorType &WhatErrorCode() const
	{
		return m_errorCode;
	}
	const std::string &WhatMeaning() const
	{
		return m_errorMessage;
	}

private:
	ErrorType m_errorCode;
	std::string m_errorMessage;
};

int CreateNewFile(const LPCWSTR &filename)
{
	if (!filename)
	{
		throw WinException(ErrorType_invalid_argument, "The current filename is empty!");
	}
	CreateFile2(filename, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, CREATE_NEW, NULL);
}

int main()
{
	try
	{
		CreateNewFile("..\\text.txt");
	}
	catch (const WinException &ex)
	{
		std::cout << ex.WhatErrorCode() << " - " << ex.WhatMeaning() << std::endl;
	}

	return 0;
}