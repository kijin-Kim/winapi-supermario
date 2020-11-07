#pragma once
#pragma comment(lib, "msimg32.lib")
#include <vector>
#include <windows.h>
#include "../Component/TextureComponent.h"


namespace Engine {

	class Renderer
	{
	public:
		Renderer(int width, int height);

		void Draw(class PlayerCameraComponent* camera);
		void Init();
		void Register(TextureComponent* component);
		void UnRegister(TextureComponent* component);


	private:
		int m_Width;
		int m_Height;

		HBITMAP m_hBackBufferBitMap;
		HDC m_hBackBufferDC;
		HWND m_hWnd;

		std::vector<std::vector<TextureComponent*>> m_TextureComponents;
	};
}
