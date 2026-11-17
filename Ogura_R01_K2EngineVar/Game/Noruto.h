#pragma once

class Norutodan;
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

		SoundSource* damageSe = NewGO<SoundSource>(0);
		damageSe->Init(10); // 登録した被弾用サウンドバンクID
		damageSe->Play(false);
	}

	int GetHP() const { return m_HP; }

	Vector3 RotateVectorY(const Vector3& vec, float angleDeg); 

private:
	ModelRender m_modelRender;
	CharacterController m_characterController;
	Vector3 m_speed;
	Vector3 m_pos;
	
	std::vector<Norutodan*> m_bulletPool;
	const int c_maxBullets = 57;

	int m_ATK = 6;
	int m_HP = 600;

	float m_shootIntervalTimer = 0.0f;
};