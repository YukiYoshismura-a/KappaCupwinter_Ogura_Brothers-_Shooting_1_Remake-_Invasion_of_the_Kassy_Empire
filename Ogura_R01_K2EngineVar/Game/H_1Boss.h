#pragma once
class H_1Boss :public IGameObject
{
public:
    H_1Boss();
    ~H_1Boss();
    void Update() override;
    void Render(RenderContext& rc) override;

    void Init(float minX, float maxX);
    void Damage(int pow); // 弾が当たったら呼ばれる

    int GetHP() const { return m_bossHp; } // HPゲージから読めるようにする
    bool IsDead() const { return m_isDead; }
    // H_1Boss.h の public: の中に追加しておくと便利！
    Vector3 GetPosition() const { return m_pos; }

    int GetHp() const { return m_bossHp; }
private:
    int m_bossHp = 1000; // 初期HP 1000
    bool m_isDead = false;
    Vector3 m_pos = Vector3::Zero;
    ModelRender m_modelRender;

    float m_attackTimer = 0.0f;
    float m_damageStopTime = 0.0f;

    int m_bossState = 0;
    float m_moveTimer = 0.0f;
    float m_actionTimer = 0.0f;
    int m_actionStep = 0;

    // H_1Boss.h の private: の中に追加
    int m_bossActionStep = 0;
    int m_repeatCount = 0;    
    Vector3 m_moveDir = Vector3::Zero;
};

