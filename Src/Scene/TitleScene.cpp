#include "TitleScene.h"
#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Common/Grid.h"


TitleScene::TitleScene(void)
{
	imgTitle_ = -1;
}


void TitleScene::Init(void)
{
	imgTitle_ = LoadGraph((Application::PATH_IMAGE + "Title.png").c_str());

	grid_ = new Grid();
}

void TitleScene::Update(void)
{

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.KeyIsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

}

void TitleScene::Draw(void)
{

	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 - 100,
		1.0f, 0.0, imgTitle_, true);


	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 - 100,
		1.0f, 0.0, imgTitle_, true);

	// グリッド線描画
	grid_->Draw();

#pragma region ３Ｄ設定のお試し
	VECTOR pos;
	VECTOR lightDir = GetLightDirection();
	float pow = 0.05f;

	#pragma region Step1：球体表示(陰影がある)
	pos = { 0.0f, 0.0f, 0.0f }; 
	DrawSphere3D(pos, 60.0f, 10, 0xff0000, 0xff0000, true);
	#pragma endregion

	#pragma region Step2：ライト無効(陰影がなくなる)
	SetUseLighting(false);
	pos = { 0.0f, 0.0f, 0.0f };
	DrawSphere3D(pos, 60.0f, 10, 0xff0000, 0xff0000, true);
	SetUseLighting(true);
	#pragma endregion

	#pragma region Step3：ディレクショナルライトの方向
	// 角度(回転)制御ではなくて、方向制御なので、
	// 意図通りには光の方向が動かないもの
	
	if (CheckHitKey(KEY_INPUT_A)) { lightDir.x -= pow; }
	if (CheckHitKey(KEY_INPUT_D)) { lightDir.x += pow; }
	if (CheckHitKey(KEY_INPUT_W)) { lightDir.y -= pow; }
	if (CheckHitKey(KEY_INPUT_S)) { lightDir.y += pow; }

	SetLightDirection(lightDir);

	// 真ん中の球体
	pos = { 0.0f, 0.0f, 0.0f };
	DrawSphere3D(pos, 60.0f, 10, 0xff0000, 0xff0000, true);

	// 光の反対方向
	VECTOR revLightDir = VScale(lightDir, -1.0f);

	// 光の位置
	pos = VAdd(pos, VScale(revLightDir, 300.0f));
	DrawSphere3D(pos, 30.0f, 10, 0xaaaa00, 0xaaaa00, true);
	DrawLine3D(pos, VAdd(pos, VScale(lightDir, 150.0f)), 0xaaaa00);
#ifdef _DEBUG
	DrawFormatString(20, 20, 0x000000,
	 "光の方向：(%.2f, %.2f, %.2f)", lightDir.x, lightDir.y, lightDir.z);
#endif
	#pragma endregion

	#pragma region Step4：Zバッファ無効(前後関係がおかしくなる)
	SetUseZBuffer3D(false);
	SetWriteZBuffer3D(false);

	pos = { 0.0f, 0.0f, 0.0f };
	DrawSphere3D(pos, 60.0f, 10, 0xff0000, 0xff0000, true);

	pos = { 0.0f, 0.0f, 100.0f };
	DrawSphere3D(pos, 100.0f, 10, 0x00ff00, 0x00ff00, true);

	SetWriteZBuffer3D(true);
	SetUseZBuffer3D(true);
	#pragma endregion

	#pragma region Step5：バックカリング

	// バックカリングを無効にする(ポリゴンの内側を描画しないか否か)
	SetUseBackCulling(true);

	// カメラ位置
	pos = { 0.0f, 500.0f, -500.0f };
	DrawSphere3D(pos, 300.0f, 100, 0xff0000, 0xff0000, true);
	SetUseBackCulling(true);

	// ライトの位置変更
	if (CheckHitKey(KEY_INPUT_A)) { lightDir.x -= pow; }
	if (CheckHitKey(KEY_INPUT_D)) { lightDir.x += pow; }
	if (CheckHitKey(KEY_INPUT_W)) { lightDir.y -= pow; }
	if (CheckHitKey(KEY_INPUT_S)) { lightDir.y += pow; }
	SetLightDirection(lightDir);
	
#ifdef _DEBUG
	DrawFormatString(20, 20, 0xffffff,
	 "光の方向：(%.2f, %.2f, %.2f)", lightDir.x, lightDir.y, lightDir.z);
#endif _DEBUG
	#pragma endregion

#pragma endregion
}

void TitleScene::Release(void)
{
	// グリッド線解放

	delete grid_;

	DeleteGraph(imgTitle_);
}
