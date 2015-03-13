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
// Windows
#include <Windows.h>
#include <windowsx.h>
#include <WinUser.h>
#ifdef _INSIDER_COMPILATION
// OpenGL
#include <gl\GL.h>
#include <gl\GLU.h>
// FreeType
#include "freetype\ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_STROKER_H
// LibPNG
#include "libpng\png.h"
// ZLib
#include "zlib\zlib.h"
#include "zlib\zconf.h"

// Import libraries
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#endif

#pragma warning(disable: 4251)

#pragma pack(1)

// Not a good habit. Must be deleted after the complement of basic features.
using namespace std;

// Ignore annoying warnings.
//#pragma warning( disable: 4251 )
//#pragma warning( disable: 1083 )

// Get ready for export the dll.
#ifdef GALIONG_EXPORTS
#define _L_ __declspec(dllexport)
#else
#define _L_ __declspec(dllimport)
#endif

#define _L_BEGIN namespace LiongStudio { namespace GaLiong {
#define _L_END } }

//#define _WHITE_BOX_TESTING

#ifdef _WHITE_BOX_TESTING // White-box testing
#define private public
#define protected public
#endif

_L_BEGIN
typedef unsigned __int8  Byte1;
typedef unsigned __int16 Byte2;
typedef unsigned __int32 Byte4;
typedef unsigned __int64 Byte8;

typedef unsigned char Byte;
typedef unsigned char *Buffer;
typedef unsigned long long BufferLength;
typedef std::tuple<const Buffer &, const BufferLength> InformativeBuffer;
typedef unsigned __int16 Flag;
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