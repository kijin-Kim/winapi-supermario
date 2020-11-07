#pragma once
#include <string>
#include "Component.h"

namespace Engine {

	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(Actor* owner) : Component(owner) {};
		virtual ~ColliderComponent() {}

		virtual void Update(float deltaTime) override final;

		void SetGravityEnabled() { m_bGravityIsEnabled = true; }
		void SetGravitydisabled() { m_bGravityIsEnabled = false; }

		void SetColliderTag(const std::string& tag) { m_ColliderTag = tag; }
		void SetColliderSize(const POINT& colliderSize) { m_ColliderSize = colliderSize; }

		const RECT& GetCollider() { return m_Collider; }
		const std::string GetColliderTag() { return m_ColliderTag; }

		virtual void LoadFromJson(const Json::Value& value);

		void CheckCollisionAndResponse(Actor* colliderOwner);

	public:
		bool m_bShouldStopJump = false;
	private:
		POINT m_ColliderSize = { 16,16 };
		RECT m_Collider = {};
		std::string m_ColliderTag = "default";
		bool m_bGravityIsEnabled = false;
		const float m_MaxImmortalTime = 3.0f;
		float m_ImmortalTimer = 0.0f;
	};

};
