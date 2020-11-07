#include <Engine.h>
#include "Engine/Core/Entry.h"
#include "../actor/Mario.h"
#include "../actor/Tile.h"
#include "../actor/BackGround.h"
#include "../actor/Enemy.h"
#include "../actor/ImageActor.h"
#include "../actor/DefaultCamera.h"
#include "DataLoader.h"

class GameLayer :public Engine::Layer
{
public:
	GameLayer(Engine::Application* application, int width, int height) :
		Layer(application, width, height)
	{
		DataLoader::LoadActors(m_Renderer, this, "data/data.json");
		mario = GetWorld()[0];
		DataLoader::LoadTiles(m_Renderer, this, "data/tile_map.txt");
		GetMap().push_back(new BackGround(m_Renderer, this));
	}

	virtual ~GameLayer()
	{
	}
	
	virtual void Enter() override final
	{
		GetApplication()->GetSoundEngine()->Play("Main_Theme");
	}

	virtual void Exit() override final
	{
		GetApplication()->GetSoundEngine()->Stop("Main_Theme");
	}

	virtual void Update(float deltaTime) override final
	{
		
		// Temporary Should Make Scene
		for (auto a : GetWorld())
		{
			a->Update(deltaTime);
		}
		for (auto a : GetMap())
		{
			
			a->Update(deltaTime);
		}
		

		// Actor vs Tile
		for (auto a : GetWorld())
		{
			auto collider = a->GetComponent<Engine::ColliderComponent>();
			for (auto b : GetMap())
			{
				if (b->HasComponent<Engine::ColliderComponent>())
					collider->CheckCollisionAndResponse(b);
			}
		}
		
		// Actor vs Actor
		for (auto a : GetWorld())
		{
			auto collider = a->GetComponent<Engine::ColliderComponent>();
			for (auto b : GetWorld())
			{
				if (a != b)
				{
					if (b->HasComponent<Engine::ColliderComponent>())
						collider->CheckCollisionAndResponse(b);
				}
			}
		}
		
		
		for (auto it = GetWorld().begin(); it != GetWorld().end();)
		{
			if (!(*it)->IsActive())
			{
				if ((*it) == mario)
				{
					mario = nullptr;
				}
				delete (*it);
				(*it) == nullptr;
				it = GetWorld().erase(it);
			}
			else
				it++;
		}

		for (auto it = GetMap().begin(); it != GetMap().end();)
		{
			if (!(*it)->IsActive())
			{
				delete (*it);
				(*it) == nullptr;
				it = GetMap().erase(it);
			}
			else
				it++;
		}

		GetWorld().insert(GetWorld().end(), GetPendingWorld().begin(), GetPendingWorld().end());
		GetPendingWorld().clear();
		
		if (mario)
			m_Renderer->Draw(mario->GetComponent<Engine::PlayerCameraComponent>());
		else
		{
			GetApplication()->Gameover();
		}
	}
private:
	Engine::Actor* mario = nullptr;
};

class TitleLayer : public Engine::Layer
{
public:
	TitleLayer(Engine::Application* application, int width, int height) :
		Layer(application, width, height)
	{
	}
	virtual ~TitleLayer()
	{
	}

	virtual void Enter() override final	
	{
		auto image = new ImageActor(m_Renderer, this);
		auto t = image->GetComponent<Engine::TextureComponent>();
		t->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/Title")));
		GetWorld().push_back(image);

		m_Camera = new DefaultCamera(m_Renderer, this);
	}

	virtual void Exit() override final
	{
	}

	virtual void Update(float deltaTime) override final
	{
		m_Renderer->Draw(m_Camera->GetComponent<Engine::PlayerCameraComponent>());
	}

private:
	DefaultCamera* m_Camera;
};

class GameOverLayer : public Engine::Layer
{
public:
	GameOverLayer(Engine::Application* application, int width, int height) :
		Layer(application, width, height)
	{

	}
	virtual ~GameOverLayer()
	{
	}

	virtual void Enter() override final
	{
		auto image = new ImageActor(m_Renderer, this);
		auto t = image->GetComponent<Engine::TextureComponent>();
		t->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/Gameover")));
		GetWorld().push_back(image);

		m_Camera = new DefaultCamera(m_Renderer, this);

		GetApplication()->GetSoundEngine()->Play("Death");
	}

