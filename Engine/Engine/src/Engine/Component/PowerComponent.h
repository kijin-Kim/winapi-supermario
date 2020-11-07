#pragma once
#include "Component.h"
#include <unordered_map>

namespace Engine { 
	class PowerComponent : public Component
	{
	public:
		enum class PowerType {
			Mushroom, FireFlower, Star
		};
	public:
		PowerComponent(Actor* owner) : Component(owner) 
		{
			
		}
		virtual ~PowerComponent() {}

		virtual void Update(float deltaTime) override;


		void EnablePower(PowerType type) { m_bIsPowerEnabled[type] = true; }
		void DisablePower(PowerType type) { m_bIsPowerEnabled[type] = false; }

		virtual void LoadFromJson(const Json::Value& value) {}

		bool IsPowerEnabled(PowerType type) { return m_bIsPowerEnabled[type]; }
		
	private:
		std::unordered_map<PowerType, bool> m_bIsPowerEnabled;
		const float m_MaxStarTimer = 10.0f;
		float m_StarTimer = 10.0f;
	};
}
