#pragma once


class gameover : public IGameObject
{
public:
	gameover();
	~gameover();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:
	FontRender m_fontRender; // ゲームover画像のスプライトなど
	Vector3 m_pos;        // 文字の座標
	float m_fallTimer = 0.0f; // 4秒待つ用タイマー

};