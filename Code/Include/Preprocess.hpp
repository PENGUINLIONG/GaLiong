#pragma once
// Standard library
#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
// STL
#include <array>
#include <list>
#include <map>
#include <set>
#include <tuple>
#include <vector>

#ifdef __APPLE__ // Apple
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else // Windows and Linux
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif

#ifdef _WIN32 // Windows
	#include <Windows.h>
	#include <windowsx.h>
	#include <WinUser.h>

	// Import libraries
	#pragma comment (lib, "winmm.lib")
	#pragma comment (lib, "opengl32.lib")
	#pragma comment (lib, "glu32.lib")
#endif

#include 

// #pragma warning(disable: 4251)

// #pragma pack(1)

// Not a good habit. Must be deleted after the complement of basic features.
using namespace std;

// Ignore annoying warnings.
// #pragma warning( disable: 4251 )
// #pragma warning( disable: 1083 )

// Ahh...?
#define _L_

#define _L_BEGIN namespace LiongFramework {
#define _L_END }
#define interface class

//#define _WHITE_BOX_TESTING

#ifdef _WHITE_BOX_TESTING // White-box testing
#define private public
#define protected public
#endif

_L_BEGIN
typedef unsigned char  Byte1;
typedef unsigned short Byte2;
typedef unsigned int Byte4;
typedef unsigned long long Byte8;

typedef char Byte;
typedef char* Buffer;
typedef unsigned long long BufferLength;
typedef std::tuple<const Buffer &, const BufferLength> InformativeBuffer;
typedef unsigned short Flag;
typedef unsigned long LongFlag;

typedef void event;

struct SizeL
{
	long Width;
	long Height;
};
struct PointL
{
	long X;
	long Y;
};
struct RectL
{
	long Left;
	long Top;
	long Right;
	long Bottom;
};

typedef SizeL Size;
typedef PointL Point;
typedef RectL Rect;

struct SizeD
{
	double Width;
	double Height;
};
struct PointD
{
	double X;
	double Y;
};
struct RectD
{
	double Left;
	double Top;
	double Right;
	double Bottom;
};
_L_END