#include "Stage.h"
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"


Stage::Stage(void)
{
	colorTime_ = 0.0f;
}


void Stage::Init(void)
{
	// 背景画像ロード
	imageBackId_ = LoadGraph((Application::PATH_IMAGE + "Sky.jpg").c_str());

	// 外部ファイルの３Ｄモデルをロード
	modelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Stage/Stage.mv1").c_str());

	// 背景モデルロード
	modelIdBack_ = MV1LoadModel((Application::PATH_MODEL + "Stage/BackStage.mv1").c_str());

	colorTime_ = 0.0f;

	// 当たり判定割り当て
	MV1SetupCollInfo(modelId_);

	// ３Ｄモデルの大きさを設定(引数は、x, y, zの倍率)
	MV1SetScale(modelId_, { 1.0f, 1.0f, 1.0f });

	// ３Ｄモデルの位置(引数は、３Ｄ座標)
	MV1SetPosition(modelId_, { 0.0f, 0.0f, 0.0f });

	// ３Ｄモデルの向き(引数は、x, y, zの回転量。単位はラジアン。)
	MV1SetRotationXYZ(modelId_, { 0.0f, DX_PI_F, 0.0f });
}

void Stage::Update(void)
{
	float delta = SceneManager::GetInstance().GetDeltaTime();

	if (colorTime_ > 0.0f)
	{
		// 色変更時間減少
		colorTime_ -= delta;
	}
}

void Stage::Draw(void)
{
	/* 画面に描画 */

	COLOR_F color = {1.0f, 1.0f, 1.0f, 1.0f};
	int team = static_cast<int>(colorTime_ * 10.0f);

	DrawGraph(0,0, imageBackId_, false);
	MV1DrawModel(modelIdBack_);


	if (colorTime_ > 0.0f && (team % COLOR_TEAM) == 0)
	{
		color = TOWER_DAMAGE_DIF;
	}

	// ３番のフレームのディフューズカラーを赤にする
	MV1SetFrameDifColorScale(modelId_, TOWER_FRAME_NUM, color);
	MV1DrawModel(modelId_);
}

void Stage::Release(void)
{
	/* メモリから解放 */

	DeleteGraph(imageBackId_);

	MV1DeleteModel(modelId_);

	MV1DeleteModel(modelIdBack_);

}

int Stage::GetModelId(void)
{
	return modelId_;
}

void Stage::SetDamage(void)
{
	colorTime_ = COLOR_TIME;
}
