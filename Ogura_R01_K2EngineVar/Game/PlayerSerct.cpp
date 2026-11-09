#include "stdafx.h"
#include "PlayerSerct.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
#include"title.h"

 PlayerSerct ::PlayerSerct()
{
	Noruto.Init("Assets/image/Noruto.dds", 724.0f, 1020.0f);
	//a晩完成したら変える
	Ogurano.Init("Assets/image/Noruto.dds", 724.0f,1020.0f);

	Noruto.SetPosition(Vector3(-600.0f, 0.0f, 0.0f));
	Ogurano.SetPosition(Vector3(600.0f, 0.0f, 0.0f));

	Noruto.Update();
	Ogurano.Update();
}

PlayerSerct ::~PlayerSerct()
{


}

void PlayerSerct::Update()
{
	// g_renderingEngine->DisableRaytracing();
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->GetLStickXF() > 0.01f)
	{
		select = 1;
	}
	else if (g_pad[0]->IsTrigger(enButtonLeft) || g_pad[0]->GetLStickXF() < -0.01f)
	{
		select = 0;
	}

	if (select == 0)
	{
		Noruto.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		Noruto.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		Ogurano.SetScale(Vector3(0.7f, 0.7f, 1.0f));
		Ogurano.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));
		

		//ここでA押されたら、Player選ぶ画面に飛ぶ
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			
			title* titleobje = FindGO<title>("title");
			if (titleobje != nullptr)
			{
				DeleteGO(titleobje);
			}
			DeleteGO(this);
			return;
		}
		
	}
	else if(select == 1)
	{
		Ogurano.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		Ogurano.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		Noruto.SetScale(Vector3(0.7f, 0.7f, 1.0f));
		Noruto.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));

		if (g_pad[0]->IsTrigger(enButtonA))
		{
			DeleteGO(this);
		
			return;
		}
	}

	Noruto.Update();
	Ogurano.Update();
}


void PlayerSerct::Render(RenderContext& rc)
{
	Noruto.Draw(rc);
	Ogurano.Draw(rc);
}