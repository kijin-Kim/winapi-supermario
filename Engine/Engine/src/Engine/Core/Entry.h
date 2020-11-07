#include <Windows.h>
#include "WindowsWindow.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	auto app = Engine::Application::CreateApplicaton();
	app->Run();

	delete app;
}