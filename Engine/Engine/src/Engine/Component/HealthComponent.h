#pragma once
#include "Component.h"

namespace Engine {

	class HealthComponent : public Component
	{
	public:
		HealthComponent(Actor* owner) : Component(owner) {}
		virtual ~HealthComponent() {}

		virtual void LoadFromJson(const Json::Value& value) override;
 
		int GetHealth() const { return m_Health; }
		void SetHealth(int health) { m_Health = health; }

		bool HasNoHp() const { return m_Health <= 0; }

	private:
		int m_Health = 1;
	};
}
