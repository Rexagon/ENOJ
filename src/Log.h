#pragma once

#include <string>
#include <fstream>
#include <iostream>

#ifdef ERROR
#undef ERROR
#endif

class Log
{
public:
	enum class Type
	{
		TEXT,
		INFO,
		WARNING,
		ERROR
	};

	static void Create(const std::string& path);
	static void Close();

	struct Out
	{
		Out& operator<<(Type type)
		{
			PrintType(type);
			return *this;
		}

		template<class T>
		Out& operator<<(const T& message)
		{
			m_file << message;
			std::cout << message;
			return *this;
		}
	};

	static Out out;
private:
	static void PrintType(Type type);

	static std::ofstream m_file;
	static size_t m_numErrors;
	static size_t m_numWarnings;
};