#include "stdafx.h"
#include "PowerComponent.h"
#include "Core/Layer.h"
#include "Core/Application.h"
#include "Core/SoundEngine.h"

namespace Engine {

	void PowerComponent::Update(float deltaTime)
	{
		if (IsPowerEnabled(PowerType::Star))
		{
			m_StarTimer -= deltaTime;
			if (m_StarTimer <= 0.0f)
			{
				m_StarTimer = m_MaxStarTimer;
				DisablePower(PowerType::Star);
				m_Owner->GetLayer()->GetApplication()->GetSoundEngine()->Stop("Invincible_Theme");
				m_Owner->GetLayer()->GetApplication()->GetSoundEngine()->Play("Main_Theme");
			}
		}
	}

}

