#pragma once

class EnemyManager;

class BGMtitle :public IGameObject
{
public:

	BGMtitle();
	~BGMtitle();
	void Update();
	void Render(RenderContext& rc);
	void Move();

	void SetEnemyManager(EnemyManager* manager) {
		m_enemyManager = manager;
	}

private:
	SpriteRender m_spriterender;
	Vector3 m_pos;
	Quaternion m_rotate;

	EnemyManager* m_enemyManager = nullptr;
	
	int m_state;
	float m_stayTimer;


};

