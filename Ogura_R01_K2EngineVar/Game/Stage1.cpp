#include "stdafx.h"
#include "Stage1.h"
#include "BGMtitle.h"
#include"EnemyManager.h"

Stage1::Stage1()
{
	
	m_modelRender.Init("Assets/modelData/Stage/Stage1.tkm");
	m_modelRender.SetPosition(Vector3(0, 0, 0));

	
	EnemyManager*enemymanager=NewGO<EnemyManager>(0, "Enemymanager");
	BGMtitle*bgmTitle=NewGO<BGMtitle>(0, "Bgmtitle");
	
	bgmTitle->SetEnemyManager(enemymanager);

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