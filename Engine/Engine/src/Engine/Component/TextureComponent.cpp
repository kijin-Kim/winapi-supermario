#include "stdafx.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "PlayerCameraComponent.h"
#include "Actor/Actor.h"
#include "Core/Renderer.h"
#include "Core/BitmapMananger.h"

namespace Engine {

	TextureComponent::TextureComponent(Actor* owner) :
		Component(owner),
		m_Texture(NULL),
		m_Order(2)
	{
	}

	TextureComponent::~TextureComponent()
	{
		m_Owner->GetRenderer()->UnRegister(this);
	}

	void TextureComponent::SetTexture(const Texture& texture)
	{
		m_Texture = texture;
	}

	void TextureComponent::Render(HDC hdc, PlayerCameraComponent* camera)
	{
		if (m_Texture.Bitmap)
		{
			HDC memdc = CreateCompatibleDC(hdc);
			SelectObject(memdc, m_Texture.Bitmap);
			
			int texWidth = m_Texture.SubRegion.right - m_Texture.SubRegion.left;
			int texHeight = m_Texture.SubRegion.bottom - m_Texture.SubRegion.top;

			Float2 position;

			auto ownerPosition = m_Owner->GetComponent<TransformComponent>()->GetPosition();
			auto cameraPosition = camera->GetPosition();

			if (camera->GetPosition().x - 320 / 2 <= 0)
			{
				position = { ownerPosition.x - texWidth / 2,
						224 - (ownerPosition.y + texHeight / 2) };
			}
			else if (camera->GetPosition().x + 320 / 2 >= 3392)
			{
				position = { -camera->GetPosition().x + 320 / 2,
						224 - (ownerPosition.y + texHeight / 2) };
			}
			else
			{
				position = { ownerPosition.x - texWidth / 2
							- camera->GetPosition().x + 320 / 2,
						224 - (ownerPosition.y + texHeight / 2) };
			}

			TransparentBlt(hdc,
				(LONG)position.x, (LONG)position.y, texWidth, texHeight,
				memdc, m_Texture.SubRegion.left, m_Texture.SubRegion.top, texWidth, texHeight, RGB(255, 255, 255));


			DeleteDC(memdc);
		}	
	}

	void TextureComponent::SetRenderOrder(int renderOrder)
	{
		m_Order = renderOrder;
		m_Owner->GetRenderer()->Register(this);
	}

	void TextureComponent::LoadFromJson(const Json::Value& value)
	{
		std::string FileName = value["Texture"]["FileName"].asString();
		RECT region = { value["Texture"]["Region"]["Top"].asInt(), value["Texture"]["Region"]["Left"].asInt(),
			value["Texture"]["Region"]["Right"].asInt(), value["Texture"]["Region"]["Bottom"].asInt() };
		int renderOrder = value["RenderOrder"].asInt();

		m_Texture = Texture(BitmapMananger::GetImage(FileName), region);
		m_Order = renderOrder;
	}

}