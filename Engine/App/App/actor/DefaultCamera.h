#pragma once
#include <Engine.h>

class DefaultCamera : public Engine::Actor
{
public:
	DefaultCamera(Engine::Renderer* renderer, Engine::Layer* layer) : Actor(renderer, layer)
	{
	
		auto transform = new Engine::TransformComponent(this);
		transform->SetPosition({ 320 / 2, 224 / 2 });
		transform->SetVelocity({ 0, 0 });
		Attach(transform);

		auto camera = new Engine::PlayerCameraComponent(this);
		Attach(camera);
	}

};