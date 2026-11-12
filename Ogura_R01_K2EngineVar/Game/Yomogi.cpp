#include "stdafx.h"
#include "Yomogi.h"
#include "Noruto.h"

Yomogi::Yomogi()
{
	m_modelRender.Init("Assets/modelData/enemy/yomogiy.tkm");

	Y_HP = 20;

	float x = (float)(rand() % 446 - 223);
	m_pos = Vector3{ x, 20.0f, 180.0f };
	m_modelRender.SetPosition(m_pos);

	m_modelRender.Update();
}

Yomogi::~Yomogi()
{
}

void Yomogi::Update()
{
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

	Noruto* player = FindGO<Noruto>("Noruto");
	if (player != nullptr)
	{
		Vector3 playerPos = player->GetPosition();
		Vector3 diff = m_pos - playerPos;
		float distance = diff.Length();

		if (distance < 30.0f && m_attacktimer <= 0.0f)
		{
			player->Damage(10); // プレイヤーにダメージ
			Damage(6);          // ヨモギー自身もダメージ＆硬直
			m_attacktimer = 1.0f;
		}
	}

	// 消滅用
	if (Y_HP < 1)
	{
		DeleteGO(this);
		return;
	}
	m_modelRender.Update();
}

void Yomogi::Move()
{
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	Noruto* player = FindGO<Noruto>("Noruto");
	if (player != nullptr)
	{
		Vector3 playerPos = player->GetPosition();

		Vector3 dir = playerPos - m_pos;
		dir.Normalize();

		float speed = 30.0f * 3.0f;
		m_pos += dir * speed * deltaTime;
	}

	// 1. Y軸の向きは固定（Z+方向なら 0.0f。もし別方向を向かせたいなら角度を調整してな！）
	Quaternion rotY;
	rotY.SetRotationY(0.0f); // 0.0f でZ+方向を向く

	// 2. 上を向かせるためのX軸の回転
	Quaternion rotX;
	rotX.SetRotationX(-1.5f); // 上向きの角度

	// 3. 合成してセット
	Quaternion rot = rotY * rotX;
	m_modelRender.SetRotation(rot);

	// 描画位置のY座標を少し浮かせて埋まりを防ぐ
	Vector3 drawPos = m_pos;
	drawPos.y += 20.0f;
	m_modelRender.SetPosition(drawPos);
}

void Yomogi::Damage(int pow)
{
	Y_HP -= pow;
	m_damageStopTime = 0.2f;
}

void Yomogi::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}