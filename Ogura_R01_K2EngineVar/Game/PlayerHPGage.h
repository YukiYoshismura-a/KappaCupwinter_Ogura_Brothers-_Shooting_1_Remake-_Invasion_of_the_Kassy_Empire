#pragma once
class Noruto;
class PlayerHPGage:public IGameObject
{
public:
	PlayerHPGage();
	~PlayerHPGage();

	void Update();
	void Render(RenderContext& rc);
	bool Start();
private:
	SpriteRender m_hpGage;
	Noruto* m_noruto = nullptr;
};

