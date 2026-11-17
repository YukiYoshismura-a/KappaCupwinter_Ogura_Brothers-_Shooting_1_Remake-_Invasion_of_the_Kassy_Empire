#pragma once
#include"sound/SoundSource.h"
class title :public IGameObject
{
public:

	title();
	~title();

	void Render(RenderContext& rc) override;

	void Update();
	void SetAlpha(float alpha);
	
	bool m_isSelectung = false;
	SpriteRender m_spriteRender;
	SoundSource* m_bgm;

};

