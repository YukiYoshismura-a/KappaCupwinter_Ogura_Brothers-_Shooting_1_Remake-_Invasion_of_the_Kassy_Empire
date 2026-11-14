#include "stdafx.h"
#include "Sakuran.h"
#include "Noruto.h"

Sakuran::Sakuran()
{
	// ★ 1. まず最初にモデルを初期化する！
	m_modelRender.Init("Assets/modelData/enemy/sakuran.tkm");

	Sa_HP = 20;

	float x = (float)(rand() % 446 - 223);
	m_pos = Vector3{ x, 20.0f, 180.0f };
	m_modelRender.SetPosition(m_pos);

	// 向きの調整（必要に応じて回転）
	Quaternion rot;
	rot.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(rot);

	m_modelRender.Update();
}

Sakuran::~Sakuran()
{
}

void Sakuran::Update()
{
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	// 攻撃クールダウンのタイマーを進める
	if (m_attacktimer > 0.0f)
	{
		m_attacktimer -= deltaTime;
	}

	// 1. ダメージクールダウン（硬直時間）のタイマーを進める
	if (m_damageStopTime > 0.0f)
	{
		m_damageStopTime -= deltaTime;
	}
	else
	{
		// ★ 硬直中でないときだけ、下にスクロール（移動）する！
		float fallSpeed = 150.0f;
		m_pos.z -= fallSpeed * deltaTime;
	}

	m_modelRender.SetPosition(m_pos);

	// レイヤーとの接触判定（ポインタを正しく分離！）
	Noruto* player = FindGO<Noruto>("Noruto");
	if (player != nullptr)
	{
		Vector3 playerPos = player->GetPosition();
		Vector3 diff = m_pos - playerPos;
		float distance = diff.Length();

		// 距離が近くて、かつ攻撃クールダウンが終わっていればダメージを与える
		if (distance < 30.0f && m_attacktimer <= 0.0f)
		{
			player->Damage(10); 
			Damage(6);// プレイヤーにダメージ
			m_attacktimer = 1.0f;   // 1秒間は連続でダメージを受けないようにする
		}
	}

	// 消滅条件（体力 < 1 または 画面下端 Z < -173 を超えたら削除）
	if (Sa_HP < 1 || m_pos.z < -173.0f)
	{
		DeleteGO(this);
		return;
	}

	m_modelRender.Update();
}

void Sakuran::Damage(int pow)
{
	// 0.2秒の無敵時間中ならダメージを受け付けない
	if (m_damageStopTime > 0.0f)
	{
		return;
	}

	Sa_HP -= pow;
	m_damageStopTime = 0.2f; // 0.2秒間、移動を止めて硬直させる！
}

void Sakuran::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}