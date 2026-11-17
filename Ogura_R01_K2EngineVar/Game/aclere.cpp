#include "stdafx.h"
#include "aclere.h"
#include "Stage1.h"
#include "title.h"
#include "EnemyManager.h"
#include "H_1Boss.h"
#include "H_1BossHPGage.h"
#include "PlayerHPGage.h"
#include "socreUI.h"
#include "gameover.h" // ★ gameover.h をインクルード！
#include"Game.h"
#include"Noruto.h"

aclere::aclere()
{
	m_spriteRender.Init("Assets/image/acleear.DDS", 1920.0f, 1080.0f);
	m_spriteRender.Update();
}

aclere::~aclere()
{
}

void aclere::Update()
{
	// ★ 【重要】万が一ゲームオーバー画面が出ていたら、クリア画面は即座に消滅して何もさせない！
	if (FindGO<gameover>("gameover") != nullptr)
	{
		DeleteGO(this);
		return;
	}

	float deltaTime = g_gameTime->GetFrameDeltaTime();
	m_clearTimer += deltaTime;

	// ★ 3秒経ったらタイトルに戻る
	if (m_clearTimer >= 3.0f)
	{
		

		// タイトル画面を生成して、自分自身を消す
		NewGO<title>(0, "title");
		NewGO<Game>(0, "Game");

		DeleteGO(this);
	}
}

void aclere::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}