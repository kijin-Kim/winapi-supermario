#include "stdafx.h"
#include "TransformComponent.h"

namespace Engine {

	TransformComponent::TransformComponent(Actor* owner) :
		Component(owner),
		m_Position({ 0,0 }),
		m_Velocity({ 0,0 })
	{

	}

	void TransformComponent::Update(float deltaTime)
	{
		m_Position.x += m_Velocity.x * deltaTime;
		m_Position.y += m_Velocity.y * deltaTime;

	//	m_Position.x = std::clamp(m_Position.x, (LONG)0 + 8, (LONG)(3392 - 8));
	}

	void TransformComponent::LoadFromJson(const Json::Value& value)
	{
		m_Position.x  = value["Position"]["x"].asInt();
		m_Position.y = value["Position"]["y"].asInt();

		m_Velocity.x = value["Velocity"]["x"].asInt();
		m_Velocity.y = value["Velocity"]["y"].asInt();
	}

}
