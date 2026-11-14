#pragma once
class Sakuran:public IGameObject

{
public:
	Sakuran();
	~Sakuran();

	void Update();
	void Move();

	void Render(RenderContext& rc);
	void Damage(int pow);
	int GetHp() const { return Sa_HP; }
	Vector3 GetPosition() const { return m_pos; }

private:
	ModelRender m_modelRender;

	int Sa_HP = 20;
	float m_damageStopTime = 0.0f;
	float m_attacktimer = 0.0f;
	Vector3 m_pos;
	const int plasPoint = 100;

};

