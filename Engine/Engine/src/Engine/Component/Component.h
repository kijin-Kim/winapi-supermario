#pragma once
#include "../Actor/Actor.h"

namespace Engine {

	class Component
	{
	public:
		Component(Actor* owner) :
			m_Owner(owner) {}
		virtual ~Component() {}
		virtual void Update(float deltaTime) {}

		template<typename T>
		static Component* Create(Actor* owner, const Json::Value& value)
		{
			T* t = nullptr;
			if (!owner->HasComponent<T>())
			{
				t = new T(owner);
				owner->Attach(t);
			}
			else
			{
				t = owner->GetComponent<T>();
			}
			t->LoadFromJson(value);
			return t;
		}

		virtual void LoadFromJson(const Json::Value& value) = 0;

	protected:
		Actor* m_Owner;
	};
}
