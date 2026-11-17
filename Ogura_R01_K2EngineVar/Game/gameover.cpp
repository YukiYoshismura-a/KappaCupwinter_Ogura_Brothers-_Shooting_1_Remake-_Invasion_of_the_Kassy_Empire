#include "stdafx.h"
#include "gameover.h"
#include "Noruto.h"
#include "Norutodan.h"
#include "Yomogi.h"
#include "Sakuran.h"    
#include "H_1Boss.h"
#include "H_1BossHPGage.h"
#include "PlayerHPGage.h"
#include "socreUI.h"
#include "EnemyManager.h"
#include "Stage1.h"
#include "Game.h"
#include "title.h"
#include "sound/SoundEngine.h"
gameover::gameover()
{
    // gameover.cpp のコンストラクタ内
    EnemyManager* enemyMgr = FindGO<EnemyManager>("EnemyManager");
    if (enemyMgr != nullptr) {
        // マネージャーのステートをクリア不能な状態（999など）に強制変更！
        enemyMgr->SetState(999);
    }
    g_soundEngine->ResistWaveFileBank(9, "Assets/sound/BGM/Gameover.wav"); // ※実際のファイル名に合わせてな！

    // ★ ゲームオーバー画面が出た瞬間に再生！
    SoundSource* goSe = NewGO<SoundSource>(0);
    goSe->Init(9);
    goSe->SetVolume(8.0f); // 必要なら音量を大きく！
    goSe->Play(false);


  

    // 2. ボス（H_1Boss）を消す
    H_1Boss* boss = FindGO<H_1Boss>("H_1Boss");
    if (boss != nullptr) {
        DeleteGO(boss);
    }

    // 3. ボスのHPゲージを消す
    H_1BossHPGage* bossGage = FindGO<H_1BossHPGage>("H_1BossHPGage");
    if (bossGage != nullptr) {
        DeleteGO(bossGage);
    }

    // 4. プレイヤーのHPゲージを消す
    PlayerHPGage* playerGage = FindGO<PlayerHPGage>("PlayerHPGage");
    if (playerGage != nullptr) {
        DeleteGO(playerGage);
    }

    // 5. スコアUIを消す
    socreUI* scoreUi = FindGO<socreUI>("socreUI");
    if (scoreUi != nullptr) {
        DeleteGO(scoreUi);
    }

    // 6. エネミーマネージャーを消す

    if (enemyMgr != nullptr) {
        DeleteGO(enemyMgr);
    }

    
    // --- ここまで一掃処理 ---

    // 「GAME OVER」の初期位置セット（スクラッチの演出用）
    m_pos = Vector3(-300.0f, 300.0f, 0.0f);
}

gameover::~gameover()
{
}

bool gameover::Start()
{
    return true;
}

void gameover::Update()
{
    float deltaTime = g_gameTime->GetFrameDeltaTime();

    // スクラッチの「y座標 < 1 まで yを -5 ずつ変える」の動きを再現！
    if (m_pos.y > 1.0f)
    {
        m_pos.y -= 300.0f * deltaTime; // 下にスライド
        if (m_pos.y < 1.0f) {
            m_pos.y = 1.0f; // ピタッと止める
        }
    }
    else
    {
        // 落ち切ったあと「4秒待つ」
        m_fallTimer += deltaTime;
        if (m_fallTimer >= 4.0f)
        {

            Stage1* stage1 = FindGO<Stage1>("Stage1");
            if (stage1 != nullptr)
            {

                DeleteGO(stage1);
            }
            NewGO<title>(0, "title");
            NewGO<Game>(0, "Game");
            DeleteGO(this);
        }
    }
}

void gameover::Render(RenderContext& rc)
{
    // フォントを使って「GAME OVER」の文字を描画する
    m_fontRender.SetText(L"GAME OVER");
    m_fontRender.SetPosition(m_pos);

    // 文字の大きさ
    m_fontRender.SetScale(3.0f);

    // 色の設定（黒色）
    m_fontRender.SetColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));

    m_fontRender.Draw(rc);
}