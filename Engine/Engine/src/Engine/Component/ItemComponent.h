#pragma once
#include "Component.h"

namespace Engine {

	class ItemComponent : public Component
	{
	public:
		enum class ItemType
		{
			None, Coin, FireFlower, Star, Mushroom
		};

		ItemComponent(Actor* owner) : Component(owner) {}
		virtual ~ItemComponent() {}

		virtual void LoadFromJson(const Json::Value& value) override {}

		void SetItemType(ItemType type) { m_ItemType = type; }
		ItemType GetItemType() const { return m_ItemType; }

	private:
		ItemType m_ItemType = ItemType::None;
	};
}