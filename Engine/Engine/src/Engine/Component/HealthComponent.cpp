#include "stdafx.h"
#include "HealthComponent.h"

namespace Engine {

	void HealthComponent::LoadFromJson(const Json::Value& value)
	{
		m_Health = value["Health"].asInt();
	}

}