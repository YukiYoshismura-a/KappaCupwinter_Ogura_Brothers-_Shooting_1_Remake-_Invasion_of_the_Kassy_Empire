#pragma once

#include "Level3DRender/LevelRender.h"

class Player;


class Game : public IGameObject
{
public:
	Game();
	~Game();
	

	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender play;
	SpriteRender info;
	Vector3 m_pos;
	
	

	int select = 0;
};

