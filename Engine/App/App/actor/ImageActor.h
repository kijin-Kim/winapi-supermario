#pragma once
#include <Engine.h>

class ImageActor :public Engine::Actor
{
public:
	ImageActor(Engine::Renderer* renderer, Engine::Layer* layer) : Actor(renderer, layer)
	{
		auto tex = new Engine::TextureComponent(this);
		tex->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/tile_set"),
			{ 0,0,16,16 }));
		tex->SetRenderOrder(1);
		Attach(tex);

		auto transform = new Engine::TransformComponent(this);
		transform->SetPosition({ 320/2, 224/2});
		transform->SetVelocity({ 0,0 });
		Attach(transform);

	}
};