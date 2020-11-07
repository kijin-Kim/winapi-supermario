#pragma once
#include <vector>

namespace Engine {
	
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void Update(float deltaTiem);
		

		void PushLayer(class Layer* layer);
		void PushOverlay(class Layer* layer);
		void PopLayer(class Layer* layer);
		void PopOverlay(class Layer* layer);
	private:
		std::vector<class Layer*> m_Layers;
		unsigned int m_LayerIndex;
	};

}
