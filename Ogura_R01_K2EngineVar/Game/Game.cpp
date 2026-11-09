#include "stdafx.h"
#include "Game.h"
#include "PlayerSerct.h"

Game::Game()
{
	play.Init("Assets/image/Play.DDS", 320.0f, 180.0f);
	info.Init("Assets/image/info.dds", 320.0f, 180.0f);

	play.SetPosition(Vector3(700.0f, 300.0f, 0.0f));
	info.SetPosition(Vector3(700.0f, -300.0f, 0.0f));


	play.SetScale(Vector3(2.0f, 2.0f, 1.0f));


	play.Update();
	info.Update();
}

Game::~Game()
{
	NewGO<PlayerSerct>(0, "PlayerSelect");
}

void Game::Update()
{
	// g_renderingEngine->DisableRaytracing();
	if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->GetLStickYF() > 0.01f)
	{
		select = 0;
	}
	else if (g_pad[0]->IsTrigger(enButtonDown) || g_pad[0]->GetLStickYF() < -0.01f)
	{
		select = 1;
	}

	if (select == 0)
	{
		play.SetScale(Vector3(2.0f, 2.0f, 1.0f));
		play.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	
		info.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		info.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));
		info.SetPosition(Vector3(550.0f, -300.0f, 0.0f));
	
		//ここでA押されたら、Player選ぶ画面に飛ぶ
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			DeleteGO(this);
			return;
		}
	}
	else if (select == 1)
	{
		info.SetScale(Vector3(2.0f, 2.0f, 1.0f));
		info.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		info.SetPosition(Vector3(550.0f, -300.0f, 0.0f));

		play.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		play.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));
	
		
	}
	play.Update();
	info.Update();
}

void Game::Render(RenderContext& rc)
{
	play.Draw(rc);
	info.Draw(rc);
}