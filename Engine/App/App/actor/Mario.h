#pragma once
#include <Engine.h>

class Mario : public Engine::Actor
{
public:

	enum class MarioState
	{
		Idle, Walk, Jump, Crouch
	};
	enum class Direction
	{
		Left, Right
	};

	Mario(Engine::Renderer* renderer, Engine::Layer* layer);
	virtual ~Mario() {}

	virtual void UpdateActors(float deltaTime) override;

private:
	MarioState m_State = MarioState::Idle;
	Direction m_Direction = Direction::Right;
	const float m_MaxJumpVelocity = 150.0f;
	bool m_bShouldJump = false;
	const float m_MaxFireDelay = 0.3f;
	float m_FireTimer = 0.0f;
	float m_bRunningScale = 1.0f;
	float m_JumpIncreasedRate = 0.0f;
};