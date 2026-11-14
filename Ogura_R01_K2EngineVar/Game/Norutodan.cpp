#include "stdafx.h"
#include "Norutodan.h"
#include"Yomogi.h"
#include"Sakuran.h"

Norutodan::Norutodan()
{
	m_modelRender.Init("Assets/modelData/Player/noruto_TAMA.tkm");
    m_modelRender.SetScale(Vector3(0.5f, 0.5f, 0.5f));
    m_modelRender.Update();
}
Norutodan::~Norutodan()
{
}

bool Norutodan::Start()
{
	return true;
}
void Norutodan::Update()
{
    float deltaTime = g_gameTime->GetFrameDeltaTime();

    // 消滅演出中（フワッと大きくなっている最中）
    if (m_isDead)
    {
        m_deathTimer += deltaTime;

        // 拡大処理
        m_scaleValue += 3.0f * deltaTime;
        m_modelRender.SetScale(Vector3(m_scaleValue, m_scaleValue, m_scaleValue));
       
        m_modelRender.Update();

        // 0.15秒経過したら確実に削除
        if (m_deathTimer > 0.15f)
        {
            DeleteGO(this);
        }
        return; 
    }

    // 通常移動処理
    m_pos += m_moveDirection * m_speed * deltaTime;
    m_modelRender.SetPosition(m_pos);
   
    Yomogi* yomogi = FindGO<Yomogi>("Yomogi1");
    if (yomogi != nullptr)
    {
        Vector3 yomogiPos = yomogi->GetPosition();
        Vector3 diff = m_pos - yomogiPos;
        float distance = diff.Length();

        if (distance < 30.0f)
        {
            // ヨモギーにダメージを与える（例：攻撃力6を与える）
            yomogi->Damage(6);

            // 弾自身は消滅演出へ
            m_isDead = true;
        }
    }

    Sakuran* sakuran = FindGO<Sakuran>("Sakuran1");
    if (sakuran != nullptr)
    {
        Vector3 sakuranPos = sakuran->GetPosition();
        if ((m_pos - sakuranPos).Length() < 30.0f)
        {
            sakuran->Damage(6); // サクランのダメージ関数を呼ぶ
            m_isDead = true;
        }
    }
    // ワールド座標Zの境界チェック（180を超えたら消滅演出スタート）
    if (m_pos.z >= 170.0f)
    {
        m_isDead = true;
    }
    m_modelRender.Update();
}


void Norutodan::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
