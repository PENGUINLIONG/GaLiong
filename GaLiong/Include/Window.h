#pragma once
#include "Preprocess.h"
#include <WinUser.h>
#include "Control.h"
#include "Button.h"
#include "Character.h"
#include "IClickable.h"
#include "IRenderable.h"

_L_BEGIN
class _L_ Window
{
public:
	Window(Size size);
	bool Create();
	void Resize(Size size)
	{
		Resize(size, true);
	}
	void Resize(Size size, bool reposition);
	void Flush()
	{
		glFlush();
		SwapBuffers(hDeviceContext);
	}
	void Remove();
	void Click(Point point);
	void Render();
	Control *AppendEntity(Control *control)
	{
		control->SetWindowSize(&this->size);
		controls.push_back(control);
		return control;
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

	Point pos;
	Size size;
	list<Control *> controls;
};
_L_END
