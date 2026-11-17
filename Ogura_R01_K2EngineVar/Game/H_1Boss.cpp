#include "stdafx.h"
#include "H_1Boss.h"
#include "Noruto.h"
#include "Norutodan.h"
#include "socreUI.h"

H_1Boss::H_1Boss()
{
	// モデルの初期化
	m_modelRender.Init("Assets/modelData/enemy/yomogiy.tkm");

	m_bossHp = 1000;
	m_isDead = false;
	m_attackTimer = 0.0f;
	m_damageStopTime = 0.0f;

	// ① 初期位置（Scratchのy=219 を z=219 に対応させる）
	m_pos = Vector3{ 0.0f, 20.0f, 219.0f };
	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetScale(4.0f, 4.0f, 4.0f);
	Quaternion rotY;
	rotY.SetRotationDegY(180.0f);
	Quaternion rot = rotY;
	m_modelRender.SetRotation(rot);

	m_modelRender.Update();

	m_bossState = 0;      // 0: 登場移動中, 1: 戦闘中, 2: 撃破演出中
	m_moveTimer = 0.0f;

	// アクションステップの初期化
	// 0: 登場後の5秒待つ, 1: プレイヤーへ向ける, 2: 突っ込む(50回), 3: 170へ戻る, 4: 戻った後の5秒待つ
	m_bossActionStep = 0;
	m_actionTimer = 0.0f;
	m_repeatCount = 0;
	m_moveDir = Vector3::Zero;
}

H_1Boss::~H_1Boss()
{
}

void H_1Boss::Init(float minX, float maxX)
{
	m_pos = Vector3{ 0.0f, 20.0f, 219.0f };
	m_modelRender.SetPosition(m_pos);

	Quaternion rotY;
	rotY.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(rotY);

	m_modelRender.Update();

	m_bossState = 0;
	m_moveTimer = 0.0f;
	m_bossActionStep = 0;
	m_actionTimer = 0.0f;
	m_repeatCount = 0;
	m_moveDir = Vector3::Zero;
}

