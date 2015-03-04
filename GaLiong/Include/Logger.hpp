#pragma once
#include "Preprocess.hpp"

_L_BEGIN
class _L_ Logger
{
	friend _L_ Logger &EndLog(Logger &logger);
	friend _L_ Logger &EndLine(Logger &logger);
public:
	Logger();
	~Logger();
	enum class WarningLevel : Flag
	{
		Trace = 0x01,
		Debug = 0x02,
		Info  = 0x04,
		Warn  = 0x08,
		Error = 0x10,
		Fatal = 0x20,
	};
	Logger &Log(const wchar_t *content);
	Logger &Log(const wchar_t *content, WarningLevel level, bool terminate = true);

#pragma region Data type adaptation
	// Standard data types (unsigned).
	inline Logger &operator<<(const unsigned char      &source);
	inline Logger &operator<<(const unsigned short     &source);
	inline Logger &operator<<(const unsigned int       &source);
	inline Logger &operator<<(const unsigned long      &source);
	inline Logger &operator<<(const unsigned long long &source);
	// Standard data types (signed).
	inline Logger &operator<<(const signed char        &source);
	inline Logger &operator<<(const signed short       &source);
	inline Logger &operator<<(const signed int         &source);
	inline Logger &operator<<(const signed long        &source);
	inline Logger &operator<<(const signed long long   &source);
	// Standard data types (indefinite sign).
	inline Logger &operator<<(const char               &source);
	// Standard data type (string).
	inline Logger &operator<<(const wchar_t *          &source);
	inline Logger &operator<<(const wstring            &source);
	// Inner data type.
		   Logger &operator<<(const InformativeBuffer  &source);
#pragma endregion
	Logger &operator<<(Logger &(func)(Logger &));

	void SpecifyOutputFile(wchar_t *path, bool fileOutputOnly = false);
private:
	bool file = false;
	bool console = true;
	bool logging = false;
	wstring tempString;
	wofstream stream;
	mutex isProcessing;
};

_L_ Logger &EndLog(Logger &logger);
_L_ Logger &EndLine(Logger &logger);

static Logger Log;
_L_END