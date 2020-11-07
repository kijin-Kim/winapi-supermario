#include "stdafx.h"
#include "WindowsWindow.h"
#include "Core.h"
#include "Layer.h"
#include "WindowsWindowMaker.h"


namespace Engine {

	WindowsWindow::WindowsWindow(std::string appName, int width, int height) :
		m_Name(appName),
		m_Width(width),
		m_Height(height),
		m_WindowsWindowMaker (new WindowsWindowMaker(this, appName, width, height)),
		m_bShouldBeClosed(false)
	{
		
	}

	WindowsWindow::~WindowsWindow()
	{
		delete m_WindowsWindowMaker;
	}


	LRESULT WindowsWindow::OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
		{
			m_bShouldBeClosed = true;
			DestroyWindow(hWnd);
		}
			break;
		default:
			break;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void WindowsWindow::ProcessMessage()
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	const HWND& WindowsWindow::GetWindowHandle() const
	{
		return m_WindowsWindowMaker->GetWindowHandle();
	}

}