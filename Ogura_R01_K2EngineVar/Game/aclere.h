#pragma once

class aclere : public IGameObject
{
public:
	aclere();
	~aclere();

	void Update() override;
	void Render(RenderContext& rc) override;

private:
	SpriteRender m_spriteRender;
	float m_clearTimer = 0.0f;
};