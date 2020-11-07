#include "stdafx.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "HealthComponent.h"
#include "PowerComponent.h"
#include "ItemComponent.h"
#include "../Core/Application.h"
#include "../Core/Layer.h"
#include "../Core/SoundEngine.h"

namespace Engine {

	void ColliderComponent::Update(float deltaTime)
	{
		m_ImmortalTimer -= deltaTime;
		auto transform = m_Owner->GetComponent<TransformComponent>();
		if (m_bGravityIsEnabled)
		{
			transform->SetVelocity({ transform->GetVelocity().x, transform->GetVelocity().y + (-9.8f * 50.0f) * deltaTime });
		}
		
		m_Collider.top = transform->GetPosition().y - m_ColliderSize.y / 2;
		m_Collider.left = transform->GetPosition().x - m_ColliderSize.x / 2;
		m_Collider.right = transform->GetPosition().x + m_ColliderSize.x / 2;
		m_Collider.bottom = transform->GetPosition().y + m_ColliderSize.y / 2;
	}

	void ColliderComponent::LoadFromJson(const Json::Value& value)
	{
		m_ColliderSize.x = value["ColliderSize"]["x"].asInt();
		m_ColliderSize.y = value["ColliderSize"]["y"].asInt();

		m_ColliderTag = value["ColliderTag"].asString();
		m_bGravityIsEnabled = value["Gravity"].asBool();
	}

