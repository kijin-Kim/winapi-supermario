#include "Mario.h"
#include "Fire.h"

Mario::Mario(Engine::Renderer* renderer, Engine::Layer* layer) :
	Actor(renderer, layer)
{
	auto anime = new Engine::AnimatedTextureComponent(this);
	anime->SetAnimatedTexture({
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"),
		{16 * 6, 16 * 2, 16 * 7 ,32 * 1 })
		});
	anime->SetRenderOrder(2);

	Attach(anime);

	auto transform = new Engine::TransformComponent(this);
	transform->SetPosition({ 320/2, 224 / 2 });
	transform->SetVelocity({ 0, 0 });
	Attach(transform);

	auto camera = new Engine::PlayerCameraComponent(this);
	Attach(camera);
}

void Mario::UpdateActors(float deltaTime)
{
	// Normal ------------------------------------------------------------------------------------

	static auto IdleRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 2, 16 * 7 ,16 * 3})
	};

	static auto IdleLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 2, 16 * 13 ,16 * 3}) 
	};

	static auto WalkRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 0, 16 * 2, 16 * 1 ,16 * 3}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 1, 16 * 2, 16 * 2 ,16 * 3}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 2, 16 * 2, 16 * 3 ,16 * 3}),
	};

	static auto WalkLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 18, 16 * 2, 16 * 19 ,16 * 3}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 17, 16 * 2, 16 * 18 ,16 * 3}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 16, 16 * 2, 16 * 17 ,16 * 3}),
	};

	static auto CrouchLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 18, 16 * 2, 16 * 19 ,16 * 3}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 17, 16 * 2, 16 * 18 ,16 * 3}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 16, 16 * 2, 16 * 17 ,16 * 3}),
	};

	static auto JumpRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 2, 16 * 5 ,16 * 3})
	};

	static auto JumpLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 2, 16 * 15 ,16 * 3})
	};

	// Mushroom ------------------------------------------------------------------------------------

	static auto MushroomIdleRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 0, 16 * 7 ,16 * 2})
	};

	static auto MushroomIdleLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 0, 16 * 13 ,16 * 2})
	};

	static auto MushroomWalkRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 0, 16 * 0, 16 * 1 ,16 * 2}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 1, 16 * 0, 16 * 2 ,16 * 2}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 2, 16 * 0, 16 * 3 ,16 * 2}),
	};

	static auto MushroomWalkLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 18, 16 * 0, 16 * 19 ,16 * 2}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 17, 16 * 0, 16 * 18 ,16 * 2}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 16, 16 * 0, 16 * 17 ,16 * 2}),
	};

	static auto MushroomJumpRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 0, 16 * 5 ,16 * 2})
	};

	static auto MushroomJumpLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 0, 16 * 15 ,16 * 2})
	};


	static auto MushroomCrouchLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 13, 16 * 0, 16 * 14 ,16 * 2})
	};
	static auto MushroomCrouchRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 5, 16 * 0, 16 * 6 ,16 * 2})
	};

	//----------------------------------------------------------------------------------------------------------------------------------------------

	static auto FireFlowerIdleRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 3, 16 * 7 ,16 * 5})
	};

	static auto FireFlowerIdleLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 3, 16 * 13 ,16 * 5})
	};

	static auto FireFlowerWalkRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 0, 16 * 3, 16 * 1 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 1, 16 * 3, 16 * 2 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 2, 16 * 3, 16 * 3 ,16 * 5}),
	};

	static auto FireFlowerWalkLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 18, 16 * 3, 16 * 19 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 17, 16 * 3, 16 * 18 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 16, 16 * 3, 16 * 17 ,16 * 5}),
	};

	static auto FireFlowerJumpRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 3, 16 * 5 ,16 * 5})
	};

	static auto FireFlowerJumpLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 3, 16 * 15 ,16 * 5})
	};


	static auto FireFlowerCrouchLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 13, 16 * 3, 16 * 14 ,16 * 5})
	};
	static auto FireFlowerCrouchRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 5, 16 * 3, 16 * 6 ,16 * 5})
	};


	//--------------------------------------------------------------------------------------------------------------------------------


	static auto StarIdleRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 3, 16 * 7 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 6, 16 * 7 ,16 * 8}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 9, 16 * 7 ,16 * 11}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 12, 16 * 7 ,16 * 14}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 15, 16 * 7 ,16 * 17}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 18, 16 * 7 ,16 * 20}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 21, 16 * 7 ,16 * 23}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 24, 16 * 7 ,16 * 26}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 6, 16 * 27, 16 * 7 ,16 * 29}),
	};

	static auto StarIdleLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 3, 16 * 13 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 6, 16 * 13 ,16 * 8}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 9, 16 * 13 ,16 * 11}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 12, 16 * 13 ,16 * 14}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 15, 16 * 13 ,16 * 17}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 18, 16 * 13 ,16 * 20}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 21, 16 * 13 ,16 * 23}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 24, 16 * 13 ,16 * 26}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 12, 16 * 27, 16 * 13 ,16 * 29}),
	};

	static auto StarWalkRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 0, 16 * 3, 16 * 1 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 1, 16 * 6, 16 * 2 ,16 * 8}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 2, 16 * 9, 16 * 3 ,16 * 11}),

	};

	static auto StarWalkLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 18, 16 * 3, 16 * 19 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 17, 16 * 6, 16 * 18 ,16 * 8}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 16, 16 * 9, 16 * 17 ,16 * 11}),
	};

	static auto StarJumpRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 3, 16 * 5 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 6, 16 * 5 ,16 * 8}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 9, 16 * 5 ,16 * 11}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 12, 16 * 5 ,16 * 14}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 15, 16 * 5 ,16 * 17}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 18, 16 * 5 ,16 * 20}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 21, 16 * 5 ,16 * 23}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 24, 16 * 5 ,16 * 26}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 4, 16 * 27, 16 * 5 ,16 * 29}),
	};

	static auto StarJumpLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 3, 16 * 15 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 6, 16 * 15 ,16 * 8}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 9, 16 * 15 ,16 * 11}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 12, 16 * 15 ,16 * 14}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 15, 16 * 15 ,16 * 17}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 18, 16 * 15 ,16 * 20}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 21, 16 * 15 ,16 * 23}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 24, 16 * 15 ,16 * 26}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 14, 16 * 27, 16 * 15 ,16 * 29}),
	};


	static auto StarCrouchLeftTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 13, 16 * 3, 16 * 14 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 13, 16 * 6, 16 * 14 ,16 * 8}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 13, 16 * 9, 16 * 14 ,16 * 11}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 13, 16 * 12, 16 * 14 ,16 * 14}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 13, 16 * 15, 16 * 14 ,16 * 17}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 13, 16 * 18, 16 * 14 ,16 * 20}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 13, 16 * 21, 16 * 14 ,16 * 23}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 13, 16 * 24, 16 * 14 ,16 * 26}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario_reversed"), {16 * 13, 16 * 27, 16 * 14 ,16 * 29}),
	};
	static auto StarCrouchRightTextures = {
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 5, 16 * 3, 16 * 6 ,16 * 5}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 5, 16 * 6, 16 * 6 ,16 * 8}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 5, 16 * 9, 16 * 6 ,16 * 11}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 5, 16 * 12, 16 * 6 ,16 * 14}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 5, 16 * 15, 16 * 6 ,16 * 17}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 5, 16 * 18, 16 * 6 ,16 * 20}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 5, 16 * 21, 16 * 6 ,16 * 23}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 5, 16 * 24, 16 * 6 ,16 * 26}),
		Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/mario"), {16 * 5, 16 * 27, 16 * 6 ,16 * 29}),
	};

	//------------------------------------------------------------------------------------------------------------------------------



	

	auto transform = GetComponent<Engine::TransformComponent>();
	auto anime = GetComponent<Engine::AnimatedTextureComponent>();
	auto power = GetComponent<Engine::PowerComponent>();

	if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
	{
		m_bRunningScale = 2.0f;
	}
	else
		m_bRunningScale = 1.0f;

	if (transform->GetPosition().y <= 0.0f)
	{
		GetLayer()->GetApplication()->Gameover();
	}


	if (Engine::Input::IsKeyPressed(VK_RIGHT))
	{
		if (m_State == MarioState::Idle)
		{
			m_State = MarioState::Walk;
		}
		else if(m_State == MarioState::Jump)
			transform->SetVelocity({ 100 * m_bRunningScale, transform->GetVelocity().y });

		m_Direction = Direction::Right;

	}
	else if (Engine::Input::IsKeyPressed(VK_LEFT))
	{
		if (m_State == MarioState::Idle)
		{
			m_State = MarioState::Walk;
		}
		else if (m_State == MarioState::Jump)
			transform->SetVelocity({ -100 * m_bRunningScale, transform->GetVelocity().y });

		m_Direction = Direction::Left;
	}
	else if (Engine::Input::IsKeyPressed(VK_DOWN))
	{
		if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Mushroom) ||
			power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower))
		{
			if (m_State == MarioState::Walk)
				transform->SetVelocity({ 0,transform->GetVelocity().y });
			m_State = MarioState::Crouch;
		}
	}
	else
	{
		if(m_State!= MarioState::Jump)
			m_State = MarioState::Idle;
	}

	if (Engine::Input::IsKeyPressed(VK_SPACE))
	{
		if (!m_bShouldJump)
		{
			GetLayer()->GetApplication()->
				GetSoundEngine()->Play("Jump");
			transform->SetVelocity({ transform->GetVelocity().x, m_MaxJumpVelocity });
			m_JumpIncreasedRate = 0.0f;
		}
		else if (m_JumpIncreasedRate <= 7.0 * 30)
		{
			m_JumpIncreasedRate += 7.0f;
			transform->SetVelocity({ transform->GetVelocity().x, transform->GetVelocity().y + 7.0f});
		}
		m_bShouldJump = true;
	
		m_State = MarioState::Jump;
	}

	if ((power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
		!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star) && 
		Engine::Input::IsKeyPressed('A')))
	{
		if (m_FireTimer <= 0.0f)
		{
			GetLayer()->GetApplication()->
				GetSoundEngine()->Play("FireBall");

			m_FireTimer = m_MaxFireDelay;

			auto fire = new Fire(GetRenderer(), GetLayer());
			auto fireTransform = fire->GetComponent<Engine::TransformComponent>();
			fireTransform->SetPosition({ transform->GetPosition().x, transform->GetPosition().y });
			if(m_Direction == Direction::Left)
				fireTransform->SetVelocity({ -200, 0 });
			else
				fireTransform->SetVelocity({ 200, 0 });

			GetPendingWorld().push_back(fire);
		}
	}
	m_FireTimer -= deltaTime;

	if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Mushroom) ||
		power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) ||
		power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
	{
		GetComponent<Engine::ColliderComponent>()->SetColliderSize({ 16,32 });
	}
	else
	{
		GetComponent<Engine::ColliderComponent>()->SetColliderSize({ 16,16 });
	}

	switch (m_State)
	{
	case Mario::MarioState::Idle:
		transform->SetVelocity({ 0,transform->GetVelocity().y });
		if (m_Direction == Direction::Left)
		{
			if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Mushroom) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(MushroomIdleLeftTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(FireFlowerIdleLeftTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(StarIdleLeftTextures);
			}
			else
				anime->SetAnimatedTexture(IdleLeftTextures);
		}
		else
		{
			if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Mushroom) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(MushroomIdleRightTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(FireFlowerIdleRightTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(StarIdleRightTextures);
			}
			else
				anime->SetAnimatedTexture(IdleRightTextures);
		}
		break;
	case Mario::MarioState::Walk:
		if (m_Direction == Direction::Left)
		{
			transform->SetVelocity({ -100 * m_bRunningScale, transform->GetVelocity().y });

			if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Mushroom) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(MushroomWalkLeftTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(FireFlowerWalkLeftTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(StarWalkLeftTextures);
			}
			else
				anime->SetAnimatedTexture(WalkLeftTextures);

		}
		else
		{
			transform->SetVelocity({ 100 * m_bRunningScale, transform->GetVelocity().y });

			if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Mushroom) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(MushroomWalkRightTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(FireFlowerWalkRightTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(StarWalkRightTextures);
			}
			else
				anime->SetAnimatedTexture(WalkRightTextures);
		}
		break;
	case Mario::MarioState::Jump:
	{
		if (m_Direction == Direction::Left)
		{
			if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Mushroom) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(MushroomJumpLeftTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(FireFlowerJumpLeftTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(StarJumpLeftTextures);
			}
			else
				anime->SetAnimatedTexture(JumpLeftTextures);
		}
		else
		{
			if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Mushroom) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(MushroomJumpRightTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(FireFlowerJumpRightTextures);
			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(StarJumpRightTextures);
			}
			else
				anime->SetAnimatedTexture(JumpRightTextures);
		}

		auto collider = GetComponent<Engine::ColliderComponent>();
		if (collider->m_bShouldStopJump)
		{
			collider->m_bShouldStopJump = false;
			m_bShouldJump = false;
			m_State = MarioState::Idle;
		}
	}
		break;
	case MarioState::Crouch:
	{
		if (m_Direction == Direction::Left)
		{
		if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Mushroom) &&
			!power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
			!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
		{
			anime->SetAnimatedTexture(MushroomCrouchLeftTextures);
		}
		else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
			!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
		{
			anime->SetAnimatedTexture(FireFlowerCrouchLeftTextures);
		}
		else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
		{
			anime->SetAnimatedTexture(StarCrouchLeftTextures);
		}
			
		}
		else
		{
			if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Mushroom) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) &&
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(MushroomCrouchRightTextures);
			}
			else if ( power->IsPowerEnabled(Engine::PowerComponent::PowerType::FireFlower) && 
				!power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(FireFlowerCrouchRightTextures);

			}
			else if (power->IsPowerEnabled(Engine::PowerComponent::PowerType::Star))
			{
				anime->SetAnimatedTexture(StarCrouchRightTextures);
			}
		}
	}
		break;
	default:
		break;
	}

}
