#pragma once
#include <map>
#include "Preprocess.h"
#include "IClickable.h"
#include "Entity.h"
#include "Character.h"
#include "Button.h"

using namespace std;

_L_BEGIN
class _L_ Window
{
public:
	Window(Size size);
	bool Create();
	void Resize(Size size);
	void Flush()
	{
		SwapBuffers(hDeviceContext);
	}
	void Remove();
	void Click(Point point);
	void Render();
	unsigned int AppendEntity(Entity *Entity);
	Entity *&GetEntity(unsigned int id)
	{
		return entitys[id];
	}
	HDC GetDeviceContext()
	{
		return hDeviceContext;
	}
	~Window();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	HGLRC hRenderingContext = NULL;
	HDC hDeviceContext = NULL;
	HINSTANCE hInstance = NULL;
	HWND hWindow;
	UINT uTimer;

	Size size;
	unsigned int entityID = 0;
	map<unsigned int, Entity *> entitys;
};
_L_END
