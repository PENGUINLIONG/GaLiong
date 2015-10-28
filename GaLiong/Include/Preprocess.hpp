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

#ifdef _WIN32
	// Windows
	#include <Windows.h>
	#include <windowsx.h>
	#include <WinUser.h>
	// OpenGL
	#include <gl/GL.h>
	#include <gl/GLU.h>

	// Import libraries
	#pragma comment (lib, "winmm.lib")
	#pragma comment (lib, "opengl32.lib")
	#pragma comment (lib, "glu32.lib")
#endif

#ifdef __APPLE__
	// OpenGL
	#include <GLUT/GLUT.h>
#endif

#pragma warning(disable: 4251)

#pragma pack(1)

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
typedef unsigned int TextureIndex;
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

struct Color
{
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	unsigned char Alpha;
};

// 二次开发的时候只要在EntityType这个命名空间内再开个枚举就行了……
// 看上去就像是EntityType这个enum class（其实是namespace）里面的项
struct ControlInterface
{
	const static Flag IClickable  = 0x0001;
	const static Flag IRenderable = 0x0002;
};

struct FileReadOption
{
	const static Flag None       = 0x0000;
	const static Flag NoClose    = 0x0001;
	const static Flag NoGenerate = 0x0002;
};

enum class Alignment
{
	Center,
	Left,
};
_L_END