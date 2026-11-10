#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
	::g_camera3D->SetNear(1.0f);
	::g_camera3D->SetFar(10000.0f);
}

GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{

	return true;
}

void GameCamera::Update()
{
	// ステージの固定された中心座標を基準にする
	Vector3 stageCenter = Vector3(0.0f, 0.0f, 0.0f);

	// 注視点をステージの中心に固定
	::g_camera3D->SetTarget(stageCenter);

	// カメラの位置を「ものすごく高い位置」に配置する
	// 高くすればするほど、遠近感（パース）が消えて正射影に近づきます
	Vector3 cameraPos = stageCenter;
	cameraPos.y += 10000.0f; // 高さを十分に上げる
	cameraPos.z = 0.0f;
	::g_camera3D->SetPosition(cameraPos);

	// 画面の上方向を固定
	::g_camera3D->SetUp(Vector3::AxisZ);

	// 近平面・遠平面の設定
	::g_camera3D->SetNear(1.0f);
	::g_camera3D->SetFar(10000.0f);

	// ★画角（ViewAngle）を極限まで小さくする
	// 画角を狭くすることで、画面の端に行ってもキャラクターが一切曲がらなくなる
	float angle = 2.0f * (3.14159265f / 180.0f); // 度をラジアンに変換
	::g_camera3D->SetViewAngle(angle);
}
