#include "stdafx.h"
#include "H_1BossHPGage.h"
#include "H_1Boss.h"

H_1BossHPGage::H_1BossHPGage()
{
	// 1. ゲージの枠（H_1HPGagename.dds）を初期化
	m_spriteRender.Init("Assets/image/H_1HPGagename.dds", 500.0f, 40.0f);
	m_spriteRender.SetPosition(Vector3(700.0f, 430.0f, 0.0f));

	// 2. ゲージの本体（H_1HPGage.dds）を初期化
	m_gaugeSprite.Init("Assets/image/H_1HPGage.dds", 380.0f, 30.0f);

	// ★ Scratchの「右端固定」を再現するため、ピボットを「右端（1.0f）」にする！
	m_gaugeSprite.SetPivot(Vector2(1.0f, 0.5f));
	m_gaugeSprite.SetPosition(Vector3(948.0f, 430.0f, 0.0f));

}

H_1BossHPGage::~H_1BossHPGage()
{
}

bool H_1BossHPGage::Start()
{
	return true;
}

void H_1BossHPGage::Update()
{
	// ボスが存在するかチェック
	H_1Boss* boss = FindGO<H_1Boss>("H_1Boss");
	if (boss == nullptr)
	{
		// ボスが倒されたり消滅したら、ゲージ全体を消す
		DeleteGO(this);
		return;
	}

	// ボスのHP割合（0.0f ～ 1.0f）を取得（最大HP1000想定）
	float hpRate = (float)boss->GetHp() / 1000.0f;
	if (hpRate < 0.0f) hpRate = 0.0f;
	if (hpRate > 1.0f) hpRate = 1.0f;

	// ★ 右端固定のまま、左側へ向かって縮ませる（スケール変更のみ！）
	m_gaugeSprite.SetScale(Vector3(hpRate, 1.0f, 1.0f));

	// （※ここで毎フレーム位置を上書きしとった処理を削除したから、960.0f の位置がキープされるで！）

	// スプライトの更新
	m_spriteRender.Update();
	m_gaugeSprite.Update();
}

void H_1BossHPGage::Render(RenderContext& rc)
{
	// 本体を描画した上に、枠を重ねて描画する
	m_gaugeSprite.Draw(rc);
	m_spriteRender.Draw(rc);
}