	virtual void Exit() override final
	{
		GetApplication()->GetSoundEngine()->Stop("Death");

	}

	virtual void Update(float deltaTime) override final
	{
		m_Renderer->Draw(m_Camera->GetComponent<Engine::PlayerCameraComponent>());
	}

private:
	DefaultCamera* m_Camera;
};

class GameClearLayer : public Engine::Layer
{
public:
	GameClearLayer(Engine::Application* application, int width, int height) :
		Layer(application, width, height)
	{

	}
	virtual ~GameClearLayer()
	{
	}

	virtual void Enter() override final
	{
		auto image = new ImageActor(m_Renderer, this);
		auto t = image->GetComponent<Engine::TextureComponent>();
		t->SetTexture(Engine::Texture(Engine::BitmapMananger::GetImage("assets/textures/GameClear")));
		GetWorld().push_back(image);

		m_Camera = new DefaultCamera(m_Renderer, this);
		GetApplication()->GetSoundEngine()->Play("GameClear");

	}

	virtual void Exit() override final
	{
		GetApplication()->GetSoundEngine()->Stop("GameClear");

	}

	virtual void Update(float deltaTime) override final
	{
		m_Renderer->Draw(m_Camera->GetComponent<Engine::PlayerCameraComponent>());
	}

private:
	DefaultCamera* m_Camera;
};


enum class GameState
{
	State_Game, State_Title, State_Gameover, State_GameClear
};

class GameApp : public Engine::Application
{
public:
	GameApp() : Application("Hello Engine", 320, 224)
	{
		m_GameLayer = new GameLayer(this, 320, 224);
		m_TitleLayer = new TitleLayer(this, 320, 224);
		m_GameoverLayer = new GameOverLayer(this, 320, 224);
		m_GameClearLayer = new GameClearLayer(this, 320, 224);

		GetSoundEngine()->CreateSound("assets/sounds/main_theme.ogg", "Main_Theme", true);
		GetSoundEngine()->CreateSound("assets/sounds/invincible.ogg", "Invincible_Theme", true);

		GetSoundEngine()->CreateSound("assets/sounds/small_jump.ogg", "Jump", false);
		GetSoundEngine()->CreateSound("assets/sounds/stomp.ogg", "Stomp", false);
		GetSoundEngine()->CreateSound("assets/sounds/kick.ogg", "Kick", false);
		GetSoundEngine()->CreateSound("assets/sounds/coin.ogg", "Coin", false);
		GetSoundEngine()->CreateSound("assets/sounds/fireball.ogg", "FireBall", false);
		GetSoundEngine()->CreateSound("assets/sounds/powerup.ogg", "PowerUp", false);
		GetSoundEngine()->CreateSound("assets/sounds/brick_smash.ogg", "Smash", false);
		GetSoundEngine()->CreateSound("assets/sounds/world_clear.wav", "GameClear", false);
		GetSoundEngine()->CreateSound("assets/sounds/death.wav", "Death", false);


		
		PushLayer(m_TitleLayer);
	}

	virtual ~GameApp()
	{
	}

	virtual void UpdateApplication(float deltaTime) override final
	{
		if (Engine::Input::IsKeyPressed(VK_LBUTTON))
		{
			if (m_State == GameState::State_Title)
			{
				PopLayer(m_TitleLayer);
				PushLayer(m_GameLayer);
				m_State = GameState::State_Game;
			}
			else if (m_State == GameState::State_Gameover || m_State== GameState::State_GameClear)
			{
				QuitApplication();
			}
		}
	}

	virtual void Gameover() override
	{
		PopLayer(m_GameLayer);
		m_State = GameState::State_Gameover;
		PushLayer(m_GameoverLayer);
	}

	virtual void GameClear() override
	{
		PopLayer(m_GameLayer);
		m_State = GameState::State_GameClear;
		PushLayer(m_GameClearLayer);
	}

private:
	GameState m_State = GameState::State_Title;
	GameLayer* m_GameLayer;
	TitleLayer* m_TitleLayer;
	GameOverLayer* m_GameoverLayer;
	GameClearLayer* m_GameClearLayer;
};


RegisterApplication(GameApp)