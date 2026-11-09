#pragma once
class PlayerSerct :public IGameObject
{
public:

	PlayerSerct();
	~PlayerSerct();
	void Render(RenderContext& rc);
	void Update();

private:
	SpriteRender S_Noruto;
	SpriteRender S_Ogurano;

	Vector3 m_pos;

	int select = 0;
};

