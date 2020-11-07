#pragma once
#include "fmod_lowlevel/inc/fmod.hpp"
#include <map>
#include <string>

namespace Engine {

	class SoundEngine
	{
	public:
		SoundEngine();
		~SoundEngine();

		void CreateSound(const std::string& fileName, const std::string& soundName, const bool& bLoop);

		void Play(const std::string& soundName);
		void Stop(const std::string& soundName);


	private:
		FMOD::System* m_System = nullptr;
		std::map<std::string, FMOD::Sound*> m_SoundMap;
		std::map<FMOD::Sound*, FMOD::Channel*> m_ChannelMap;
		void* m_extraDriverData = nullptr;
		static bool s_bIsInstantiated;
	};
}
