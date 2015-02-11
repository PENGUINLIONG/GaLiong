#pragma once
// Standard library
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
// STL
#include <list>
#include <tuple>
#include <vector>
// Windows
#include <Windows.h>
// OpenGL
#include <gl\GL.h>
#include <gl\GLU.h>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_STROKER_H

// Import libraries
//#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

// Not a good habit. Must be deleted after the complement of basic features.
using namespace std;

// I forgot what this used for.
#pragma warning( disable: 4251 )

// Get ready for export the dll.
#ifdef GALIONG_EXPORTS
#define _L_ __declspec(dllexport)
#else
#define _L_ __declspec(dllimport)
#endif

#define _L_BEGIN namespace LiongStudio { namespace GaLiong {
#define _L_END } }

#define _L_ENUM_BEGIN(name) enum name {
#define _L_ENUM_JOIN(name) }; enum name {
#define _L_ENUM_END };

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
		IRenderable = 1,
		IClickable = 1 << 1
	};
}

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
_L_END