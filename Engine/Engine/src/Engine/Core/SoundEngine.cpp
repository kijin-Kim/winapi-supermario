#include "stdafx.h"
#include "SoundEngine.h"

namespace Engine {

	bool SoundEngine::s_bIsInstantiated = false;

	SoundEngine::SoundEngine()
	{
		ASSERT(!s_bIsInstantiated, "Is Already Initialized");

		auto result = FMOD::System_Create(&m_System);
		if (result != FMOD_OK)
			ASSERT(false, "failed to create system");

		result = m_System->init(32, FMOD_INIT_NORMAL, m_extraDriverData);
		if(result != FMOD_OK)
			ASSERT(false, "failed to Initialize system");

		s_bIsInstantiated = true;
	}

	SoundEngine::~SoundEngine()
	{
		m_System->release();
		s_bIsInstantiated = false;
	}

	void SoundEngine::CreateSound(const std::string& fileName, const std::string& soundName, const bool& bLoop)
	{
		int loopFlag;
		if (bLoop)
			loopFlag = FMOD_LOOP_NORMAL;
		else
			loopFlag = FMOD_LOOP_OFF;

		m_SoundMap[soundName] = nullptr;
		auto& sound = m_SoundMap[soundName];
		auto result = m_System->createSound(fileName.c_str(), loopFlag, 0, &sound);

		if (result != FMOD_OK)
			ASSERT(false, "Cannot Load Sound");

	};


	void SoundEngine::Play(const std::string& soundName)
	{
		if (m_SoundMap.count(soundName) <= 0)
			ASSERT(false, "Sound isn't Initialized");

		auto& sound = m_SoundMap[soundName];
		auto& channel = m_ChannelMap[sound];

		bool bIsPlaying = false;
		auto result = channel->isPlaying(&bIsPlaying);
		float volume;

		if (bIsPlaying) 
			return;

		result = m_System->playSound(sound, 0, false, &channel);
		if (result != FMOD_OK)
			ASSERT(false, "Cannot play sound");

	}

	void SoundEngine::Stop(const std::string& soundName)
	{
		if (m_SoundMap.count(soundName) <= 0)
			ASSERT(false, "Sound isn't Initialized");

		auto& sound = m_SoundMap[soundName];
		auto& channel = m_ChannelMap[sound];

		bool bIsPlaying = false;
		auto result = channel->isPlaying(&bIsPlaying);

		if (!bIsPlaying)
			return;

		result = channel->stop();
		if (result != FMOD_OK)
			ASSERT(false, "Cannot stop sound");
	}

}