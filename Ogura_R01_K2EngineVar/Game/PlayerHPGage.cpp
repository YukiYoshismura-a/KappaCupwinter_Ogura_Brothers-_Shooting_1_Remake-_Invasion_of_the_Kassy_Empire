#include "stdafx.h"
#include "PlayerHPGage.h"
#include "Noruto.h"

PlayerHPGage::PlayerHPGage()
{
}

PlayerHPGage::~PlayerHPGage()
{
}

// ★ 初期化は Start() の中に移動する！
bool PlayerHPGage::Start()
{
    // 赤いバー画像（.dds）の初期化
    m_hpGage.Init("Assets/image/PlayerHPGage.DDS", 1.0f, 15.0f);

    // ピボット（基準点）を「左端・上下中央」にする
    m_hpGage.SetPivot(Vector2(0.0f, 0.5f));

    // 画面左下の位置に配置
    m_hpGage.SetPosition(Vector3(-800.0f, -500.0f, 0.0f));
   
    // 最初に1回だけ Noruto を探してキャッシュしておく
    m_noruto = FindGO<Noruto>("Noruto");

    return true;
}

void PlayerHPGage::Update()
{
    if (m_noruto == nullptr) {
        m_noruto = FindGO<Noruto>("Noruto");
        return;
    }

    // 現在のHPを取得
    int currentHP = m_noruto->GetHP();
    if (currentHP < 0) {
        currentHP = 0; // マイナスになってバーが逆転するのを防ぐ
    }

    // Scratchと同じ「現在HP / 10.0f」を横幅のスケールにする
    float barWidth = static_cast<float>(currentHP) / 5.0f;

    m_hpGage.SetScale(Vector3(barWidth, 2.0f, 2.0f));
    m_hpGage.Update();
}

void PlayerHPGage::Render(RenderContext& rc)
{
    m_hpGage.Draw(rc);
}