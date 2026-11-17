#pragma once
#pragma once

class H_1BossHPGage : public IGameObject
{
public:
	H_1BossHPGage();
	~H_1BossHPGage();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:
	SpriteRender m_spriteRender;
	SpriteRender m_gaugeSprite;
};
