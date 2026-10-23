#include "stdafx.h"
#include "title.h"

title::title()
{
	m_spriteRender.Init("Assets/image/title.DDS",1920.0f,1080.0f);
}

title::~title()
{
}
void title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}