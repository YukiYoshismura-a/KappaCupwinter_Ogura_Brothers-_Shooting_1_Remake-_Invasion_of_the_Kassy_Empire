#include "stdafx.h"
#include "BGMtitle.h"
#include "EnemyManager.h"

BGMtitle::BGMtitle()
{
	m_spriterender.Init("Assets/image/ogurakoushinkyoku.DDS", 400.0f, 50.0f);
	m_pos = Vector3(950.0f, 0.0f, 0.0f);
	m_spriterender.SetPosition(m_pos);
	
	m_rotate.SetRotationDegZ(90.0f);
	m_spriterender.SetRotation(m_rotate);

	m_spriterender.SetScale(Vector3(1.5f, 1.5f, 1.5f));
	m_spriterender.Update();

	m_state = 0;
	m_stayTimer = 0.0f;
}
BGMtitle::~BGMtitle()
{

}

void BGMtitle::Update()
{
	Move();
	m_spriterender.Update();
}

void BGMtitle:: Move()
{
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	if (m_state == 0)
	{
		m_pos.x -= 60.0f * deltaTime;
		if (m_pos.x <= 850.0f)
		{
			m_pos.x = 850.0f;
			m_state = 1;	
		}
	}
	else if (m_state == 1)
	{
		m_stayTimer += deltaTime;
		if (m_stayTimer >= 3.0f)
		{
			m_state = 2;
		}
	}
	else if (m_state == 2)
	{
		m_pos.x += 60.0f * deltaTime;
		if (m_pos.x >= 950.0f)
		{
			if (m_enemyManager != nullptr)
			{
				m_enemyManager->OnTitleFinished();
			}
			DeleteGO(this);
		}
	}
	
	m_spriterender.SetPosition(m_pos);
}

void BGMtitle::Render(RenderContext& rc)
{

	m_spriterender.Draw(rc);
}