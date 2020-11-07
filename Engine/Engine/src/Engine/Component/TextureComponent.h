#pragma once
#include "Component.h"

namespace Engine {

	struct Texture
	{
		HBITMAP Bitmap;
		RECT SubRegion;

		Texture() = default;

		Texture(HBITMAP bitmap, RECT subRegion = {}) :
			Bitmap(bitmap),
			SubRegion(subRegion)
		{
			if (SubRegion.top == 0 &&
				SubRegion.left == 0 &&
				SubRegion.right == 0 &&
				SubRegion.bottom == 0)
			{
				BITMAP bmp;
				GetObject(Bitmap, sizeof(BITMAP), &bmp);
				SubRegion = { 0,0, bmp.bmWidth, bmp.bmHeight };
			}
		}
	};
	
	class TextureComponent : public Component
	{
	public:
		TextureComponent(class Actor* owner);
		virtual ~TextureComponent();

		void SetTexture(const Texture& texture);

		virtual void Render(HDC hdc, class PlayerCameraComponent* camera);

		int GetRenderOrder() const { return m_Order; }
		void SetRenderOrder(int renderOrder);

		virtual void LoadFromJson(const Json::Value& value) override;

	private:
		Texture m_Texture = NULL;
		int m_Order;
	};
}

