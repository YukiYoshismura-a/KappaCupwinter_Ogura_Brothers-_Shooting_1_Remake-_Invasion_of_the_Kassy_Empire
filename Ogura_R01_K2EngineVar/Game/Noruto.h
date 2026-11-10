#pragma once
class Noruto :public IGameObject
{
public:
	Noruto();
	~Noruto();
	void Render(RenderContext& rc) override;
	void Update()override;
	void Move();
	void Shoot();
	Vector3 RotateVectorY(const Vector3& vec, float angleDeg); 
private:
	ModelRender m_modelRender;
	CharacterController m_characterController;
	Vector3 m_speed;
	Vector3 m_pos;
	
	int m_ATK = 6;
	int m_HP = 600;

	float m_shootIntervalTimer = 0.0f;
};