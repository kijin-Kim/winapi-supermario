#pragma once
#include "Component.h"
#include "TransformComponent.h"

namespace Engine {

	class PlayerCameraComponent : public Component
	{
	public:
		PlayerCameraComponent(Actor* owner) :
			Component(owner)
		{
		}
		virtual ~PlayerCameraComponent() {}

  		Float2 GetPosition() const { return m_Owner->GetComponent<TransformComponent>()->GetPosition(); }

		virtual void LoadFromJson(const Json::Value& value) { }
	};
}
