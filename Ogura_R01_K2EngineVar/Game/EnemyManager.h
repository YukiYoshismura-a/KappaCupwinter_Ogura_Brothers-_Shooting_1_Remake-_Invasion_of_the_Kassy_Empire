#pragma once

class Yomogi;

class EnemyManager:public IGameObject
{
public:
	EnemyManager();
	~EnemyManager();

	void Update();
	
	void OnTitleFinished()
	{
		m_isTitleFinished = true;
	}
private:
	int m_stageState = 0;
	float m_Timer = 0.0f;
	bool m_isTitleFinished = false;
	int m_spawnCount = 0;

	Yomogi* m_currentYomogi = nullptr;
};

