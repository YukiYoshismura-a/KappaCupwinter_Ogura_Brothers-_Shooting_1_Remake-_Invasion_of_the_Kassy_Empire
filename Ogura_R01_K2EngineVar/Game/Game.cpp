#include "stdafx.h"
#include "Game.h"
#include "PlayerSerct.h"
#include "sound/SoundEngine.h" // ★ サウンドエンジン用

Game::Game()
{
	play.Init("Assets/image/Play.DDS", 320.0f, 180.0f);
	info.Init("Assets/image/info.dds", 320.0f, 180.0f);

	play.SetPosition(Vector3(700.0f, 300.0f, 0.0f));
	info.SetPosition(Vector3(700.0f, -300.0f, 0.0f));


	play.SetScale(Vector3(2.0f, 2.0f, 1.0f));


	play.Update();
	info.Update();

	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/SE/koreka.wav");
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/SE/DEN.wav");
}

Game::~Game()
{
	//NewGO<PlayerSerct>(0, "PlayerSelect");
}

void Game::Update()
{
	int prevSelect = select;
	// g_renderingEngine->DisableRaytracing();
	if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->GetLStickYF() > 0.01f)
	{
		select = 0;
	}
	else if (g_pad[0]->IsTrigger(enButtonDown) || g_pad[0]->GetLStickYF() < -0.01f)
	{
		select = 1;
	}
	if (select != prevSelect)
	{
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1); // バンクID 1 に登録した "koreka.wav" を初期化
		se->Play(false); // ループなしで1回だけ再生
	}
	if (select == 0)
	{
		play.SetScale(Vector3(2.0f, 2.0f, 1.0f));
		play.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	
		info.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		info.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));
		info.SetPosition(Vector3(550.0f, -300.0f, 0.0f));
	
		
	}
	else
	{
		info.SetScale(Vector3(2.0f, 2.0f, 1.0f));
		info.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		info.SetPosition(Vector3(550.0f, -300.0f, 0.0f));

		play.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		play.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));
	
		
	}
	play.Update();
	info.Update();

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (select == 0)
		{
			NewGO<PlayerSerct>(0, "playerselect");
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(2); 
			se->Play(false);
			DeleteGO(this);
			return;
		}
		else
		{
			
		}
	}
}

void Game::Render(RenderContext& rc)
{
	play.Draw(rc);
	info.Draw(rc);
}