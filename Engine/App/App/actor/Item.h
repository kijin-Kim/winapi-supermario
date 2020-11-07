#pragma once
#include <Engine.h>

class Item : public Engine::Actor
{
public:
	Item(Engine::Renderer* renderer, Engine::Layer* layer) :
		Actor(renderer, layer)
	{
		auto transform = new Engine::TransformComponent(this);
		transform->SetPosition({ 0, 0 });
		transform->SetVelocity({ 100, 0 });
		Attach(transform);


		auto collider = new Engine::ColliderComponent(this);
		collider->SetColliderTag("Item");
		collider->SetColliderSize({ 16,16});
		collider->SetGravityEnabled();
		Attach(collider);


		auto tex = new Engine::TextureComponent(this);
		tex->SetRenderOrder(1);
		Attach(tex);

		auto item = new Engine::ItemComponent(this);
		int seed = rand() % 4;
		switch (seed)
		{
		case 0:
			item->SetItemType(Engine::ItemComponent::ItemType::Coin);
			tex->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/item_objects"),
				{ 0,16 * 6,16,16 * 7 }));
			transform->SetVelocity({ 0,0 });
			break;
		case 1:
			item->SetItemType(Engine::ItemComponent::ItemType::FireFlower);
			tex->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/item_objects"),
				{ 0,16 * 2,16,16 * 3 }));
			transform->SetVelocity({ 0,0 });
			break;
		case 2:
			item->SetItemType(Engine::ItemComponent::ItemType::Star);
			tex->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/item_objects"),
				{ 0,16 * 3,16,16 * 4 }));
			transform->SetVelocity({ 0,0 });
			break;
		case 3:
			item->SetItemType(Engine::ItemComponent::ItemType::Mushroom);
			tex->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/item_objects"),
				{ 0,0,16,16 }));
			transform->SetVelocity({ 100,0 });
			break;
		default:
			break;
		}
		Attach(item);
	}
};
