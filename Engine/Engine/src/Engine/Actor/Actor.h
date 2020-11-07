#pragma once
#include <vector>
#include <map>
#include <typeinfo>
#include "../vendor/JsonCpp/json/json.h"

namespace Engine {

	class Actor
	{
	public:
		Actor(class Renderer* renderer, class Layer* layer);
		virtual ~Actor();

		void Update(float deltaTime);
		virtual void UpdateActors(float deltaTime) {}

		void Attach(class Component* component);

		class Renderer* GetRenderer() const { return m_Renderer; }
		class Layer* GetLayer() const { return m_Layer; }

		template<typename T>
		T* GetComponent()
		{
			return (T*)(m_ComponentMap[&typeid(T)]);
		}
		template<typename T>
		bool HasComponent()
		{
			return m_ComponentMap.count(&typeid(T));
		}

		template<typename T>
		static Actor* Create(Renderer* renderer,class Layer* layer, const Json::Value& value)
		{
			T* t = new T(renderer, layer);
			return t;
		}



		void SetActive(bool active) { m_bIsActive = active; }
		bool IsActive() const { return m_bIsActive; }


		std::vector<Actor*>& GetWorld();
		std::vector<Actor*>& GetPendingWorld();
		std::vector<Actor*>& GetMap();

	private:
		std::vector<class Component*> m_Components;
		std::map<const std::type_info*, class Component*> m_ComponentMap;
		Renderer* m_Renderer;
		bool m_bIsActive = true;
		class Layer* m_Layer;
	};
}
