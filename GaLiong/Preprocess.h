#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
// OpenGL
#include <gl\GL.h>
#include <gl\GLU.h>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_STROKER_H

//#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

using namespace std;

#pragma warning( disable: 4251 )

#ifdef GALIONG_EXPORTS
#define _L_ __declspec(dllexport)
#else
#define _L_ __declspec(dllimport)
#endif

typedef int code;

#define _L_BEGIN namespace LiongStudio { namespace GaLiong {
#define _L_END } }

_L_BEGIN
namespace EntityType
{
	enum EntityType
	{
		IRenderable = 0x01,
		IClickable = 0x01 << 1
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