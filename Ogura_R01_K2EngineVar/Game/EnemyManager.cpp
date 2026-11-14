#include "stdafx.h"
#include "EnemyManager.h"
#include"Yomogi.h"
#include"Sakuran.h"

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
		case 3: // 3秒待つ
			m_Timer += deltaTime;
			if (m_Timer >= 3.0f)
			{
				m_Timer = 0.0f;
				m_spawnCount = 0; // カウンターをリセット
				m_stageState = 4; // サクランのウェーブへ
			}
			break;

		case 4: // 【サクラン】10回繰り返す（出して倒される/消えるまで待つ）
		{
			Sakuran* existingSakuran = FindGO<Sakuran>("Sakuran1");

			if (existingSakuran == nullptr && m_spawnCount < 10)
			{
				NewGO<Sakuran>(0, "Sakuran1");
				m_spawnCount++;
			}
			else if (m_spawnCount >= 10 && existingSakuran == nullptr)
			{
				m_Timer = 0.0f;
				m_stageState = 5; // 10体終わったら次へ
			}
			break;
		}

		case 5: // 3秒待つ
			m_Timer += deltaTime;
			if (m_Timer >= 3.0f)
			{
				m_Timer = 0.0f;
				m_stageState = 6;
			}
			break;

		case 6: // 【サクラン】1体送る（待たずにすぐ次へ進む）
		{
			NewGO<Sakuran>(0, "Sakuran1"); // 出すだけ出す
			m_Timer = 0.0f;
			m_stageState = 7; // 0.5秒待ちフェーズへ直行
			break;
		}

		case 7: // 0.5秒待つ
			m_Timer += deltaTime;
			if (m_Timer >= 0.5f)
			{
				m_Timer = 0.0f;
				m_spawnCount = 0; // ヨモギー用のフラグとしてリセット
				m_stageState = 8;
			}
			break;

		case 8: // 【ヨモギー】1体出して、体力が0になる（消滅する）まで待つ
		{
			Yomogi* existingYomogi = FindGO<Yomogi>("Yomogi1");

			// まだ出していなければ1体出す
			if (existingYomogi == nullptr && m_spawnCount == 0)
			{
				NewGO<Yomogi>(0, "Yomogi1");
				m_spawnCount = 1; // 「すでに出した」という印
			}
			// 出し終わっていて、かつ画面からいなくなったらクリア！
			else if (m_spawnCount == 1 && existingYomogi == nullptr)
			{
				m_stageState = 9; // ウェーブ完全クリア！
			}
			break;
		}

		default:
			break;

	}
	
}