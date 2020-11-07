#include "stdafx.h"
#include "Input.h"

namespace Engine {

	bool Input::IsKeyPressed(const int key)
	{
		return GetKeyState(key) & 0x8000;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		POINT point = {};
		GetCursorPos(&point);
		return{(float)point.x, (float)point.y};
		
	}

	float Input::GetMouseX()
	{
		auto [x,y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}

}