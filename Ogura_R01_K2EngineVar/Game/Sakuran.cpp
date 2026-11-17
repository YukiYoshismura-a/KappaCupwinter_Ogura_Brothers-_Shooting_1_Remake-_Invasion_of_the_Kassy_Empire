#include "stdafx.h"
#include "Sakuran.h"
#include "Noruto.h"
#include "socreUI.h"
#include "Norutodan.h"
#include "gameover.h" // ★ ゲームオーバー検知用を追加！

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

void Sakuran::Init(float minX, float maxX)
{
	// minX 〜 maxX の間でランダムなX座標を計算する（★ マイナスを正しく修正！）
	float range = maxX - minX;
	float x = minX + (float)(rand() % (int)(range + 1));

	m_pos = Vector3{ x, 20.0f, 180.0f }; // 一番上の奥のライン
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();
}

void Sakuran::Update()
{
	// ★ ゲームオーバー画面がすでに生成されていたら、自分を消して処理を抜ける
	if (FindGO<gameover>("gameover") != nullptr)
	{
		DeleteGO(this);
		return;
	}

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
		// 硬直中でないときだけ Move() を呼ぶ！
		Move();
	}

	// プレイヤーとの接触判定
	Noruto* player = FindGO<Noruto>("Noruto"); // ★ 型名と変数名を正しく分離
	if (player != nullptr)
	{
		Vector3 playerPos = player->GetPosition();
		Vector3 diff = m_pos - playerPos;
		float distance = diff.Length();

		if (distance < 30.0f)
		{
			if (m_attacktimer <= 0.0f)
			{
				player->Damage(10);
				m_attacktimer = 1.0f;
			}
			Damage(6);
		}
	}

	// 消滅条件（体力 < 1 または 画面下端 Z < -173 を超えたら削除）
	if (Sa_HP < 1 || m_pos.z < -173.0f)
	{
		socreUI* ui = FindGO<socreUI>("socreUI"); // ★ 型名と変数名を正しく分離
		if (ui != nullptr)
		{
			ui->AddScore(plasPoint); // スコアを加算！
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