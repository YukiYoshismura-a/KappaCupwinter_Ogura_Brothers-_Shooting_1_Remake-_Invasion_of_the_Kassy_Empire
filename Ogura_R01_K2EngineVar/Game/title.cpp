#include "stdafx.h"
#include "title.h"
#include"sound/SoundEngine.h"
title::title()
{

	m_spriteRender.Init("Assets/image/title.DDS", 1920.0f, 1080.0f);
	
	g_soundEngine->ResistWaveFileBank(0,"Assets/sound/BGM/title.wav");
	m_bgm = NewGO<SoundSource>(0);
	m_bgm->Init(0);
	m_bgm->Play(true);
}
void title::SetAlpha(float alpha)
{
	m_spriteRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, alpha));
}

title::~title()
{
	if (m_bgm != nullptr)
	{
		DeleteGO(m_bgm);
	}
}

void title::Update()
{
	

	// g_renderingEngine->DisableRaytracing();
	if (!m_isSelectung && g_pad[0]->IsTrigger(enButtonA))
	{
		m_isSelectung = true;

		SetAlpha(0.5f);

		
	}
}
void title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}