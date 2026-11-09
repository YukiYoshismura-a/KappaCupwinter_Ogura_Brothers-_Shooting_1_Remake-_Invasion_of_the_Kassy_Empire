#pragma once
class Stage1 :public IGameObject
{
public:
	Stage1();
	~Stage1();
	void Render(RenderContext& rc) override;
	void Update();


	ModelRender m_modelRender;
};

