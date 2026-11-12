#pragma once
class Noruto :public IGameObject
{
public:
	Noruto();
	~Noruto();
	void Render(RenderContext& rc);
	void Update();
	void Move();
	void Shoot();
	
	Vector3 GetPosition()const{
		return m_pos;
	}

	void Damage(int power) {
		m_HP -= power;
	}

	int GetHP() const { return m_HP; }

	Vector3 RotateVectorY(const Vector3& vec, float angleDeg); 
private:
	ModelRender m_modelRender;
	CharacterController m_characterController;
	Vector3 m_speed;
	Vector3 m_pos;
	
	int m_ATK = 6;
	int m_HP = 600;

	int sccor = 0;
	float m_shootIntervalTimer = 0.0f;
};