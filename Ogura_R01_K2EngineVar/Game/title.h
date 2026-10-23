#pragma once
class title :public IGameObject
{
public:

	title();
	~title();

	void Render(RenderContext& rc) override;

	SpriteRender m_spriteRender;

};

