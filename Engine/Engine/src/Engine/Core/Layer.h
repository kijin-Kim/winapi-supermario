#pragma once
#include "Renderer.h"
#include "Application.h"

namespace Engine {

	class Layer
	{
	public:
		Layer(Application* application, int width, int height) : m_Application(application) { 
			m_Renderer = new Renderer(width, height); }
		virtual ~Layer();

		virtual void Enter() {};
		virtual void Exit() {};

		virtual void Update(float deltaTime) {};

		std::vector<class Actor*>& GetWorld();
		std::vector<class Actor*>& GetPendingWorld();
		std::vector<class Actor*>& GetMap();

		Application* GetApplication() const { return m_Application; }


	protected:
		Renderer* m_Renderer;
		std::vector<class Actor*> m_World;
		std::vector<class Actor*> m_Map;
		std::vector<class Actor*> m_PendingWorld;
	private:
		Application* m_Application;
	};

}