void H_1Boss::Update()
{
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	// 1. 被弾硬直・攻撃タイマーを進める
	if (m_damageStopTime > 0.0f)
	{
		m_damageStopTime -= deltaTime;
	}

	if (m_attackTimer > 0.0f)
	{
		m_attackTimer -= deltaTime;
	}

	// ==========================================
	// ステート 0: 登場時の移動（1秒かけて z: 219 → 119 へ移動）
	// ==========================================
	if (m_bossState == 0)
	{
		m_moveTimer += deltaTime;
		float t = m_moveTimer / 1.0f;
		if (t > 1.0f) t = 1.0f;

		float targetZ = 119.0f;
		m_pos.z = 219.0f + (targetZ - 219.0f) * t;
		m_modelRender.SetPosition(m_pos);
		m_modelRender.Update();

		if (m_moveTimer >= 1.0f)
		{
			m_bossState = 1;      // 戦闘開始！
			m_bossActionStep = 0; // 戦闘開始直後の「5秒待つ」へ
			m_actionTimer = 0.0f;
		}
		return;
	}

	// ==========================================
	// ステート 2: 撃破演出中（z座標を奥へスライドして消滅）
	// ==========================================
	if (m_bossState == 2)
	{
		// z座標をプラス方向にスライド
		m_pos.z += 5.0f * (deltaTime * 60.0f);
		m_modelRender.SetPosition(m_pos);
		m_modelRender.Update();

		// z座標が 218 を超えたら完全に消去
		if (m_pos.z > 218.0f)
		{
			DeleteGO(this);
		}
		return;
	}

	// ==========================================
	// ステート 1: 通常戦闘中
	// ==========================================

	// 2. プレイヤー（Noruto）との接触判定（ボス戦全般：3秒ごとにダメージ）
	Noruto* player = FindGO<Noruto>("Noruto");
	if (player != nullptr && !m_isDead)
	{
		Vector3 playerPos = player->GetPosition();
		Vector3 diff = m_pos - playerPos;
		float distance = diff.Length();

		// ボスに触れたらプレイヤーにダメージ（3.0秒ごと）
		if (distance < 50.0f && m_attackTimer <= 0.0f)
		{
			player->Damage(10);   // プレイヤーにダメージ
			m_attackTimer = 3.0f; // 次のダメージまで 3.0秒待つ
		}
	}

	// 3. 戦闘中の完全行動ループ（5秒待つ → プレイヤーに向ける → 突っ込む → 170へ戻る → 5秒待つ）
	if (player != nullptr)
	{
		switch (m_bossActionStep)
		{
		case 0: // ① 登場後の「5秒待つ」
			m_actionTimer += deltaTime;
			if (m_actionTimer >= 5.0f)
			{
				m_actionTimer = 0.0f;
				m_bossActionStep = 1; // 次：プレイヤーに向ける
			}
			break;

		case 1: // ② プレイヤーへ向ける（方向をロックする）
		{
			Vector3 playerPos = player->GetPosition();
			m_moveDir = playerPos - m_pos;
			m_moveDir.y = 0.0f;
			m_moveDir.Normalize();

			m_repeatCount = 0; // カウンターリセット
			m_bossActionStep = 2; // すぐに突っ込むへ！
			break;
		}

		case 2: // ③ 突っ込む（50回繰り返す {6歩進む}）
		{
			float stepSpeed = 100.0f; // スピード調整
			m_pos += m_moveDir * stepSpeed * deltaTime;

			m_repeatCount++;
			if (m_repeatCount >= 200) // 規定回数繰り返したら終了
			{
				m_repeatCount = 0;
				m_bossActionStep = 3; // ④ 170へ戻るフェーズへ
			}
			break;
		}

		case 3: // ④ z = 170 へ戻る
		{
			float targetZ = 170.0f;
			float returnSpeed = 110.0f; // 戻るときのスピード

			// Z座標を一定スピードでターゲット（170）に向かって動かす
			if (m_pos.z < targetZ)
			{
				m_pos.z += returnSpeed * deltaTime;
				if (m_pos.z > targetZ) m_pos.z = targetZ;
			}
			else if (m_pos.z > targetZ)
			{
				m_pos.z -= returnSpeed * deltaTime;
				if (m_pos.z < targetZ) m_pos.z = targetZ;
			}

			// X座標も中央（0.0f）に向かって一定スピードで戻す
			if (m_pos.x < 0.0f)
			{
				m_pos.x += returnSpeed * deltaTime;
				if (m_pos.x > 0.0f) m_pos.x = 0.0f;
			}
			else if (m_pos.x > 0.0f)
			{
				m_pos.x -= returnSpeed * deltaTime;
				if (m_pos.x < 0.0f) m_pos.x = 0.0f;
			}

			// 完全に z=170 かつ x=0 に到達したら、次の「5秒待つ」へ！
			if (m_pos.z == targetZ && m_pos.x == 0.0f)
			{
				m_actionTimer = 0.0f;
				m_bossActionStep = 4; // ⑤ 戻った後の5秒待つへ
			}
			break;
		}

		case 4: // ⑤ 戻ったあとの「5秒待つ」
			m_actionTimer += deltaTime;
			if (m_actionTimer >= 5.0f)
			{
				m_actionTimer = 0.0f;
				m_bossActionStep = 1; // ★ 再び「プレイヤーに向ける」に戻ってループ！
			}
			break;
		}

		// 撃破判定（HP < 1）
		if (m_bossHp < 1 && !m_isDead)
		{
			m_isDead = true;

			socreUI* ui = FindGO<socreUI>("socreUI");
			if (ui != nullptr)
			{
				ui->AddScore(1000);
			}

			m_bossState = 2; // 撃破演出へ
			return;
		}

		m_modelRender.SetPosition(m_pos);
		m_modelRender.Update();
	}
}

void H_1Boss::Damage(int pow)
{
	if (m_damageStopTime > 0.0f || m_isDead || m_bossState != 1)
	{
		return;
	}

	m_bossHp -= pow;
	m_damageStopTime = 0.2f; // ★ プレイヤーからの被弾硬直は 0.2秒
}

void H_1Boss::Render(RenderContext& rc)
{
	if (m_bossState != 2 || m_pos.z <= 218.0f)
	{
		m_modelRender.Draw(rc);
	}
}