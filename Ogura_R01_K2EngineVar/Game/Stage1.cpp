#include "stdafx.h"
#include "Stage1.h"
#include "BGMtitle.h"
#include"EnemyManager.h"
#include "sound/SoundEngine.h"

Stage1::Stage1()
{
	
	m_modelRender.Init("Assets/modelData/Stage/Stage1.tkm");
	m_modelRender.SetPosition(Vector3(0, 0, 0));

	
	EnemyManager*enemymanager=NewGO<EnemyManager>(0, "Enemymanager");
	BGMtitle*bgmTitle=NewGO<BGMtitle>(0, "Bgmtitle");
	
	bgmTitle->SetEnemyManager(enemymanager);

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/BGM/ogurakoshinkyoku\.wav"); // ※実際のファイル名に合わせて変更してな！

m_stageBgm = NewGO<SoundSource>(0);
	m_stageBgm->Init(6);
	m_stageBgm->Play(true);
	m_modelRender.Update();
}

Stage1::~Stage1()
{
	if (m_stageBgm != nullptr)
	{
		DeleteGO(m_stageBgm);
	}

}
void Stage1::StopBGM()
{
	if (m_stageBgm != nullptr)
	{
		DeleteGO(m_stageBgm);
		m_stageBgm = nullptr;
	}
}
void Stage1::Update()
{
}

void Stage1::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}