#pragma once
#include "Preprocess.hpp"
#include "ControlBase.hpp"
#include "Button.hpp"
#include "Character.hpp"
#include "IClickable.hpp"
#include "IRenderable.hpp"
#include "Logger.hpp"

_L_BEGIN
class _L_ Window
{
	friend class Logger;
public:
	Window(Size size);
	~Window();
	ControlBase *AppendEntity(ControlBase *ControlBase);
	void Clear();
	void Click(Point point);
	bool Create();
	void Flush();
	HDC GetDeviceContext();
	void Remove();
	void Render();
	void Resize(Size size);
private:
	bool isFullScreen = false;
	HGLRC hRenderingContext = NULL;
	HDC hDeviceContext = NULL;
	HINSTANCE hInstance = NULL;
	HWND hWindow = NULL;
	Point pos;
	Size size, border, previous;
	vector<ControlBase *> controls;

	DWORD style = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME;
	DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;

	void Resize(Size size, bool outer);
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
_L_END
