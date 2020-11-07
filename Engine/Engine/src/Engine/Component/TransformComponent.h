#pragma once
#include <wtypes.h>
#include "Component.h"

namespace Engine {

	struct Float2
	{
		Float2() : x(0), y(0) { }
		Float2(float x, float y) : x(x), y(y) { }

		float x;
		float y;
	};

	class TransformComponent : public Component
	{
	public:
		TransformComponent(class Actor* owner);
		virtual ~TransformComponent() {}

		virtual void Update(float deltaTime) override final;

		Float2 GetPosition() const { return m_Position; }
		Float2 GetVelocity() const { return m_Velocity; }

		void SetPosition(Float2 position) { m_Position = position; }
		void SetVelocity(Float2 velocity) { m_Velocity = velocity; }

		virtual void LoadFromJson(const Json::Value& value) override;

	private:
		Float2 m_Position;
		Float2 m_Velocity;
	};

};

