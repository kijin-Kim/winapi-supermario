#pragma once
#include <Windows.h>
#include "LayerStack.h"

namespace Engine {

	class Application
	{
	public:
		Application(std::string appName, int width, int height);
		virtual ~Application();

		void Run();

		static Application* CreateApplicaton();

		virtual void Gameover() {}
		virtual void GameClear() {}

		class  SoundEngine* GetSoundEngine() const;
	protected:
		void PushLayer(class Layer* layer);
		void PushOverlay(class Layer* layer);
		void PopLayer(class Layer* layer);
		void PopOverlay(class Layer* layer);
		virtual void UpdateApplication(float deltaTime) {}
		void QuitApplication() { m_bIsRunning = false; }
	private:
		void update(float deltaTime);
	private:
		class WindowsWindow* m_Window;
		bool m_bIsRunning;
		float m_TimeElapsed = 0.0f;
		LayerStack m_LayerStack;
		class SoundEngine* m_SoundEngine;
		static bool s_bIsInstantiated;
	};
}

#define RegisterApplication(x) Engine::Application* Engine::Application::CreateApplicaton()\
{\
	return new x();\
}