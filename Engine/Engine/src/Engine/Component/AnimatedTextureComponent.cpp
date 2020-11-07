#include "stdafx.h"
#include "AnimatedTextureComponent.h"
#include "Core/BitmapMananger.h"

namespace Engine {


	AnimatedTextureComponent::AnimatedTextureComponent(Actor* owner) :
		TextureComponent(owner),
		m_CurrentFrame(0.0f),
		m_FramePerSec(10.0f)
	{

	}

	AnimatedTextureComponent::~AnimatedTextureComponent()
	{

	}

	void AnimatedTextureComponent::Update(float deltaTime)
	{
		if (!m_Textures.empty())
		{
			m_CurrentFrame += m_FramePerSec * deltaTime;
			while (m_CurrentFrame >= m_Textures.size())
				m_CurrentFrame -= m_Textures.size();

			TextureComponent::SetTexture(m_Textures[m_CurrentFrame]);
		}
	}

	
	void AnimatedTextureComponent::SetAnimatedTexture(const std::initializer_list<Texture>& textures)
	{
		m_Textures = textures;
		//TextureComponent::SetTexture(m_Textures[0]);
	}

	void AnimatedTextureComponent::LoadFromJson(const Json::Value& value)
	{
		std::vector<Texture> textures;

		for (int i = 0; i < value["Textures"].size(); i++)
		{
			std::string FileName = value["Textures"][i]["FileName"].asString();
			RECT region = { value["Textures"][i]["Region"]["Top"].asInt(), value["Textures"][i]["Region"]["Left"].asInt(),
				value["Textures"][i]["Region"]["Right"].asInt(), value["Textures"][i]["Region"]["Bottom"].asInt() };
		}

		int renderOrder = value["RenderOrder"].asInt();

		SetRenderOrder(renderOrder);
	}

}