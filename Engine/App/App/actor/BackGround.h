#pragma once
#include <Engine.h>

class BackGround : public Engine::Actor
{
public:
	BackGround(Engine::Renderer* renderer, Engine::Layer* layer) : Actor(renderer, layer)
	{
		auto tex = new Engine::TextureComponent(this);
		tex->SetRenderOrder(0);
		auto t = Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/map"));
		tex->SetTexture(t);
		Attach(tex);


		auto transform = new Engine::TransformComponent(this);
		transform->SetPosition({ 3392 / 2, 224 / 2});
		transform->SetVelocity({ 0,0 });
		Attach(transform);
	}

};