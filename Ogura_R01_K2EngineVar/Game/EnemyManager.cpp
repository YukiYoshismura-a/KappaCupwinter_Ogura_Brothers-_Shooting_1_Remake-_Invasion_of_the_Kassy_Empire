#include "stdafx.h"
#include "EnemyManager.h"
#include"Yomogi.h"

EnemyManager::EnemyManager()
{
	m_stageState = 0;
	m_Timer = 0.0f;
	m_spawnCount = 0;
	m_isTitleFinished = false;
	m_currentYomogi = nullptr;

}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::Update()
{
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	switch (m_stageState)
	{
		case 0: // タイトル終了待ち
		if (m_isTitleFinished)
		{
			m_Timer = 0.0f;
			m_stageState = 1;
		}
		break;
		case 1: // 3秒待つ
		m_Timer += deltaTime;
		if (m_Timer >= 3.0f)
		{
			m_Timer = 0.0f;
			m_spawnCount = 0;       // 何回繰り返したかのカウンター
			m_stageState = 2;       // 戦闘ウェーブへ！
		}
		break;

		case 2: // 5回繰り返す（ヨモギーを出して倒されるまで待つ）
		{
			Yomogi* existingYomogi = FindGO<Yomogi>("Yomogi1");

			// もし画面上にヨモギーがいなくて、かつまだ5体出してないなら…
			if (existingYomogi == nullptr && m_spawnCount < 5)
			{
				NewGO<Yomogi>(0, "Yomogi1"); // 新しく1体出す！
				m_spawnCount++;              // カウントを＋1する
			}
			// 5体出し切って、かつ画面上のヨモギーもいなくなったら次のウェーブへ
			else if (m_spawnCount >= 5 && existingYomogi == nullptr)
			{
				m_stageState = 3;
			}


			break;
		}
		case 3:

		break;

		default:
			break;

	}
	
}