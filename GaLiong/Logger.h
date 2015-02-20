#include "Preprocess.h"
#include "ControlBase.h"
#include "Font.h"
#include "TextureBase.h"
#include "Window.h"

_L_BEGIN
class Logger
{
public:
	Logger();
	~Logger();
	enum class WarningLevel : Flag
	{
		Trace = 0,
		Debug,
		Info,
		Warn,
		Error,
		Fatal
	};
	void Log(wchar_t *content);
	void Log(wchar_t *content, WarningLevel level);
#pragma region Data type adaptation
	// Standard data types (unsigned).
	Logger operator<<(unsigned char source);
	Logger operator<<(unsigned short source);
	Logger operator<<(unsigned int source);
	Logger operator<<(unsigned long source);
	Logger operator<<(unsigned long long source);
	// Standard data types (signed).
	Logger operator<<(signed char source);
	Logger operator<<(signed short source);
	Logger operator<<(signed int source);
	Logger operator<<(signed long source);
	Logger operator<<(signed long long source);
	// Standard data types (indefinite sign).
	Logger operator<<(char source);
	Logger operator<<(short source);
	Logger operator<<(int source);
	Logger operator<<(long source);
	Logger operator<<(long long source);
	// Standard data type (string).
	Logger operator<<(char *source);
	Logger operator<<(wchar_t *source);
	Logger operator<<(string source);
	Logger operator<<(wstring source);
	// Inner data type.
	Logger operator<<(Buffer &source);
	Logger operator<<(ControlBase &source);
	Logger operator<<(Font &source);
	Logger operator<<(TextureBase &source);
	Logger operator<<(Window &source);
#pragma endregion
};
_L_END