#pragma once
class Norutodan :public IGameObject
{
public:
	Norutodan();
	~Norutodan();
	bool Start();

	void Render(RenderContext& rc) override;
	void Update()override;
	void Move();

	void SetPosition(const Vector3& pos)
	{
		m_pos = pos;
		m_modelRender.SetPosition(m_pos);
	}

	void kakudo(const Vector3& dir)
	{
		m_moveDirection = dir;
	}
private:
	ModelRender m_modelRender;
	Vector3 m_pos = Vector3::Zero;

	Vector3 m_moveDirection = Vector3::AxisZ;
	float m_speed = 800.0f;
};

