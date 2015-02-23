#pragma once
// Standard library
#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
// STL
#include <list>
#include <tuple>
#include <vector>
// Windows
#include <Windows.h>
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

#ifdef _WHITE_BOX_TESTING // White-box testing
#define private public
#define protected public
#endif

_L_BEGIN
// 二次开发的时候只要在EntityType这个命名空间内再开个枚举就行了……
// 看上去就像是EntityType这个enum class（其实是namespace）里面的项
namespace ControlInterface
{
	enum ControlInterface
	{
		IClickable = 0x01,
		IRenderable = 0x02
	};
}

enum class FileReadOption : unsigned char
{
	None = 0x00,
	NoClose = 0x01,
	NoGenerate = 0x02
};

typedef unsigned __int8  Byte1;
typedef unsigned __int16 Byte2;
typedef unsigned __int32 Byte4;
typedef unsigned __int64 Byte8;

typedef unsigned char Byte;
typedef unsigned char *Buffer;
typedef unsigned long long BufferLength;
typedef std::tuple<const Buffer &, const BufferLength> InformativeBuffer;
typedef unsigned __int16 Flag;
typedef unsigned long LongFlag;

typedef struct {
	long Width;
	long Height;
} SizeL;
typedef struct {
	long X;
	long Y;
} PointL;
typedef struct {
	long Left;
	long Top;
	long Right;
	long Bottom;
} RectL;

typedef SizeL Size;
typedef PointL Point;
typedef RectL Rect;

typedef struct {
	double Width;
	double Height;
} SizeD;
typedef struct {
	double X;
	double Y;
} PointD;
typedef struct {
	double Left;
	double Top;
	double Right;
	double Bottom;
} RectD;

typedef struct {
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	unsigned char Alpha;
} Color;

typedef unsigned int TextureID;

template<class T> inline T operator~ (T a) { return (T)~(int)a; }
template<class T> inline T operator| (T a, T b) { return (T)((int)a | (int)b); }
template<class T> inline T operator& (T a, T b) { return (T)((int)a & (int)b); }
template<class T> inline T operator^ (T a, T b) { return (T)((int)a ^ (int)b); }
template<class T> inline T& operator|= (T& a, T b) { return (T&)((int&)a |= (int)b); }
template<class T> inline T& operator&= (T& a, T b) { return (T&)((int&)a &= (int)b); }
template<class T> inline T& operator^= (T& a, T b) { return (T&)((int&)a ^= (int)b); }
_L_END