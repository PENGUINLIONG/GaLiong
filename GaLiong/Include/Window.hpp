#pragma once
#include "Preprocess.hpp"
#include "Button.hpp"
#include "Character.hpp"
#include "ControlBase.hpp"
#include "Event.hpp"
#include "Timer.hpp"
#include "IClickable.hpp"
#include "IRenderable.hpp"
#include "Logger.hpp"

_L_BEGIN
class _L_ Window : public IClickable, public IRenderable
{
	friend class Logger;
public:
	Window(Size size);
	~Window();
	ControlBase *AppendEntity(ControlBase *ControlBase);
	void Clear();
	bool Create();
	void Flush();
	HDC GetDeviceContext();
	void Remove();
	void TrackMouse(long interval);
private:
	bool isFullScreen = false, _MouseDown = false;
	HGLRC hRenderingContext = NULL;
	HDC hDeviceContext = NULL;
	HINSTANCE hInstance = NULL;
	HWND hWindow = NULL;
	Point pos;
	Size size, border, previous;
	Timer _MouseTracker;
	vector<ControlBase *> controls;

	DWORD style = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME;
	DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;

	void DoResize(Size size, bool outer);
	void Window_MouseButton(void *sender, MouseEventArgs e);
	void Window_MouseHover(void *sender, MouseEventArgs e);
	void Window_Render(void *sender, EventArgs e);
	void Window_Resize(void *sender, ResizeEventArgs e);
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
_L_END
