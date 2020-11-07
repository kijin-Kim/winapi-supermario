#include "stdafx.h"
#include "Application.h"
#include "Renderer.h"
#include "WindowsWindow.h"
#include "SoundEngine.h"

namespace Engine {

	bool Application::s_bIsInstantiated = false;;

	Application::Application(std::string appName, int width, int height) :
		m_Window(new WindowsWindow(appName, width, height)),
		m_bIsRunning(true)
	{
		ASSERT(!s_bIsInstantiated, "어플리케이션이 이미 존재합니다.");
		s_bIsInstantiated = true;
		m_SoundEngine = new SoundEngine();
	}

	Application::~Application()
	{
		s_bIsInstantiated = false;
		delete m_Window;
		delete m_SoundEngine;
	}

	void Application::Run()
	{
		LARGE_INTEGER lastCount;
		QueryPerformanceCounter(&lastCount);
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		auto lastTime = lastCount.QuadPart / (float)frequency.QuadPart;

		while (m_bIsRunning)
		{
			LARGE_INTEGER count;
			
			QueryPerformanceCounter(&count);
			auto currentTime = count.QuadPart / (float)frequency.QuadPart;
			auto dt = currentTime - lastTime;
			lastTime = currentTime;


			if (!m_Window->ShouldBeClosed())
			{
				m_Window->ProcessMessage();
				UpdateApplication(dt);
				update(dt);

			}
			else
				m_bIsRunning = false;
		}
	}

	void Application::update(float deltaTime)
	{
		m_LayerStack.Update(deltaTime);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* layer)
	{
		m_LayerStack.PopOverlay(layer);
	}

	SoundEngine* Application::GetSoundEngine() const
	{
		return m_SoundEngine;
	}

}