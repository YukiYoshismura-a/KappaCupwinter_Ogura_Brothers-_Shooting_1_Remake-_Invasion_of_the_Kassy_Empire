#include "stdafx.h"
#include "Norutodan.h"
#include "Yomogi.h"
#include "Sakuran.h"
#include"H_1Boss.h"
#include "sound/SoundEngine.h"

Norutodan::Norutodan()
{
    m_modelRender.Init("Assets/modelData/Player/noruto_TAMA.tkm");
    m_modelRender.SetScale(Vector3(0.5f, 0.5f, 0.5f));
    g_soundEngine->ResistWaveFileBank(8, "Assets/sound/SE/hit.wav");
    m_modelRender.Update();


}

Norutodan::~Norutodan()
{
}

bool Norutodan::Start()
{
    return true;
}

void Norutodan::Shoot(const Vector3& pos, const Vector3& dir)
{
    m_pos = pos;
    m_moveDirection = dir;
    m_isActive = true;  // 弾を有効化！

    // ★ ここで消滅用のフラグやタイマーを確実に初期化する！
    m_isDead = false;
    m_deathTimer = 0.0f;
    m_scaleValue = 0.5f; // 当初のサイズ（0.5倍など）にリセット

    m_modelRender.SetScale(Vector3(m_scaleValue, m_scaleValue, m_scaleValue));
    m_modelRender.SetPosition(m_pos);

    m_modelRender.Update();


}
// Norutodan.cpp の Update() の判定部分はこれだけでOK！
void Norutodan::Update()
{
    if (!m_isActive) return;

    float deltaTime = g_gameTime->GetFrameDeltaTime();

    if (m_isDead)
    {
        m_deathTimer += deltaTime;
        m_scaleValue += 3.0f * deltaTime;
        m_modelRender.SetScale(Vector3(m_scaleValue, m_scaleValue, m_scaleValue));
        m_modelRender.Update();
        if (m_deathTimer > 0.15f) { m_isActive = false; }
        return;
    }

    m_pos += m_moveDirection * m_speed * deltaTime;
    m_modelRender.SetPosition(m_pos);

    // ==========================================
    // ★ Yomogi1 〜 Yomogi3 をループで全員チェック！
    // ==========================================
    for (int i = 1; i <= 3; i++)
    {
        char name[32];
        sprintf_s(name, "Yomogi%d", i);
        Yomogi* yomogi = FindGO<Yomogi>(name);
        if (yomogi != nullptr)
        {
            Vector3 yomogiPos = yomogi->GetPosition();
            if ((m_pos - yomogiPos).Length() < 30.0f)
            {
                yomogi->Damage(6);
                m_isDead = true;

                SoundSource* hitSe = NewGO<SoundSource>(0);
                hitSe->Init(8);
                hitSe->SetVolume(2.5f);
                hitSe->Play(false);
                break; // 当たったら消滅へ
            }
        }
    }

    // 既に当たって消滅中ならサクラン判定はスキップ
    if (m_isDead)
    {
        m_modelRender.Update();
        if (m_pos.z >= 170.0f) {
            m_isDead = true;
        }
        return;
    }

    // ==========================================
    // ★ Sakuran1 〜 Sakuran3 をループで全員チェック！
    // ==========================================
    for (int i = 1; i <= 3; i++)
    {
        char name[32];
        sprintf_s(name, "Sakuran%d", i);
        Sakuran* sakuran = FindGO<Sakuran>(name);
        if (sakuran != nullptr)
        {
            Vector3 sakuranPos = sakuran->GetPosition();
            if ((m_pos - sakuranPos).Length() < 30.0f)
            {
                sakuran->Damage(6);
                m_isDead = true;

                SoundSource* hitSe = NewGO<SoundSource>(0);
                hitSe->Init(8);
                hitSe->SetVolume(2.5f);
                hitSe->Play(false);
                break; // 当たったら消滅へ
            }
        }
    }
    H_1Boss* boss = FindGO<H_1Boss>("H_1Boss"); // ※ボスのインスタンス名に合わせてね
    if (boss != nullptr && !boss->IsDead())
    {
        Vector3 bossPos = boss->GetPosition();
        if ((m_pos - bossPos).Length() < 90.0f) // ボスの当たり判定サイズ
        {
            boss->Damage(6);
            m_isDead = true;

            SoundSource* hitSe = NewGO<SoundSource>(0);

            hitSe->Init(8);
            hitSe->SetVolume(2.5f);
            hitSe->Play(false);
        }

    }

    // 画面外（奥）に行ったら消滅
    if (m_pos.z >= 170.0f)
    {
        m_isDead = true;
    }

    m_modelRender.Update();
}

void Norutodan::Render(RenderContext& rc)
{
    // ★ 非アクティブのときは描画しない
    if (!m_isActive)
    {
        return;
    }

    m_modelRender.Draw(rc);
}