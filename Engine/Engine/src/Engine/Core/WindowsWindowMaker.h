#pragma once
#include <Windows.h>

namespace Engine {
	class WindowsWindowMaker
	{
	public:
		WindowsWindowMaker(class WindowsWindow* window, std::string name, int width, int height);
		~WindowsWindowMaker();


		const HWND& GetWindowHandle() const { return m_Handle; }

	private:
		HINSTANCE m_hIstance;
		HWND m_Handle;
		class WindowsWindow* m_WindowsWindow;
	};
}
