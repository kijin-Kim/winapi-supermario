#pragma once
#include <Engine.h>

class Fire : public Engine::Actor
{
public:
	Fire(Engine::Renderer* renderer, Engine::Layer* layer) : Actor(renderer, layer)
	{
		auto texture = new Engine::AnimatedTextureComponent(this);
		texture->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/item_objects"),
			{ 16 * 7,16 * 9,16 * 8,16 * 10 }));
		texture->SetRenderOrder(2);

		Attach(texture);

		auto transform = new Engine::TransformComponent(this);
		transform->SetPosition({ 0, 0 });
		transform->SetVelocity({ 200, 0 });
		Attach(transform);

		auto collider = new Engine::ColliderComponent(this);
		collider->SetColliderTag("Fire");
		collider->SetColliderSize({ 16,16 });
		collider->SetGravityEnabled();
		Attach(collider);
	}

};
