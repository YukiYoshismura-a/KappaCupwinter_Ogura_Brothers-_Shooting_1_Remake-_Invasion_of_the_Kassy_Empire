#include "stdafx.h"
#include "title.h"

title::title()
{

	m_spriteRender.Init("Assets/image/title.DDS",1920.0f,1080.0f);
}

void title::SetAlpha(float alpha)
{
	m_spriteRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, alpha));
}

title::~title()
{
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