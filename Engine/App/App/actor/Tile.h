#pragma once
#include <Engine.h>
#include "Item.h"

class Tile : public Engine::Actor
{
public:
	Tile(Engine::Renderer* renderer, Engine::Layer* layer) : Actor(renderer, layer)
	{
		auto tex = new Engine::TextureComponent(this);
		tex->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/tile_set"),
			{ 0,0,16,16 }));
		tex->SetRenderOrder(1);
		Attach(tex);

		auto transform = new Engine::TransformComponent(this);
		transform->SetPosition({ 100,200 });
		transform->SetVelocity({ 0,0 });
		Attach(transform);

	}

	virtual void UpdateActors(float deltaTime) override 
	{
		if (HasComponent<Engine::HealthComponent>() && 
			GetComponent<Engine::HealthComponent>()->GetHealth() <= 0)
		{
			SetActive(false);
		}
	}
};


class RandomTile : public Tile
{
public:
	RandomTile(Engine::Renderer* renderer, Engine::Layer* layer) : Tile(renderer, layer) {}

	virtual void UpdateActors(float deltaTime) override
	{
		if (HasComponent<Engine::HealthComponent>())
		{
			if (GetComponent<Engine::HealthComponent>()->GetHealth() == 1)
			{
				GetComponent<Engine::TextureComponent>()->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/tile_set"),
					{ 16 * 27, 0, 16 * 28, 16 }));

				//POP Star or Mushroom
				auto transform = GetComponent<Engine::TransformComponent>();
				
				int seed = rand() % 3;

				auto item = new Item(GetRenderer(), GetLayer());
				auto itemTransform = item->GetComponent<Engine::TransformComponent>();
				itemTransform->SetPosition({ transform->GetPosition().x, transform->GetPosition().y + 16 });
				GetPendingWorld().push_back(item);

				GetComponent<Engine::HealthComponent>()->SetHealth(0);
			}
			
		}
	}
};