#pragma once
#include <string>
#include <windows.h>
#include "Application.h"

namespace Engine {

	class WindowsWindow
	{
	public:
		WindowsWindow(std::string appName, int width, int height);
		~WindowsWindow();
		 
		LRESULT OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void ProcessMessage();

		bool ShouldBeClosed() const { return m_bShouldBeClosed; }


		const std::string& GetName() const { return m_Name; }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

		const HWND& GetWindowHandle() const;


	private:
		class WindowsWindowMaker* m_WindowsWindowMaker;
		bool m_bShouldBeClosed;

		std::string m_Name;
		int m_Width;
		int m_Height;
	};
}