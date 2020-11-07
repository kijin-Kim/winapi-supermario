#pragma once
#include <Engine.h>

class Enemy : public Engine::Actor
{
public:
	Enemy(Engine::Renderer* renderer, Engine::Layer* layer) : Actor(renderer, layer)
	{
		auto anime = new Engine::AnimatedTextureComponent(this);
		anime->SetAnimatedTexture({ 
			Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/enemies"), {16 * 0, 16 * 1, 16 * 1 ,16 * 2 }) ,
			Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/enemies"), {16 * 1, 16 * 1, 16 * 2 ,16 * 2 }) });
		anime->SetRenderOrder(2);

		Attach(anime);

		auto transform = new Engine::TransformComponent(this);
		transform->SetPosition({ 320 / 2, 224 / 2 });
		transform->SetVelocity({ 100, 0 });
		Attach(transform);

		auto collider = new Engine::ColliderComponent(this);
		collider->SetColliderTag("Enemy");
		collider->SetColliderSize({ 16,16 });
		collider->SetGravityEnabled();
		Attach(collider);
	}

};
