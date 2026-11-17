#include "stdafx.h"
#include "Yomogi.h"
#include "Noruto.h"
#include "socreUI.h"
#include "Norutodan.h"
#include "gameover.h" // ★ ゲームオーバー検知用に追加！

Yomogi::Yomogi()
{
	m_modelRender.Init("Assets/modelData/enemy/yomogiy.tkm");
	Y_HP = 20;
	m_modelRender.Update();
}

Yomogi::~Yomogi()
{
}

void Yomogi::Init(float minX, float maxX)
{
	// minX 〜 maxX の間でランダムなX座標を計算する（★ マイナスを正しく修正！）
	float range = maxX - minX;
	float x = minX + (float)(rand() % (int)(range + 1));

	m_pos = Vector3{ x, 20.0f, 180.0f };
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();
}

void Yomogi::Update()
{
	// ★ ゲームオーバー画面がすでに生成されていたら、自分を消して処理を抜ける
	if (FindGO<gameover>("gameover") != nullptr)
	{
		DeleteGO(this);
		return;
	}

	float deltaTime = g_gameTime->GetFrameDeltaTime();
	if (m_attacktimer > 0.0f)
	{
		m_attacktimer -= deltaTime;
	}
	if (m_damageStopTime > 0.0f)
	{
		m_damageStopTime -= deltaTime;
	}
	else
	{
		Move();
	}

	// 1. プレイヤーとの距離判定
	Noruto* player = FindGO<Noruto>("Noruto"); // ★ 型名と変数名を正しく分離
	if (player != nullptr)
	{
		Vector3 playerPos = player->GetPosition();
		Vector3 diff = m_pos - playerPos;
		float distance = diff.Length();

		if (distance < 30.0f && m_attacktimer <= 0.0f)
		{
			player->Damage(10);
			Damage(6);
			m_attacktimer = 1.0f;
		}
	}

	// 消滅用
	if (Y_HP < 1)
	{
		socreUI* ui = FindGO<socreUI>("socreUI"); // ★ 型名と変数名を正しく分離
		if (ui != nullptr)
		{
			ui->AddScore(plasPoint);
		}
		DeleteGO(this);
		return;
	}
	m_modelRender.Update();
}

void Yomogi::Move()
{
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	Noruto* player = FindGO<Noruto>("Noruto"); // ★ 型名と変数名を正しく分離
	if (player != nullptr)
	{
		Vector3 playerPos = player->GetPosition();

		Vector3 dir = playerPos - m_pos;
		dir.Normalize();

		float speed = 30.0f * 3.0f;
		m_pos += dir * speed * deltaTime;
	}

	Quaternion rotY;
	rotY.SetRotationY(0.0f);

	Quaternion rotX;
	rotX.SetRotationX(-1.5f);

	Quaternion rot = rotY * rotX;
	m_modelRender.SetRotation(rot);

	Vector3 drawPos = m_pos;
	drawPos.y += 20.0f;
	m_modelRender.SetPosition(drawPos);
}

void Yomogi::Damage(int pow)
{
	if (m_damageStopTime > 0.0f)
	{
		return;
	}

	Y_HP -= pow;
	m_damageStopTime = 0.2f;
}

void Yomogi::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}