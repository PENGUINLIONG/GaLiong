#pragma once
#include "Preprocess.h"
#include "Entity.h"
#include "Button.h"
#include "Character.h"
#include "IClickable.h"


using namespace std;

_L_BEGIN
class _L_ Window
{
public:
	Window(Size size);
	bool Create();
	void Resize(Size size);
	inline void Flush()
	{
		glFlush();
		SwapBuffers(hDeviceContext);
	}
	void Remove();
	void Click(Point point);
	void Render();
	inline Entity *AppendEntity(Entity *entity)
	{
		entitys.push_back(entity);
		return entity;
	}
	inline HDC GetDeviceContext()
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
	list<Entity *> entitys;
};
_L_END