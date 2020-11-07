#include "stdafx.h"
#include "Layer.h"
#include "Actor/Actor.h"

namespace Engine {


	Layer::~Layer()
	{
		while (!GetWorld().empty())
		{
			delete GetWorld().back();
			GetWorld().pop_back();
		}
	}

	std::vector<Actor*>& Layer::GetWorld()
	{
		return m_World;
	}

	std::vector<class Actor*>& Layer::GetPendingWorld()
	{
		return m_PendingWorld;
	}

	std::vector<Actor*>& Layer::GetMap()
	{
		return m_Map;
	}

}