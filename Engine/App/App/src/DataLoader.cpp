#include "DataLoader.h"
#include <fstream>
#include <filesystem>
#include "JsonCpp/json/json.h"

#include "../actor/Mario.h"
#include "../actor/Tile.h"
#include "../actor/Enemy.h"




//TODO : Some Function to Register custom actor, component to engine side

std::unordered_map<std::string, std::function<Engine::Actor * (Engine::Renderer*,Engine::Layer*, const Json::Value&)>> DataLoader::s_ActorCreationMap
{
	{"Mario", &Engine::Actor::Create<Mario>},
	{"Tile", &Engine::Actor::Create<Tile>},
	{"Enemy", &Engine::Actor::Create<Enemy>},
};

std::unordered_map<std::string, std::function<Engine::Component* (Engine::Actor*, const Json::Value&)>> DataLoader::s_ComponentCreationMap
{
	{"TransformComponent",&Engine::Component::Create<Engine::TransformComponent>},
	{"TextureComponent",&Engine::Component::Create<Engine::TextureComponent>},
	{"AnimatedTextureComponent",&Engine::Component::Create<Engine::AnimatedTextureComponent>},
	{"ColliderComponent",& Engine::Component::Create<Engine::ColliderComponent>},
	{"PlayerCameraComponent",&Engine::Component::Create<Engine::PlayerCameraComponent>},
	{"HealthComponent",&Engine::Component::Create<Engine::HealthComponent>},
	{"PowerComponent",& Engine::Component::Create<Engine::PowerComponent>}
};


bool DataLoader::bCheckIsCollidable[924];
bool DataLoader::bCheckHasHealth[924];


void DataLoader::LoadActors(Engine::Renderer* renderer, Engine::Layer* layer, const std::string& fileName)
{
	std::ifstream jsonFile(fileName);
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::Value value;

	JSONCPP_STRING errs;
	bool bIsOk = parseFromStream(builder, jsonFile, &value, &errs);

	if (bIsOk)
	{
		for (int i = 0; i < value["Actors"].size(); i++)
		{
			std::string actorType = value["Actors"][i]["ActorType"].asString();
			auto* actor = s_ActorCreationMap[actorType](renderer, layer, value);
			layer->GetWorld().push_back(actor);

			for (int j = 0; j < value["Actors"][i]["Components"].size(); j++)
			{
				std::string componentType = value["Actors"][i]["Components"][j]["ComponentType"].asString();
				s_ComponentCreationMap[componentType](actor, value["Actors"][i]["Components"][j]["ComponentProperties"]);
			}
		}
	}
}

void DataLoader::LoadTiles(Engine::Renderer* renderer, Engine::Layer* layer, const std::string& fileName)
{
	//temp
	for (int i = 0; i < 7 * 33; i++)
	{
		bCheckIsCollidable[i] = true;
	}

	bCheckIsCollidable[8 * 33] = true;
	bCheckIsCollidable[8 * 33 + 1] = true;

	bCheckIsCollidable[9 * 33] = true;
	bCheckIsCollidable[9 * 33 + 1] = true;
	bCheckIsCollidable[313] = true;


	for (int i = 0; i < 7 * 33; i++)
	{
		if(!(i%33 == 3 && (i/33)%2 == 0))
			bCheckHasHealth[i] = true;
	}


	//------------------------------------------
	std::ifstream textFile(fileName);

	std::vector<int> tileId;
	while (!textFile.eof())
	{
		int a;
		textFile >> a;
		tileId.push_back(a);
	}
	

	for (int i = 0; i < 224/16; i++)
	{
		for (int j = 0; j < 3392/16; j++)
		{
			int id = tileId[i * 3392 / 16 + j];
			if (id != -1)
			{
				bool bIsCollidable = false;
				Tile* t = nullptr;
				if (id != 24)
					t = new Tile(renderer, layer);
				else
				{
					t = new RandomTile(renderer, layer);
				}

				auto transform = t->GetComponent<Engine::TransformComponent>();
				auto texture = t->GetComponent<Engine::TextureComponent>();

				if (bCheckIsCollidable[id])
				{
					

					auto collider = new Engine::ColliderComponent(t);
					if (id != 313)
						collider->SetColliderTag("Tile");
					else
						collider->SetColliderTag("Clear");
					collider->SetColliderSize({ 16,16 });
					collider->SetGravitydisabled();
					t->Attach(collider);
				}

				if (bCheckHasHealth[id])
				{
					auto health = new Engine::HealthComponent(t);
					health->SetHealth(2);
					t->Attach(health);
				}

				transform->SetPosition({ (float)8 + 16 * j, (float)224 - (8 + 16 * i)});
				texture->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/tile_set"),
					{ 0 + (16 * (id % 33)), 0 + (16 * (id / 33)),
					16 + (16 * (id % 33)),16 + (16 * (id / 33)) }));

				layer->GetMap().push_back(t);
			}
		}
		
	}
}

bool DataLoader::IsCollidableTile(int tileId)
{
	return bCheckIsCollidable[tileId];
}
