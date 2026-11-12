#pragma once
class Yomogi :public IGameObject
{
public:
	Yomogi();
	~Yomogi();

	void Update();
	void Move();

	void Damage(int pow);
	void Render(RenderContext&rc);

	int GetHp() const { return Y_HP; }

	Vector3 GetPosition() const { return m_pos; }
private:
	ModelRender m_modelRender;

	int Y_HP = 20;
	float m_damageStopTime = 0.0f;
	float m_attacktimer = 0.0f;
	Vector3 m_pos;
	const int plasPoint = 100;
};

