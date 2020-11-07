#include "stdafx.h"
#include "LayerStack.h"

#include "Layer.h"

namespace Engine {


	LayerStack::LayerStack() :m_LayerIndex(0)
	{

	}

	LayerStack::~LayerStack()
	{
		while (!m_Layers.empty())
		{
			delete m_Layers.back();
			m_Layers.pop_back();
		}
	}

	void LayerStack::Update(float deltaTime)
	{
		/*for (Layer* layer : m_Layers)
			layer->Update(deltaTime);*/
		if(!m_Layers.empty())
			m_Layers.back()->Update(deltaTime);
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layer->Enter();
		m_Layers.emplace(m_Layers.begin() + m_LayerIndex, layer);
		m_LayerIndex++;
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		layer->Enter();
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		layer->Exit();
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerIndex, layer);
		if (it != m_Layers.begin() + m_LayerIndex)
		{
			//delete (*it);
			m_Layers.erase(it);
		}
		m_LayerIndex--;
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		layer->Exit();
		auto it = std::find(m_Layers.begin() + m_LayerIndex, m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			//delete (*it);
			m_Layers.erase(it);
		}
	}

}