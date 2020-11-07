#include "stdafx.h"
#include "WindowsWindowMaker.h"
#include <Windows.h>
#include "Core.h"
#include "WindowsWindow.h"


EXTERN_C IMAGE_DOS_HEADER __ImageBase;
HINSTANCE g;

namespace Engine {

	LRESULT CALLBACK SetWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	WindowsWindowMaker::WindowsWindowMaker(WindowsWindow* window, std::string name, int width, int height) :
		m_WindowsWindow(window),
		m_hIstance(NULL),
		m_Handle(NULL)
	{
		g = m_hIstance = (HINSTANCE)&__ImageBase;
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
		wc.lpfnWndProc = SetWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hIstance;
		wc.hIcon = NULL;
		wc.hIconSm = NULL;
		wc.hCursor = NULL;
		wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
		wc.lpszClassName = L"Win32 Window Class";
		wc.lpszMenuName = NULL;

		RegisterClassEx(&wc);

		DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);
		DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);
		const int xPos = (dwWidth - width) / 2.0f;
		const int yPos = (dwHeight - height) / 2.0f;

		RECT wr;
		wr.left = xPos;
		wr.top = yPos;
		wr.right = wr.left + width;
		wr.bottom = wr.top + height;
		DWORD windowStyle = WS_OVERLAPPEDWINDOW;
		AdjustWindowRect(&wr, windowStyle, false);


		std::wstring windowName;
		windowName.assign(name.begin(), name.end());

		m_Handle = CreateWindowEx(
			NULL,
			wc.lpszClassName,
			windowName.c_str(),
			windowStyle,
			wr.left, wr.top,
			wr.right - wr.left, wr.bottom - wr.top,
			NULL,
			NULL,
			m_hIstance,
			window
		);
		ASSERT(m_Handle, "윈도우 클래스 생성을 실패하였습니다.");
		auto a = GetLastError();
		LOG(std::to_string(a));
		ShowWindow(m_Handle, SW_SHOW);
		SetFocus(m_Handle);

	}

	WindowsWindowMaker::~WindowsWindowMaker()
	{
		DestroyWindow(m_Handle);
	}

	LRESULT CALLBACK RedirectWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return window->OnWndProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT CALLBACK SetWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_NCCREATE:
		{
			const CREATESTRUCTA* const created = reinterpret_cast<CREATESTRUCTA*>(lParam);
			WindowsWindow* window = reinterpret_cast<WindowsWindow*>(created->lpCreateParams);
			ASSERT(window, "치명적인 오류 : WindowsWindow가 전달되지 않았습니다 ");
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(RedirectWndProc));
			return window->OnWndProc(hWnd, uMsg, wParam, lParam);
			break;
		}
		}

	}

}