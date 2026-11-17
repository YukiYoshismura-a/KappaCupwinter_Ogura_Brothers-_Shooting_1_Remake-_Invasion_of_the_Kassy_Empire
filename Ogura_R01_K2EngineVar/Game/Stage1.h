#pragma once

class EnemyManager;
class Stage1 :public IGameObject
{
public:
	Stage1();
	~Stage1();
	void Render(RenderContext& rc) override;
	void Update();
public:
	void StopBGM(); // 追加！
private:
	ModelRender m_modelRender;
	SoundSource* m_stageBgm = nullptr;
};

