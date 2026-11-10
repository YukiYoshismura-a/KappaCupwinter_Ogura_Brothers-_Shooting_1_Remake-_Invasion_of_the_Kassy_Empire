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
	//敵にあたった時これ呼ぶ
	void Hit()
	{
		if (!m_isDead)
		{
			m_isDead = true;
			
		}
	}
private:
	ModelRender m_modelRender;
	Vector3 m_pos = Vector3::Zero;

	Vector3 m_moveDirection = Vector3::AxisZ;
	float m_speed = 200.0f;

	//消去用演出
	bool m_isDead = false;
	float m_scaleValue = 0.5f;
	float m_deathTimer = 0.0f;
	
};

