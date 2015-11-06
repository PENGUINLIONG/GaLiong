//
//  Window.cpp
//  GaLiong
//
//  Created by Liong on ??/??/??.
//

#include "Window.hpp"

_L_BEGIN
Window::Window(Size size) : size(size), previous(size), pos({ 200, 100 })
{
	Rect w = { 0, 0, size.Width, size.Height };
	AdjustWindowRectEx((RECT *)&w, style, false, exStyle);
	border = { (w.Right - w.Left - size.Width), (w.Bottom - w.Top - size.Height) };
	_MouseTracker = Timer(this);
	
	// Binding events.
	_MouseTracker.Elapsed += [&](void *sender, ElapsedEventArgs e) {
		Point point;
		GetCursorPos((LPPOINT)&point);
		MouseHover(this, new MouseEventArgs(point, MouseButtons::None, _MouseDown));
	};
	MouseButton += Window_MouseButton;
	MouseHover += Window_MouseHover;
	Render += Window_Render;
	Resize += Window_Resize;
}

Window::~Window()
{
	for(auto &entity : controls)
	{
		if (!entity)
			return;
		delete entity;
		entity = nullptr;
	}
}

ControlBase *Window::AppendEntity(ControlBase *ControlBase)
{
	ControlBase->SetWindowSize(&this->size);
	controls.push_back(ControlBase);
	return ControlBase;
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Window::Create()
{
	int pixelFormat;
	WNDCLASS windowClass;
	Rect windowRect = { 0, 0, size.Width, size.Height };

	hInstance = GetModuleHandle(L"OpenGLiong");
	windowClass.style = CS_HREDRAW | CS_OWNDC | CS_VREDRAW | CS_DBLCLKS; // ########## It will be alright when this conponent is set to NULL. This should be looked up later maybe.
	windowClass.lpfnWndProc = (WNDPROC)WindowProc;
	windowClass.cbClsExtra = NULL; // No extra
	windowClass.cbWndExtra = NULL; // window data.
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Default icon.
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Default cursor.
	windowClass.hbrBackground = NULL; // No backGround image in need in an opengl application.
	windowClass.lpszMenuName = NULL; // No menu.
	windowClass.lpszClassName = L"OpenGLiong";

	if (!RegisterClass(&windowClass))
	{
		MessageBox(NULL, L"窗体注册大失败！", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}

	if (!(hWindow = CreateWindowEx(exStyle, L"OpenGLiong", L"OpenGLiong", style, 200, 100, windowRect.Right - windowRect.Left + border.Width, windowRect.Bottom - windowRect.Top + border.Height, NULL, NULL, hInstance, NULL)))
	{
		Remove();
		MessageBox(NULL, L"无法创建窗体", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor = { sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };

	if (!(hDeviceContext = GetDC(hWindow)))
	{
		Remove();
		MessageBox(NULL, L"无法获取设备上下文", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}
	if (!(pixelFormat = ChoosePixelFormat(hDeviceContext, &pixelFormatDescriptor)))
	{
		Remove();
		MessageBox(NULL, L"无法获取像素格式", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}
	if (!SetPixelFormat(hDeviceContext, pixelFormat, &pixelFormatDescriptor))
	{
		Remove();
		MessageBox(NULL, L"无法设置像素格式", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}
	if (!(hRenderingContext = wglCreateContext(hDeviceContext)))
	{
		Remove();
		MessageBox(NULL, L"无法创建渲染上下文", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}
	if (!wglMakeCurrent(hDeviceContext, hRenderingContext))
	{
		Remove();
		MessageBox(NULL, L"无法绑定渲染上下文", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}

	SetWindowLongPtr(hWindow, GWLP_USERDATA, (LONG_PTR)this);
	ShowWindow(hWindow, SW_SHOW);
	SetForegroundWindow(hWindow);
	SetFocus(hWindow);
	DoResize(size, false);

	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthFunc(GL_NEVER); // No 3D models will be used.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

void Window::DoResize(Size size, bool outer)
{
	if (outer)
	{
		if (isFullScreen)
		{
			DEVMODE dm;
			dm.dmSize = sizeof(DEVMODE);
			dm.dmPelsWidth = size.Width;
			dm.dmPelsHeight = size.Height;
			dm.dmBitsPerPel = 8;
			dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

			ChangeDisplaySettings(&dm, NULL);
			SetWindowLongPtr(hWindow, GWL_STYLE, /*WS_POPUP | */WS_SYSMENU);
			SetWindowLongPtr(hWindow, GWL_EXSTYLE, WS_EX_APPWINDOW);
			// The SWP_SHOWWINDOW CANNOT be removed or it will be a white-blank and when you try clicking it,
			// the window underneath will receive the WM_#BUTTON#### message but not this window.
			// I don't know what the fuck MS thinking now. There is no detailed description on MSDN.
			//                                                                             --Liong 2015.2.17
			SetWindowPos(hWindow, HWND_TOPMOST, 0, 0, size.Width, size.Height, SWP_SHOWWINDOW | SWP_DRAWFRAME);
		}
		else
		{
			ChangeDisplaySettings(NULL, NULL);

			SetWindowLongPtr(hWindow, GWL_STYLE, style);
			SetWindowLongPtr(hWindow, GWL_EXSTYLE, exStyle);
			SetWindowPos(hWindow, HWND_NOTOPMOST, pos.X, pos.Y, size.Width, size.Height, SWP_SHOWWINDOW | SWP_DRAWFRAME);
		}
		return; // Invoke SetWindowPos when we process a outer request will send WM_SIZE message to WndProc so this function will be ivoked twice.
		// Returning here makes everything work normally.
	}

	double &&w = (double)size.Width;
	double &&h = (double)size.Height;
	if (h == 0)
		h = 1;
	glViewport(0, 0, size.Width, size.Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ratio = 1.0f * w / h;
	// Set the correct perspective.
	gluPerspective(90, ratio, 0.0f, 10.0f);
	glOrtho(h/w, h/w, 0.0f, 0.0f, -10.0f, 10.0f);
	//       |    摄像机位置   |       中心      |     朝上的点     |
	gluLookAt(0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	previous = this->size;
	this->size = size;
	
	ResizeEventArgs e(size);

	for (const auto &control : controls)
	{
		if (!control)
			return;
		if (control->Implemented(ControlInterface::IRenderable))
		{
			IRenderable *iRenderable = dynamic_cast<IRenderable *>(control);
			iRenderable->Resize(iRenderable, e);
		}
	}
}

void Window::Flush()
{
	glFlush();
	SwapBuffers(hDeviceContext);
}

HDC Window::GetDeviceContext()
{
	return hDeviceContext;
}

void Window::Remove()
{
	if (isFullScreen)
		isFullScreen = false;

	if (hRenderingContext)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRenderingContext);
		hRenderingContext = NULL;
	}
	if (hDeviceContext && !ReleaseDC(hWindow, hDeviceContext))
		hDeviceContext = NULL;
	if (hWindow && !DestroyWindow(hWindow))
		hWindow = NULL;
	if (!UnregisterClass(L"OpenGLiong", hInstance))
		hInstance = 0;
}

void Window::TrackMouse(long interval)
{
	if (interval > 0)
		_MouseTracker.SetInterval(interval);
	else
		_MouseTracker.Stop();
	_MouseTracker.Start();
}

void Window::Window_MouseButton(void *sender, MouseEventArgs e)
{
	Log << L"Check click... At (" << e.Location.X << L", " << e.Location.Y << L")." << EndLog;

	PointD size_relative = { -50.0 + ((double)(((double)e.Location.X - ((size.Width - size.Height) >> 1)) * 100) / (double)size.Height), 50.0 - ((double)e.Location.Y / (double)size.Height * 100) };

	for (auto &controlBase = controls.rbegin(); controlBase != controls.rend(); controlBase++)
	{
		if (!*controlBase)
			continue;
		if ((*controlBase)->Implemented(ControlInterface::IClickable))
		{
			IClickable *iClickable = dynamic_cast<IClickable *>(*controlBase);
			if (iClickable->IsHover(size_relative))
			{
				iClickable->MouseButton(iClickable, e);
				return;
			}
		}
	}
}

void Window::Window_MouseHover(void *sender, MouseEventArgs e)
{
	async(launch::async, [&]() {
		PointD size_relative = { -50.0 + ((double)(((double)e.Location.X - ((size.Width - size.Height) >> 1)) * 100) / (double)size.Height), 50.0 - ((double)e.Location.Y / (double)size.Height * 100) };

		for (auto &controlBase = controls.rbegin(); controlBase != controls.rend(); controlBase++)
		{
			if (!*controlBase)
				continue;
			if ((*controlBase)->Implemented(ControlInterface::IClickable))
			{
				IClickable *iClickable = dynamic_cast<IClickable *>(*controlBase);
				if (iClickable->IsHover(size_relative))
				{
					iClickable->MouseHover(iClickable, e);
					return;
				}
			}
		}
	});
}

void Window::Window_Render(void *sender, EventArgs e)
{
	for (const auto &control : controls)
	{
		if (!control)
			return;
		if (control->Implemented(ControlInterface::IRenderable))
		{
			IRenderable *iRenderable = dynamic_cast<IRenderable *>(control);
			iRenderable->Render(iRenderable, e);
		}
	}
}

void Window::Window_Resize(void *sender, ResizeEventArgs e)
{
	DoResize(size, true);
}

LRESULT Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window *window = reinterpret_cast<Window *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (uMsg)
	{
		case WM_SIZE:
			window->DoResize({ LOWORD(lParam), HIWORD(lParam) }, false);
			return 0;
		case WM_MOVE:
			if (!window->isFullScreen)
				window->pos = { LOWORD(lParam) - (window->border.Width >> 1), HIWORD(lParam) - (window->border.Height - (window->border.Width >> 1)) };
			return 0;
		case WM_KEYDOWN:
			if (wParam != VK_ESCAPE)
			{
				switch (wParam)
				{
					case VK_F11:
						window->isFullScreen = !window->isFullScreen;
						if (window->isFullScreen)
						{
							Log << L"Try to switch to fullscreen mode..." << EndLog;
							window->Resize(window, new ResizeEventArgs({ GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) }));
						}
						else
						{
							Log << L"Try to switch to window mode..." << EndLog;
							window->Resize(window, new ResizeEventArgs(window->previous));
						}
						break;
					case VK_F12:
						break;
					default:
						break;
				}
				return 0;
			}
		case WM_LBUTTONDOWN:
			window->_MouseDown = true;
			window->MouseButton(window, new MouseEventArgs({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) }, MouseButtons::Left, true));
			return 0;
		case WM_LBUTTONUP:
			window->_MouseDown = false;
			window->MouseButton(window, new MouseEventArgs({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) }, MouseButtons::Left, false));
			return 0;
		case WM_RBUTTONDOWN:
			window->_MouseDown = true;
			window->MouseButton(window, new MouseEventArgs({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) }, MouseButtons::Right, true));
			return 0;
		case WM_RBUTTONUP:
			window->_MouseDown = false;
			window->MouseButton(window, new MouseEventArgs({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) }, MouseButtons::Right, false));
			return 0;
		case WM_DESTROY:
		case WM_CLOSE:
			if (window)
			{
				 window->Remove();
				 PostQuitMessage(0);
				 return 0;
			}
			break;
		default: break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
_L_END