#include "stdafx.h"
#include "Norutodan.h"

Norutodan::Norutodan()
{
	m_modelRender.Init("Assets/modelData/Player/noruto_TAMA.tkm");
	
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
	m_pos += m_moveDirection * m_speed * deltaTime;
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();

	if (m_pos.z > 180.0f)
	{
		DeleteGO(this);
	}


}

void Norutodan::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
