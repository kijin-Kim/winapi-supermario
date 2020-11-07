#pragma once
#include "TextureComponent.h"

namespace Engine {

	class AnimatedTextureComponent : public TextureComponent
	{
	public:
		AnimatedTextureComponent(class Actor* owner);
		virtual ~AnimatedTextureComponent();

		virtual void Update(float deltaTime) override;

		void SetAnimatedTexture(const std::initializer_list<Texture>& textures);
		void SetRenderOrder(int renderOrder) { TextureComponent::SetRenderOrder(renderOrder); }

		virtual void LoadFromJson(const Json::Value& value) override;

	private:
		std::vector<Texture> m_Textures;
		float m_CurrentFrame;
		float m_FramePerSec;
	};
}