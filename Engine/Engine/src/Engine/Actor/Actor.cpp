#include "stdafx.h"
#include "Actor.h"
#include "Component/Component.h"
#include "Core/Renderer.h"
#include "Core/Layer.h"


namespace Engine {

	Actor::Actor(Renderer* renderer, Layer* layer) :
		m_Renderer(renderer),
		m_Layer(layer)
	{

	}

	Actor::~Actor()
	{
		while (!m_Components.empty())
		{
			delete m_Components.back();
			m_Components.pop_back();
		}
	}

	void Actor::Update(float deltaTime)
	{
		for (auto comp : m_Components)
			comp->Update(deltaTime);

		UpdateActors(deltaTime);
	}

	void Actor::Attach(Component* component)
	{
		m_ComponentMap[&typeid(*component)] = component;
		m_Components.push_back(component);
	}

	std::vector<Actor*>& Actor::GetWorld()
	{
		return m_Layer->GetWorld();
	}

	std::vector<Actor*>& Actor::GetPendingWorld()
	{
		return m_Layer->GetPendingWorld();
	}

	std::vector<Actor*>& Actor::GetMap()
	{
		return m_Layer->GetMap();
	}
}