	void ColliderComponent::CheckCollisionAndResponse(Actor* colliderOwner)
	{
		RECT rect;
		auto collider = colliderOwner->GetComponent<ColliderComponent>();
		if (IntersectRect(&rect, &m_Collider, &collider->GetCollider()))
		{
			int rectWidth = rect.right - rect.left;
			int rectHeight = rect.bottom - rect.top;

			auto tag = collider->GetColliderTag();
			if (m_ColliderTag == "Player" &&tag == "Tile") //BLOCK
			{
				auto transform = m_Owner->GetComponent<TransformComponent>();
				if (rectWidth < rectHeight)
				{
					//왼쪽 또는 오른쪽
					bool bIsLeft = m_Collider.left - collider->GetCollider().left <= 0;
					if (bIsLeft)
					{
						transform->SetPosition({ transform->GetPosition().x - rectWidth, transform->GetPosition().y });
					}
					else
						transform->SetPosition({ transform->GetPosition().x + rectWidth, transform->GetPosition().y });

				}
				else
				{
					bool bIsTop = m_Collider.top - collider->GetCollider().top >= 0;
					if (bIsTop)
					{
						transform->SetVelocity({ transform->GetVelocity().x, 0 });
						transform->SetPosition({ transform->GetPosition().x, transform->GetPosition().y + rectHeight });
						m_bShouldStopJump = true;
					}
					else
					{
						transform->SetVelocity({ transform->GetVelocity().x, -transform->GetVelocity().y });
						transform->SetPosition({ transform->GetPosition().x, transform->GetPosition().y - rectHeight });
						if (colliderOwner->HasComponent<HealthComponent>())
						{
							auto health = colliderOwner->GetComponent<HealthComponent>();
							health->SetHealth(health->GetHealth() - 1);
						}
					}

				}
			}
			else if ((m_ColliderTag == "Item" || m_ColliderTag == "Enemy") && tag == "Tile") //BLOCK
			{
				auto transform = m_Owner->GetComponent<TransformComponent>();
				if (rectWidth < rectHeight)
				{
					//왼쪽 또는 오른쪽
					bool bIsLeft = m_Collider.left - collider->GetCollider().left <= 0;
					if (bIsLeft)
					{
						transform->SetPosition({ transform->GetPosition().x - rectWidth, transform->GetPosition().y });
					}
					else
						transform->SetPosition({ transform->GetPosition().x + rectWidth, transform->GetPosition().y });

					transform->SetVelocity({ -transform->GetVelocity().x, transform->GetVelocity().y });
				}
				else
				{
					bool bIsTop = m_Collider.top - collider->GetCollider().top >= 0;
					if (bIsTop)
					{
						transform->SetVelocity({ transform->GetVelocity().x, 0 });
						transform->SetPosition({ transform->GetPosition().x, transform->GetPosition().y + rectHeight });
					}
					else
					{
						transform->SetPosition({ transform->GetPosition().x, transform->GetPosition().y - rectHeight });
					}

				}
			}
			else if (m_ColliderTag == "Fire" && tag == "Tile") //BLOCK AND BOUNCE
			{
				auto transform = m_Owner->GetComponent<TransformComponent>();
				if (rectWidth < rectHeight)
				{
					m_Owner->SetActive(false);
				}
				else
				{
					bool bIsTop = m_Collider.top - collider->GetCollider().top >= 0;
					if (bIsTop)
					{
						transform->SetPosition({ transform->GetPosition().x, transform->GetPosition().y + rectHeight });
					}
					else
					{
						transform->SetPosition({ transform->GetPosition().x, transform->GetPosition().y - rectHeight });
					}
					transform->SetVelocity({ transform->GetVelocity().x, -transform->GetVelocity().y });
				}
			}

			else if (m_ColliderTag == "Player" && tag == "Item") //Erase
			{
				if (IntersectRect(&rect, &m_Collider, &collider->GetCollider()))
				{
					colliderOwner->SetActive(false);

					auto item = colliderOwner->GetComponent<ItemComponent>();
					auto type = item->GetItemType();
					auto power = m_Owner->GetComponent<PowerComponent>();
					switch (type)
					{
					case Engine::ItemComponent::ItemType::None:
						break;
					case Engine::ItemComponent::ItemType::Coin:
						m_Owner->GetLayer()->GetApplication()->GetSoundEngine()->Play("Coin");
						break;
					case Engine::ItemComponent::ItemType::FireFlower:
						power->EnablePower(PowerComponent::PowerType::FireFlower);
						power->EnablePower(PowerComponent::PowerType::Mushroom);
						m_Owner->GetLayer()->GetApplication()->GetSoundEngine()->Play("PowerUp");
						break;
					case Engine::ItemComponent::ItemType::Star:
						power->EnablePower(PowerComponent::PowerType::Star);
						m_Owner->GetLayer()->GetApplication()->GetSoundEngine()->Stop("Main_Theme");
						m_Owner->GetLayer()->GetApplication()->GetSoundEngine()->Play("Invincible_Theme");
						break;
					case Engine::ItemComponent::ItemType::Mushroom:
						power->EnablePower(PowerComponent::PowerType::Mushroom);
						m_Owner->GetLayer()->GetApplication()->GetSoundEngine()->Play("PowerUp");
						break;
					default:
						break;
					}
				}
			}
			else if (m_ColliderTag == "Player" && tag == "Enemy") //Erase
			{
				auto transform = m_Owner->GetComponent<TransformComponent>();
				bool bIsTop = m_Collider.top - collider->GetCollider().top >= 0;

				if (rectWidth > rectHeight && bIsTop)
				{
					if (m_ImmortalTimer <= 0.0f)
					{
						m_ImmortalTimer = m_MaxImmortalTime;

						transform->SetVelocity({ transform->GetVelocity().x, 0 });
						transform->SetPosition({ transform->GetPosition().x, transform->GetPosition().y + rectHeight });
						colliderOwner->SetActive(false);
						m_Owner->GetLayer()->GetApplication()->GetSoundEngine()->Play("Stomp");
					}					
				}
				else
				{
					auto ownerPower = m_Owner->GetComponent<PowerComponent>();

					if (ownerPower->IsPowerEnabled(PowerComponent::PowerType::Star))
					{
						m_ImmortalTimer = 0.0f;
					}

					if (m_ImmortalTimer <= 0.0f)
					{
						m_ImmortalTimer = m_MaxImmortalTime;

						if (!bIsTop)
						{
							transform->SetPosition({ transform->GetPosition().x, transform->GetPosition().y + rectHeight });
						}
						else if (rectWidth <= rectHeight)
						{
							//왼쪽 또는 오른쪽
							bool bIsLeft = m_Collider.left - collider->GetCollider().left <= 0;
							if (bIsLeft)
							{
								transform->SetPosition({ transform->GetPosition().x - rectWidth, transform->GetPosition().y });
							}
							else
								transform->SetPosition({ transform->GetPosition().x + rectWidth, transform->GetPosition().y });

							transform->SetVelocity({ -transform->GetVelocity().x, transform->GetVelocity().y });
						}

						if (ownerPower->IsPowerEnabled(PowerComponent::PowerType::FireFlower) &&
							!ownerPower->IsPowerEnabled((PowerComponent::PowerType::Star)))
						{
							ownerPower->DisablePower(PowerComponent::PowerType::FireFlower);
						}
						else if (ownerPower->IsPowerEnabled(PowerComponent::PowerType::Mushroom) &&
							!ownerPower->IsPowerEnabled((PowerComponent::PowerType::Star)))
						{
							ownerPower->DisablePower(PowerComponent::PowerType::Mushroom);
						}
						else if (ownerPower->IsPowerEnabled(PowerComponent::PowerType::Star))
						{
							//Immoratal
							colliderOwner->SetActive(false);
							m_Owner->GetLayer()->GetApplication()->GetSoundEngine()->Play("Kick");
						}
						else
						{
							m_Owner->SetActive(false);
						}
					}
				}

			}
			else if (m_ColliderTag == "Fire" && tag == "Enemy") //Erase
			{
				if (IntersectRect(&rect, &m_Collider, &collider->GetCollider()))
				{
					m_Owner->SetActive(false);
					colliderOwner->SetActive(false);
					m_Owner->GetLayer()->GetApplication()->GetSoundEngine()->Play("Kick");
				}
			}
			else if (m_ColliderTag == "Player" && tag == "Clear")
			{
				m_Owner->GetLayer()->GetApplication()->GameClear();
			}

		}

		auto transform = m_Owner->GetComponent<TransformComponent>();
		m_Collider.top = transform->GetPosition().y - m_ColliderSize.y / 2;
		m_Collider.left = transform->GetPosition().x - m_ColliderSize.x / 2;
		m_Collider.right = transform->GetPosition().x + m_ColliderSize.x / 2;
		m_Collider.bottom = transform->GetPosition().y + m_ColliderSize.y / 2;

	}

}

