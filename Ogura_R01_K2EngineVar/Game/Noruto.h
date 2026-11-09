#pragma once
class Noruto :public IGameObject
{
public:
	Noruto();
	~Noruto();
	void Render(RenderContext& rc) override;
	void Update()override;
private:
	ModelRender m_modelRender;

	Quaternion m_rot;

};