#include "stdafx.h"
#include "Stage1.h"

Stage1::Stage1()
{
	m_modelRender.Init("Assets/modelData/Stage/Stage1.tkm");

	m_modelRender.SetPosition(Vector3(0, 0, 0));
	
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	m_modelRender.Update();
}

Stage1::~Stage1()
{
}

void Stage1::Update()
{
}

void Stage1::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}