#include "stdafx.h"
#include "Noruto.h"
#include "Norutodan.h"
#include "gameover.h"
#include "Stage1.h"
#include "aclere.h" // ★ α版クリア画面のヘッダーをインクルード！
#include "sound/SoundEngine.h"

Noruto::Noruto()
{
	m_modelRender.Init("Assets/modelData/Player/Noruto.tkm");
	m_pos = Vector3(0.0f, 18.0f, -140.0f);
	m_characterController.Init(3.0f, 200.0f, m_pos);

	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();

	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/SE/shot.wav");
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/SE/ara.wav");
	// ★ ゲーム開始時にあらかじめ弾をプール（生成）しておく
	for (int i = 0; i < c_maxBullets; ++i)
	{
		Norutodan* tama = NewGO<Norutodan>(0, "Norutodan");
		tama->SetActive(false); // 最初は非アクティブ（待機中）にしておく
		m_bulletPool.push_back(tama);
	}
}

Noruto::~Noruto()
{
}

void Noruto::Update()
{
	// ★ ゲームオーバー画面がすでに生成されていたら、プレイヤー自身を消して処理を抜ける
	if (FindGO<gameover>("gameover") != nullptr)
	{
		DeleteGO(this);
		return;
	}

	Move();

	// ★ HPが0になったらゲームオーバーを生成
	if (m_HP <= 0)
	{
		// ★ 【重要】すでにゲームオーバーが出ておらず、さらに「クリア画面（aclere）が出ていない」ときだけ発動！
		if (FindGO<gameover>("gameover") == nullptr && FindGO<aclere>("aclere") == nullptr)
		{
			Stage1* stage1 = FindGO<Stage1>("Stage1");
			if (stage1 != nullptr)
			{
				stage1->StopBGM();
			}
			NewGO<gameover>(0, "gameover");
		}
	}

	if (m_shootIntervalTimer > 0.0f)
	{
		m_shootIntervalTimer -= g_gameTime->GetFrameDeltaTime();
	}

	if (g_pad[0]->IsPress(enButtonA) && m_shootIntervalTimer <= 0.0f)
	{
		Shoot();
		m_shootIntervalTimer = 0.1f;
	}

	m_modelRender.Update();
}

void Noruto::Move()
{
	m_speed = Vector3(0.0f, 0.0f, 0.0f);

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	float stickLength = stickL.Length();

	if (stickLength > 0.01f)
	{
		stickL.Normalize();

		float moveSpeed = 30.0f * 3.0f * min(stickLength, 1.0f);

		m_speed.x = stickL.x * moveSpeed;
		m_speed.z = stickL.y * moveSpeed;
	}
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	if (deltaTime > 0.1f) {
		deltaTime = 1.0f / 60.0f;
	}

	m_pos = m_characterController.Execute(m_speed, deltaTime);

	// 左右の制限
	if (m_pos.x < -300.0f) { m_pos.x = -300.0f; }
	if (m_pos.x > 300.0f) { m_pos.x = 300.0f; }

	// 上下の制限
	if (m_pos.z < -170.0f) { m_pos.z = -170.0f; }
	if (m_pos.z > 170.0f) { m_pos.z = 170.0f; }

	m_characterController.SetPosition(m_pos);
	m_modelRender.SetPosition(m_pos);
}

void Noruto::Shoot()
{
	Vector3 forward = Vector3::AxisZ;

	SoundSource* shotSe = NewGO<SoundSource>(0);
	shotSe->Init(7);
	shotSe->Play(false);

	// ★ プールから空いている（非アクティブな）弾を探して発射するヘルパーラムダ
	auto fireBullet = [&](const Vector3& dir) {
		for (auto tama : m_bulletPool)
		{
			if (!tama->IsActive())
			{
				tama->Shoot(m_pos, dir); // 位置と向きをセットして有効化
				break;
			}
		}
		};

	// 左
	fireBullet(RotateVectorY(forward, -10.0f));
	// 中
	fireBullet(forward);
	// 右
	fireBullet(RotateVectorY(forward, 10.0f));
}

Vector3 Noruto::RotateVectorY(const Vector3& vec, float angleDeg)
{
	float rad = angleDeg * (3.14159265f / 180.0f);
	float cosVal = cos(rad);
	float sinVal = sin(rad);

	Vector3 result;
	result.x = vec.x * cosVal + vec.z * sinVal;
	result.y = vec.y;
	result.z = -vec.x * sinVal + vec.z * cosVal;
	return result;
}

void Noruto::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}