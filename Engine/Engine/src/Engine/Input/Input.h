#pragma once
#include <utility>

namespace Engine {

	class Input
	{
	public:
		static bool IsKeyPressed(const int key);
		static std::pair<float,float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
