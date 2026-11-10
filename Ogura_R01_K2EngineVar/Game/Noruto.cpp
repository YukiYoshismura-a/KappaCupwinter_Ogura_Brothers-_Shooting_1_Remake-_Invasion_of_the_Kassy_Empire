#include "stdafx.h"
#include "Noruto.h"
#include"Norutodan.h"

Noruto::Noruto()
{

	m_modelRender.Init("Assets/modelData/Player/Noruto.tkm");
	m_pos = Vector3(0.0f, 18.0f, 0.0f);
	m_characterController.Init(3.0f, 200.0f, m_pos);
	
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();
}

Noruto::~Noruto()
{
}

void Noruto::Update()
{
	Move();
	if (m_shootIntervalTimer > 0.0f)
	{
	

			m_shootIntervalTimer -= g_gameTime->GetFrameDeltaTime();
		
	}

	if (g_pad[0]->IsPress(enButtonA)&&m_shootIntervalTimer<=0.0f)
	{
		Shoot();

		m_shootIntervalTimer = 0.1f;
	}
	else
	{
		m_shootIntervalTimer = 0.0f;
	}
	m_modelRender.Update();
}

void Noruto::Move()
{
	m_speed = Vector3(0.0f, 0.0f, 0.0f);

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	m_speed.x += stickL.x * 30.0f*3;
	m_speed.z += stickL.y * 30.0f*3;


	m_pos = m_characterController.Execute(m_speed, 1.0f/60.0f);
	m_modelRender.SetPosition(m_pos);
}

void Noruto::Shoot()
{
	Vector3 forward = Vector3::AxisZ;
	//左
	{
		Vector3 dir = RotateVectorY(forward, -10.0f);
		Norutodan* tama = NewGO<Norutodan>(0, "Norutodan");
		tama->SetPosition(m_pos);
		tama->kakudo(dir);
	}
	//中
	{

		Norutodan* tama = NewGO<Norutodan>(0, "Norutodan");
		tama->SetPosition(m_pos);
		tama->kakudo(forward);

	}

	{
		Vector3 dir = RotateVectorY(forward, 10.0f);
		Norutodan* tama = NewGO<Norutodan>(0, "Norutodan");
		tama->kakudo(dir);
	}
	//右
	{
		Vector3 dir = RotateVectorY(forward, 10.0f);
		Norutodan* tama = NewGO<Norutodan>(0, "Norutodan");
		tama->SetPosition(m_pos);
		tama->kakudo(dir);
	}
}
	Vector3 Noruto::RotateVectorY(const Vector3 & vec, float angleDeg)
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