#pragma once
// This Class is Temporary
// Should be written in Engine Side
#include <Engine.h>
#include <functional>

class DataLoader
{
public:
	static void LoadActors(Engine::Renderer* renderer, Engine::Layer* layer, const std::string& fileName);
	static void LoadTiles(Engine::Renderer* renderer, Engine::Layer* layer, const std::string& fileName);
	static bool IsCollidableTile(int tileId);

private:
	static std::unordered_map<std::string, std::function<Engine::Actor * (Engine::Renderer*, Engine::Layer*, const Json::Value&)>> s_ActorCreationMap;
	static std::unordered_map<std::string, std::function<Engine::Component * (Engine::Actor*, const Json::Value&)>> s_ComponentCreationMap;
	static bool bCheckIsCollidable[924];
	static bool bCheckHasHealth[924];
};
