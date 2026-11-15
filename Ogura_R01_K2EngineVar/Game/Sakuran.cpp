#include "stdafx.h"
#include "Sakuran.h"
#include "Noruto.h"
#include"socreUI.h"

Sakuran::Sakuran()
{
	// モデルの初期化
	m_modelRender.Init("Assets/modelData/enemy/sakuran.tkm");

	Sa_HP = 20;
	m_attacktimer = 0.0f;
	m_damageStopTime = 0.0f;

	float x = (float)(rand() % 446 - 223);
	m_pos = Vector3{ x, 20.0f, 180.0f };
	m_modelRender.SetPosition(m_pos);

	// 向きの調整
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

	// ダメージ硬直（無敵・停止）のタイマーを進める
	if (m_damageStopTime > 0.0f)
	{
		m_damageStopTime -= deltaTime;
	}
	else
	{
		// ヨモギーと同じように、硬直中でないときだけ Move() を呼ぶ！
		Move();
	}

	// プレイヤーとの接触判定
	Noruto* player = FindGO<Noruto>("Noruto");
	if (player != nullptr)
	{
		Vector3 playerPos = player->GetPosition();
		Vector3 diff = m_pos - playerPos;
		float distance = diff.Length();

		if (distance < 30.0f)
		{
			// 1. プレイヤーへのダメージは1秒に1回に制限する
			if (m_attacktimer <= 0.0f)
			{
				player->Damage(10);
				m_attacktimer = 1.0f;
			}

			// 2. サクラン自身の硬直（Damage関数内の m_damageStopTime で0.2秒制限されるのでいつでも呼んでOK）
			Damage(6);
		}
	}
	// 消滅条件（体力 < 1 または 画面下端 Z < -173 を超えたら削除）
	if (Sa_HP < 1 || m_pos.z < -173.0f)
	{
		socreUI* ui = FindGO<socreUI>("socreUI");
		if (ui != nullptr)
		{
			ui->AddScore(plasPoint); // 持ってる plasPoint (100点) を加算！
		}
		DeleteGO(this);
		return;
	}

	m_modelRender.Update();
}

void Sakuran::Move()
{
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	// サクランはZ軸マイナス方向（手前）へまっすぐ進む
	float fallSpeed = 80.0f;
	m_pos.z -= fallSpeed * deltaTime;

	m_modelRender.SetPosition(m_pos);

	// 向きの維持
	Quaternion rot;
	rot.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(rot);
}

void Sakuran::Damage(int pow)
{
	// 0.2秒の無敵・硬直時間中なら重複ダメージを受け付けない
	if (m_damageStopTime > 0.0f)
	{
		return;
	}

	// HPを減らす
	Sa_HP -= pow;

	// 0.2秒間、移動を止めて硬直させる
	m_damageStopTime = 0.2f;
}

void Sakuran::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}