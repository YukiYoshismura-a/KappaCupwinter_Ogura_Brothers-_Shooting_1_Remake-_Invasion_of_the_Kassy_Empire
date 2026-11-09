#include "stdafx.h"
#include "Noruto.h"
Noruto::Noruto()
{

	m_modelRender.Init("Assets/modelData/Player/Noruto.tkm");
	m_modelRender.SetPosition(Vector3(0, 30.5f, 0));

	m_modelRender.Update();
}

Noruto::~Noruto()
{
}

void Noruto::Update()
{
	//m_rot.AddRotationDegY(1.0f);
	m_rot.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.Update();
}

void Noruto::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}