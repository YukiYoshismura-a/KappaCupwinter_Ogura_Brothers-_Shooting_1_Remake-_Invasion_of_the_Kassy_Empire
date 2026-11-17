#include "stdafx.h"
#include "EnemyManager.h"
#include "Yomogi.h"
#include "Sakuran.h"
#include "H_1Boss.h"
#include "socreUI.h"
#include "PlayerHPGage.h"
#include "H_1BossHPGage.h"
#include "aclere.h" // ★ α版クリア画面用クラスをインクルード！
#include"gameover.h"
#include"Stage1.h"
#include"Noruto.h"
EnemyManager::EnemyManager()
{
	NewGO<socreUI>(0, "socreUI");
	NewGO<PlayerHPGage>(0, "hpGage");
	m_stageState = 0;
	m_Timer = 0.0f;
	m_spawnCount = 0;
	m_loopCount = 0;
	m_isTitleFinished = false;
	m_currentYomogi = nullptr;
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
	if (FindGO<gameover>("gameover") != nullptr)
	{
		return;
	}

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
			m_spawnCount = 0;
			m_stageState = 2; // 戦闘ウェーブへ！
		}
		break;

	case 2: // 5回繰り返す（ヨモギーを出して倒されるまで待つ：全範囲）
	{
		Yomogi* yomogi = FindGO<Yomogi>("Yomogi1");

		if (yomogi == nullptr && m_spawnCount < 5)
		{
			Yomogi* newYomogi = NewGO<Yomogi>(0, "Yomogi1");
			newYomogi->Init(-223.0f, 223.0f); // 全範囲からランダム
			m_spawnCount++;
		}
		else if (m_spawnCount >= 5 && yomogi == nullptr)
		{
			m_spawnCount = 0;
			m_stageState = 3;
		}
		break;
	}

	case 3: // 3秒待つ
		m_Timer += deltaTime;
		if (m_Timer >= 3.0f)
		{
			m_Timer = 0.0f;
			m_spawnCount = 0;
			m_stageState = 4;
		}
		break;

	case 4: // 【サクラン】10回繰り返す
	{
		Sakuran* existingSakuran = FindGO<Sakuran>("Sakuran1");

		if (existingSakuran == nullptr && m_spawnCount < 10)
		{
			NewGO<Sakuran>(0, "Sakuran1");
			m_spawnCount++;
		}
		else if (m_spawnCount >= 10 && existingSakuran == nullptr)
		{
			m_spawnCount = 0;
			m_Timer = 0.0f;
			m_stageState = 5;
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

	case 6: // ループの初期化
	{
		m_loopCount = 0;
		m_spawnCount = 0;
		m_stageState = 7;
		break;
	}

	case 7: // 5回繰り返すメイン処理（サクラン1 ＋ 0.5秒 ＋ ヨモギー1）
	{
		if (m_loopCount < 5)
		{
			if (m_spawnCount == 0)
			{
				Sakuran* sakuran = NewGO<Sakuran>(0, "Sakuran1");
				sakuran->Init(-223.0f, 223.0f);
				m_Timer = 0.0f;
				m_spawnCount = 1;
			}
			else if (m_spawnCount == 1)
			{
				m_Timer += deltaTime;
				if (m_Timer >= 0.5f)
				{
					m_Timer = 0.0f;
					m_spawnCount = 2;
				}
			}
			else if (m_spawnCount == 2)
			{
				Yomogi* yomogi = FindGO<Yomogi>("Yomogi1");

				if (yomogi == nullptr && m_Timer == 0.0f)
				{
					Yomogi* newYomogi = NewGO<Yomogi>(0, "Yomogi1");
					newYomogi->Init(-223.0f, 223.0f);
					m_Timer = 1.0f;
				}
				else if (yomogi == nullptr && m_Timer > 0.0f)
				{
					m_Timer = 0.0f;
					m_loopCount++;
					m_spawnCount = 0;
				}
			}
		}
		else
		{
			m_loopCount = 0;
			m_spawnCount = 0;
			m_stageState = 8;
		}
		break;
	}

	case 8: // 【ヨモギー】1体出して倒されるまで待つ
	{
		Yomogi* yomogi = FindGO<Yomogi>("Yomogi1");

		if (yomogi == nullptr && m_spawnCount == 0)
		{
			Yomogi* newYomogi = NewGO<Yomogi>(0, "Yomogi1");
			newYomogi->Init(-223.0f, 223.0f);
			m_spawnCount = 1;
		}
		else if (m_spawnCount == 1 && yomogi == nullptr)
		{
			m_spawnCount = 0;
			m_stageState = 9;
		}
		break;
	}

	case 9:
	{
		m_loopCount = 0;
		m_spawnCount = 0;
		m_stageState = 10;
		break;
	}

	case 10: // ① ヨモギー2（左寄り）
	{
		Yomogi* yomogi = FindGO<Yomogi>("Yomogi2");
		if (yomogi == nullptr && m_spawnCount == 0)
		{
			Yomogi* newYomogi = NewGO<Yomogi>(0, "Yomogi2");
			newYomogi->Init(-223.0f, -50.0f);
			m_spawnCount = 1;
		}
		else if (m_spawnCount == 1 && yomogi == nullptr)
		{
			m_spawnCount = 0;
			m_stageState = 11;
		}
		break;
	}

	case 11: // ② ヨモギー3（右寄り）
	{
		Yomogi* yomogi = FindGO<Yomogi>("Yomogi3");
		if (yomogi == nullptr && m_spawnCount == 0)
		{
			Yomogi* newYomogi = NewGO<Yomogi>(0, "Yomogi3");
			newYomogi->Init(50.0f, 223.0f);
			m_spawnCount = 1;
		}
		else if (yomogi == nullptr && m_spawnCount == 1)
		{
			m_spawnCount = 0;
			m_stageState = 12;
		}
		break;
	}

	case 12: // ③ サクラン2 と 3
	{
		Sakuran* sakuran2 = NewGO<Sakuran>(0, "Sakuran2");
		sakuran2->Init(-223.0f, -50.0f);

		Sakuran* sakuran3 = NewGO<Sakuran>(0, "Sakuran3");
		sakuran3->Init(50.0f, 223.0f);

		m_stageState = 13;
		break;
	}

	case 13:
	{
		m_Timer += deltaTime;
		if (m_Timer >= 4.0f)
		{
			m_Timer = 0.0f;
			m_loopCount++;

			if (m_loopCount >= 5)
			{
				m_loopCount = 0;
				m_stageState = 14;
			}
			else
			{
				m_stageState = 10;
			}
		}
		break;
	}
	case 14:
	{
		m_Timer += deltaTime;
		if (m_Timer >= 4.0f)
		{
			m_Timer = 0.0f;
			m_stageState = 15;
		}
		break;
	}

	case 15:
	{
		Sakuran* sakuran2 = NewGO<Sakuran>(0, "Sakuran2");
		sakuran2->Init(-223.0f, -50.0f);

		m_stageState = 16;
		break;
	}

	case 16:
	{
		m_Timer += deltaTime;
		if (m_Timer >= 1.0f)
		{
			m_Timer = 0.0f;
			m_stageState = 17;
		}
		break;
	}

	case 17:
	{
		Yomogi* yomogi = FindGO<Yomogi>("Yomogi2");
		if (yomogi == nullptr && m_spawnCount == 0)
		{
			Yomogi* newYomogi = NewGO<Yomogi>(0, "Yomogi2");
			newYomogi->Init(-223.0f, -50.0f);
			m_spawnCount = 1;
		}
		else if (m_spawnCount == 1 && yomogi == nullptr)
		{
			m_Timer += deltaTime;
			if (m_Timer >= 4.0f)
			{
				m_Timer = 0.0f;
				m_spawnCount = 0;
				m_stageState = 18;
			}
		}
		break;
	}
	case 18:
	{
		Sakuran* sakuran2 = NewGO<Sakuran>(0, "Sakuran2");
		sakuran2->Init(-223.0f, -50.0f);

		m_stageState = 19;
		break;
	}

	case 19:
	{
		Yomogi* yomogi3 = FindGO<Yomogi>("Yomogi3");
		if (yomogi3 == nullptr && m_spawnCount == 0)
		{
			Yomogi* newYomogi = NewGO<Yomogi>(0, "Yomogi3");
			newYomogi->Init(50.0f, 223.0f);
			m_spawnCount = 1;
		}
		else if (m_spawnCount == 1 && yomogi3 == nullptr)
		{
			m_spawnCount = 0;
			m_Timer = 0.0f;
			m_stageState = 20;
		}
		break;
	}

	case 20:
	{
		m_Timer += deltaTime;
		if (m_Timer >= 4.0f)
		{
			m_Timer = 0.0f;
			m_stageState = 21;
		}
		break;
	}

	case 21:
	{
		Sakuran* sakuran3 = NewGO<Sakuran>(0, "Sakuran3");
		sakuran3->Init(50.0f, 223.0f);

		m_stageState = 22;
		break;
	}

	case 22:
	{
		Yomogi* yomogi2 = FindGO<Yomogi>("Yomogi2");
		if (yomogi2 == nullptr && m_spawnCount == 0)
		{
			Yomogi* newYomogi = NewGO<Yomogi>(0, "Yomogi2");
			newYomogi->Init(-223.0f, -50.0f);
			m_spawnCount = 1;
		}
		else if (m_spawnCount == 1 && yomogi2 == nullptr)
		{
			m_spawnCount = 0;
			m_Timer = 0.0f;
			m_stageState = 23;
		}
		break;
	}

	case 23:
	{
		m_Timer += deltaTime;
		if (m_Timer >= 4.0f)
		{
			m_Timer = 0.0f;
			m_stageState = 24;
		}
		break;
	}

	case 24:
	{
		Sakuran* sakuran3 = NewGO<Sakuran>(0, "Sakuran3");
		sakuran3->Init(50.0f, 223.0f);

		m_stageState = 25;
		break;
	}

	case 25:
	{
		Yomogi* yomogi3 = FindGO<Yomogi>("Yomogi3");
		if (yomogi3 == nullptr && m_spawnCount == 0)
		{
			Yomogi* newYomogi = NewGO<Yomogi>(0, "Yomogi3");
			newYomogi->Init(50.0f, 223.0f);
			m_spawnCount = 1;
		}
		else if (yomogi3 == nullptr && m_spawnCount == 1)
		{
			m_spawnCount = 0;
			m_stageState = 26;
		}
		break;
	}
	case 26: // 【1面 中ボス】を送って倒されるまで待つ
	{
		H_1Boss* boss = FindGO<H_1Boss>("H_1Boss");
		if (boss == nullptr && m_spawnCount == 0)
		{
			H_1Boss* newBoss = NewGO<H_1Boss>(0, "H_1Boss");
			newBoss->Init(0.0f, 0.0f);

			NewGO<H_1BossHPGage>(0, "1h_hpGage");
			m_spawnCount = 1;
			m_Timer = 0.0f; // ★ ボス出現時のタイマーをリセット！
		}
		else if (m_spawnCount == 1)
		{
			// ボスが存在している間はタイマーを回すか、あるいはボスが生きていた証拠を残す
			if (boss != nullptr)
			{
				m_Timer += deltaTime; // 戦闘経過時間
			}
			// ボスが消えたとき！
			else
			{
				// ★【超重要】ボスが生まれてから「最低でも2秒以上戦闘した」あとに消えた場合のみ、撃破とみなす！
				// （リトライ直後の誤爆なら、ボスが存在する暇もなく即座にここに来るのでタイマーが0のまま弾ける！）
				if (m_Timer >= 2.0f)
				{
					if (FindGO<gameover>("gameover") == nullptr)
					{
						if (FindGO<aclere>("aclere") == nullptr)
						{
							if (auto stage1 = FindGO<Stage1>("Stage1")) { stage1->StopBGM(); DeleteGO(stage1); }
							if (auto noruto = FindGO<Noruto>("Noruto")) { DeleteGO(noruto); }
						
							if (auto boss = FindGO<H_1Boss>("H_1Boss")) { DeleteGO(boss); }
							if (auto bossGage = FindGO<H_1BossHPGage>("1h_hpGage")) { DeleteGO(bossGage); }
							if (auto playerGage = FindGO<PlayerHPGage>("hpGage")) { DeleteGO(playerGage); }
							if (auto scoreUi = FindGO<socreUI>("socreUI")) { DeleteGO(scoreUi); }
							if (auto enemyMgr = FindGO<EnemyManager>("EnemyManager")) { DeleteGO(enemyMgr); }

							// その上でクリア画面を生成する
							NewGO<aclere>(0, "aclere");
							
						}
					}
				}

				m_spawnCount = 0;
				m_stageState = 28;
			}
		}
		break;
	}

	default:
		break;
	}
}