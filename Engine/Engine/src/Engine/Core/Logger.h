#pragma once
#include <string>

namespace Engine {

	class Logger
	{
	public:
		static void Log(const std::string& message)
		{
			OutputDebugStringA(("Log : " + message + "\n").c_str());
		}
	};

}

#define LOG(x) Engine::Logger::Log(x)