#pragma once
class socreUI:public IGameObject
{
public:
	socreUI();
	~socreUI();
	void Update();
	void Render(RenderContext& rc);
	void AddScore(int point) { m_score += point; }
	int GetScore() const { return m_score; }


private:
	FontRender fontRender;
	int m_score = 0;


};

