#include "Log.h"

#define ENOJ_VERSION "1.0.3"

std::ofstream Log::m_file;
size_t Log::m_numErrors = 0;
size_t Log::m_numWarnings = 0;
Log::Out Log::out;

void Log::Create(const std::string & path)
{
	m_file.open(path);

	if (m_file.is_open()) {
		m_file << "ENOJ version: " << ENOJ_VERSION << "\n";
		m_file << "Log file created" << "\n\n";
	}
}

void Log::Close()
{
	if (m_file.is_open()) {
		m_file << "\n\n";

		m_file << "[CLOSED]\n";
		m_file << m_numWarnings << " warnings\n";
		m_file << m_numErrors << " errors";

		m_file.close();
	}
}

void Log::PrintType(Type type)
{
	switch (type) {
	case Type::ERROR:
		m_file << "[ERROR]: ";
		std::cout << "[ERROR]: ";
		++m_numErrors;
		break;

	case Type::WARNING:
		m_file << "[WARNING]: ";
		std::cout << "[WARNING]: ";
		++m_numWarnings;
		break;
	case Type::INFO:
		m_file << "[INFO]: ";
		std::cout << "[INFO]: ";
		break;
	}
}
