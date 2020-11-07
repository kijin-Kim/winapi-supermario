#include "stdafx.h"
#include "Renderer.h"
#include "Component/PlayerCameraComponent.h"

namespace Engine {

	Renderer::Renderer(int width, int height) :
		m_Width (width), m_Height(height)
	{
		m_hWnd = FindWindow(L"Win32 Window Class",NULL);
		Init();
	}

	void Renderer::Draw(PlayerCameraComponent* camera)
	{
		//ClearColor
		Rectangle(m_hBackBufferDC, -1, -1, m_Width + 1, m_Height + 1);
		//Render
		for (auto layers : m_TextureComponents)
		{
			for(auto t : layers)
				t->Render(m_hBackBufferDC, camera);
		}
		//Present
		HDC hdc = GetDC(m_hWnd);
		BitBlt(hdc, 0, 0, m_Width, m_Height, m_hBackBufferDC, 0, 0, SRCCOPY);
		ReleaseDC(m_hWnd, hdc);
	}

	void Renderer::Init()
	{
		m_TextureComponents.resize(3);

		HDC hdc = GetDC(m_hWnd);

		m_hBackBufferBitMap = CreateCompatibleBitmap(hdc, m_Width, m_Height);
		m_hBackBufferDC = CreateCompatibleDC(hdc);
		SelectObject(m_hBackBufferDC, m_hBackBufferBitMap);
		SetBkMode(m_hBackBufferDC, TRANSPARENT);

		ReleaseDC(m_hWnd, hdc);
	}

	void Renderer::Register(TextureComponent* component)
	{
		if (std::find(m_TextureComponents[component->GetRenderOrder()].begin(),
			m_TextureComponents[component->GetRenderOrder()].end(),
			component) == m_TextureComponents[component->GetRenderOrder()].end())
			m_TextureComponents[component->GetRenderOrder()].push_back(component);
	}

	void Renderer::UnRegister(TextureComponent* component)
	{
		auto it = std::find(m_TextureComponents[component->GetRenderOrder()].begin(), m_TextureComponents[component->GetRenderOrder()].end(), component);
		if (it != m_TextureComponents[component->GetRenderOrder()].end())
			m_TextureComponents[component->GetRenderOrder()].erase(it);
	}

}