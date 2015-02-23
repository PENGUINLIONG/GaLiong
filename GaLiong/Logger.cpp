#include "Logger.h"

_L_BEGIN
Logger::Logger()
{
	//locale::global(locale(""));
	std::wcout.imbue(std::locale(""));
}
Logger::~Logger()
{
}

Logger &Logger::Log(const wchar_t *content)
{
	return Log(content, WarningLevel::Info);
}
Logger &Logger::Log(const wchar_t *content, WarningLevel level, bool terminate)
{
	if (!logging)
	{
		wchar_t timeBuffer[20];
		time_t now = time(0);
		struct tm ts = *localtime(&now);
		wcsftime(timeBuffer, 20, L"%Y-%m-%d %X", &ts);
		tempString = timeBuffer;

		switch (level)
		{
			case WarningLevel::Info:
				tempString += L" [INFO] ";
				break;
			case WarningLevel::Warn:
				tempString += L" [WARN] ";
				break;
			case WarningLevel::Debug:
				tempString += L" [DEBUG] ";
				break;
			case WarningLevel::Error:
				tempString += L" [ERROR] ";
				break;
			case WarningLevel::Fatal:
				tempString += L" [FATAL] ";
				break;
			case WarningLevel::Trace:
				tempString += L" [TRACE] ";
				break;
			default:
				break;
		}
		logging = true;
	}
	tempString += content;
	if (terminate)
		return EndLog(*this);
	return *this;
}

Logger &Logger::operator<<(const unsigned char &source)
{	
	return Log(to_wstring(source).c_str(), WarningLevel::Info, false);;
}	   
Logger &Logger::operator<<(const unsigned short &source)
{	  
	return Log(to_wstring(source).c_str(), WarningLevel::Info, false);;
}	  
Logger &Logger::operator<<(const unsigned int &source)
{
	return Log(to_wstring(source).c_str(), WarningLevel::Info, false);;
}
Logger &Logger::operator<<(const unsigned long &source)
{
	return Log(to_wstring(source).c_str(), WarningLevel::Info, false);;
}
Logger &Logger::operator<<(const unsigned long long &source)
{
	return Log(to_wstring(source).c_str(), WarningLevel::Info, false);;
}

Logger &Logger::operator<<(const signed char &source)
{
	return Log(to_wstring(source).c_str(), WarningLevel::Info, false);;
}
Logger &Logger::operator<<(const signed short &source)
{
	return Log(to_wstring(source).c_str(), WarningLevel::Info, false);;
}
Logger &Logger::operator<<(const signed int &source)
{
	return Log(to_wstring(source).c_str(), WarningLevel::Info, false);;
}
Logger &Logger::operator<<(const signed long &source)
{
	return Log(to_wstring(source).c_str(), WarningLevel::Info, false);;
}
Logger &Logger::operator<<(const signed long long &source)
{
	return Log(to_wstring(source).c_str(), WarningLevel::Info, false);;
}

Logger &Logger::operator<<(const char &source)
{
	return Log(to_wstring(source).c_str(), WarningLevel::Info, false);;
}

Logger &Logger::operator<<(const wchar_t *&source)
{
	return Log(source, WarningLevel::Info, false);
}
Logger &Logger::operator<<(const wstring &source)
{
	return Log(source.c_str(), WarningLevel::Info, false);
}

Logger &Logger::operator<<(const InformativeBuffer &source)
{
	wstringstream tempSStream;
	tempSStream << L"BufferData:";
	const Buffer &buffer = get<0>(source);
	const BufferLength length = get<1>(source);
	for (unsigned long long i = 0; i < length; i++)
	{
		if (!(i & 0x000000000000000F)) // Display the data of every 16 bytes in a line.
			tempSStream << endl << L"    " <<
			L"0x" << setfill(L'0') << hex << setw(sizeof(void *) << 1) <<
				buffer + i << L" |" << uppercase;
		tempSStream << L' ' << setfill(L'0') << hex << setw(2) << *(buffer + i);
	}

	return Log(tempSStream.str().c_str(), WarningLevel::Info, false);
}
Logger &Logger::operator<<(ControlBase &source)
{
	wstring s;
	s += L"Control :\n    ";
	if (source.Implemented(ControlInterface::IClickable))
		s += L"IClickable ";
	if (source.Implemented(ControlInterface::IRenderable))
		s += L"IRenderable ";
	
	return Log(s.c_str(), WarningLevel::Info, false);
}
Logger &Logger::operator<<(Window &source)
{
	wstringstream tempSStream;
	tempSStream << L"Window (HWND = 0x" << setfill(L'0') << hex << setw(sizeof(void *) << 1) << source.hWindow << L") :" << endl;
	tempSStream << (source.isFullScreen ? L"    Fullscreen mode;" : L"    Window mode;") << endl;
	unsigned long long i = 0;
	tempSStream << L"    With " << source.controls.size() << L" controls :";
	for_each(source.controls.begin(), source.controls.end(), [&i, &tempSStream](ControlBase *&control)
	{
		tempSStream << endl;
		tempSStream << L"        [" << i << L']';
		if (control->Implemented(ControlInterface::IClickable))
			tempSStream << L" IClickable";
		if (control->Implemented(ControlInterface::IRenderable))
			tempSStream << L" IRenderable";
		i++;
	});
	
	return Log(tempSStream.str().c_str(), WarningLevel::Info, false);
}

Logger &Logger::operator<<(Logger &(func)(Logger &))
{
	return func(*this);
}

void Logger::SpecifyOutputFile(wchar_t *path, bool fileOutputOnly)
{
	if (path == L"Console")
	{
		console = true;
		if (!fileOutputOnly)
			file = true;
		else if (stream.is_open())
		{
			file = false;
			stream.close();
		}
		return;
	}
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.out);
	file = true;
	if (fileOutputOnly)
		console = false;
	else
		console = true;
	return;
}

Logger &EndLog(Logger &logger)
{
	if (logger.logging)
	{
		if (logger.console)
			wcout << logger.tempString.c_str() << endl;
		if (logger.file)
			logger.stream << logger.tempString.c_str() << endl;
		logger.logging = false;
		logger.tempString.clear();
	}
	return logger;
}

Logger &EndLine(Logger &logger)
{
	if (logger.console)
		wcout << endl;
	if (logger.file)
		logger.stream << endl;
	return logger;
}
_L_END