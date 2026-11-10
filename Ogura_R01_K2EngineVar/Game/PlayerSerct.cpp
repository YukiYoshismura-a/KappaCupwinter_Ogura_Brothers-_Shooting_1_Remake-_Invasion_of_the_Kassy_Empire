#include "stdafx.h"
#include "PlayerSerct.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
#include"title.h"
#include"GameCamera.h"
#include "Stage1.h"
#include"Noruto.h"

 PlayerSerct ::PlayerSerct()
{
	S_Noruto.Init("Assets/image/Noruto.dds", 724.0f, 1020.0f);
	//a晩完成したら変える
	S_Ogurano.Init("Assets/image/Noruto.dds", 724.0f,1020.0f);

	S_Noruto.SetPosition(Vector3(-550.0f, 0.0f, 0.0f));
	S_Ogurano.SetPosition(Vector3(550.0f, 0.0f, 0.0f));

	S_Noruto.Update();
	S_Ogurano.Update();
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
		 S_Noruto.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		 S_Noruto.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		 S_Ogurano.SetScale(Vector3(0.7f, 0.7f, 1.0f));
		 S_Ogurano.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));

		 // 乗留斗選択状態でAボタンが押されたとき
		 if (g_pad[0]->IsTrigger(enButtonA))
		 {
			 title* titleobje = FindGO<title>("title");
			 if (titleobje != nullptr)
			 {
				 DeleteGO(titleobje);
			 }

			 NewGO<Stage1>(0, "Stage1");
			 NewGO<Noruto>(0, "Noruto");
			 NewGO<GameCamera>(0, "GameCamera");

			 DeleteGO(this);
			 return;
		 }
	 }
	 else if (select == 1)
	 {
		 S_Ogurano.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		 S_Ogurano.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		 S_Noruto.SetScale(Vector3(0.7f, 0.7f, 1.0f));
		 S_Noruto.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));

		 // 大倉野選択状態でAボタンが押されたとき
		 if (g_pad[0]->IsTrigger(enButtonA))
		 {
			 title* titleobje = FindGO<title>("title");
			 if (titleobje != nullptr)
			 {
				 DeleteGO(titleobje);
			 }

			 NewGO<Stage1>(0, "Stage1");
			 NewGO<Noruto>(0, "Noruto");
			 NewGO<GameCamera>(0, "GameCamera");

			 DeleteGO(this);
			 return;
		 }
	 }

	 S_Noruto.Update();
	 S_Ogurano.Update();
 }

void PlayerSerct::Render(RenderContext& rc)
{
	S_Noruto.Draw(rc);
	S_Ogurano.Draw(rc);
}