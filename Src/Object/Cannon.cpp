#include "Cannon.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "./Shot/ShotBase.h"
#include "./Shot/ShotNormal.h"



void Cannon::Init(void)
{
	standId_ = MV1LoadModel((Application::PATH_MODEL + "Cannon/Stand.mv1").c_str());
	barrelId_ = MV1LoadModel((Application::PATH_MODEL + "Cannon/Barrel.mv1").c_str());

	// 弾のモデル
	shotModelId_ = MV1LoadModel((Application::PATH_MODEL + "Cannon/Shot.mv1").c_str());
	shotSpecialModelId_ = MV1LoadModel((Application::PATH_MODEL + "Cannon/SpikeShot.mv1").c_str());

	// 爆破エフェクトのロード
	effectIdRes_ = LoadEffekseerEffect((Application::PATH_EFFECT + "Blast/Blast.efkefc").c_str());


	standPos_ = STAND_POS;

	// 大砲ローカル座標
	barrelLocalPos_ = BARREL_POS;

	// 大砲グローバル座標
	barrelPos_ = VAdd(barrelLocalPos_, standPos_);

	standRot_ = STAND_ANGLES;
	barrelRot_ = VAdd(standRot_, BARREL_ANGLES);

	// 弾発射の硬直時間
	stepShotDelay_ = 0.0f;

	MV1SetScale(standId_, { STAND_SCALE, STAND_SCALE, STAND_SCALE });
	MV1SetScale(barrelId_, { BARREL_SCALE, BARREL_SCALE, BARREL_SCALE });

	MV1SetPosition(standId_, standPos_);
	MV1SetPosition(barrelId_, barrelPos_);

	Update();
}

void Cannon::Update(void)
{
	RotationProc();

	// 発射操作
	ProcessShot();

	// 弾の更新
	UpdateShot();
}

void Cannon::Draw(void)
{
//	MV1DrawModel(standId_);
// 	MV1DrawModel(barrelId_);

	// 弾の描画
	DrawShot();


#ifdef _DEBUG

	// 弾の発射位置
	VECTOR pos = barrelPos_;

	// 砲身からの相対座標
	VECTOR localPos = { 0.0f, 25.0f, 30.0f };

	// 砲身の回転行列
	MATRIX matRot = MGetIdent();
	matRot = MMult(matRot, MGetRotX(barrelRot_.x));
	matRot = MMult(matRot, MGetRotY(barrelRot_.y));
	matRot = MMult(matRot, MGetRotZ(barrelRot_.z));

	// 方向と同じ要領で、相対座標を回転
	VECTOR localPosRot = VTransform(localPos, matRot);

	// ローカル座標からワールド座標へ変換
	pos = VAdd(pos, localPosRot);

	// 弾の発射位置目安
	DrawSphere3D(pos, 10.0f, 10, 0x00ff00, 0x00ff00, true);

	// 砲台のモデル描画
	MV1DrawModel(standId_);

	// 砲身のモデル描画(一時的に半透明にする)
	MV1SetMaterialDifColor(barrelId_, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.5f));

	MV1DrawModel(barrelId_);


	DrawFormatString(0, 0, 0xFF0000, "standRot:(%.1f°, %.1f°, %.1f°), barrelRot:(%.1f°, %.1f°, %.1f°)",
					 AsoUtility::Rad2DegF(standRot_.x), AsoUtility::Rad2DegF(standRot_.y), AsoUtility::Rad2DegF(standRot_.z),
					 AsoUtility::Rad2DegF(barrelRot_.x), AsoUtility::Rad2DegF(barrelRot_.y), AsoUtility::Rad2DegF(barrelRot_.z));
#endif
}

void Cannon::Release(void)
{
	// 爆破エフェクトの解放
	int i = DeleteEffekseerEffect(effectIdRes_);

	// 砲台モデルの解放
	MV1DeleteModel(barrelId_);
	MV1DeleteModel(standId_);

	// 弾モデルの解放
	MV1DeleteModel(shotSpecialModelId_);
	MV1DeleteModel(shotModelId_);

	for (ShotBase* shot : shots_)
	{
		shot->Release();
		delete shot;
	}

}

std::vector<ShotBase*> Cannon::GetShots(void)
{
	return shots_	;
}


void Cannon::RotationProc(void)
{
	InputManager& input = InputManager::GetInstance();

	VECTOR rot = {};
	float speedX = ROT_SPEED_X;
	float speedY = ROT_SPEED_Y;

	if (input.KeyIsNew(KEY_INPUT_LSHIFT) || input.KeyIsNew(KEY_INPUT_RSHIFT))
	{
		speedX *= ROT_SPEED_UP;
		speedY *= ROT_SPEED_UP;
	}

	if (input.KeyIsNew(KEY_INPUT_A) || input.KeyIsNew(KEY_INPUT_LEFT))
	{
		standRot_.y -= speedY;
		if (standRot_.y < ROT_Y_MIN)
		{
			standRot_.y = ROT_Y_MIN;
		}
	}
	if (input.KeyIsNew(KEY_INPUT_D) || input.KeyIsNew(KEY_INPUT_RIGHT))
	{
		standRot_.y += speedY;
		if (standRot_.y > ROT_Y_MAX)
		{
			standRot_.y = ROT_Y_MAX;
		}
	}

	if (input.KeyIsNew(KEY_INPUT_W) || input.KeyIsNew(KEY_INPUT_UP))
	{
		barrelRot_.x += speedX;
		if (barrelRot_.x > ROT_X_MAX)
		{
			barrelRot_.x = ROT_X_MAX;
		}
	}
	if (input.KeyIsNew(KEY_INPUT_S) || input.KeyIsNew(KEY_INPUT_DOWN))
	{
		barrelRot_.x -= speedX;
		if (barrelRot_.x < ROT_X_MIN)
		{
			barrelRot_.x = ROT_X_MIN;
		}
	}

	// 土台のY軸回転を大砲のY軸に反映する
	barrelRot_.y = standRot_.y;

	// 回転を反映
	MV1SetRotationXYZ(standId_, standRot_);
	MV1SetRotationXYZ(barrelId_, barrelRot_);

}

void Cannon::ProcessShot(void)
{
	auto& ins = InputManager::GetInstance();
	VECTOR forward = { 0.0f, 0.0f, 1.0f };

	// 攻撃キーを押すと、弾を生成
	if (stepShotDelay_ <= 0.0f)
	{
		if (ins.KeyIsNew(KEY_INPUT_Z) ||
			ins.KeyIsNew(KEY_INPUT_SPACE))
		{
			// 有効な弾を取得する
			ShotBase* shot = GetValidShot(ShotBase::TYPE::NORMAL);

			// 単位行列
			MATRIX matRot = MGetIdent();

			// 各軸の行列を作り、行列を合成する
			matRot = MMult(matRot, MGetRotX(barrelRot_.x));
			matRot = MMult(matRot, MGetRotY(barrelRot_.y));
			matRot = MMult(matRot, MGetRotZ(barrelRot_.z));

			// X軸の行列
			MATRIX xMat = MGetRotX(barrelRot_.x);
			MATRIX yMat = MGetRotX(barrelRot_.y);

			// 回転行列同士を合成
			MATRIX mixA = MMult(xMat, yMat);
			MATRIX mixB = MMult(yMat, xMat);


			// 回転行列を使用して、ベクトルを回転する
			shotDir_ = VTransform(forward, matRot);

			// 発射位置を調整
			VECTOR shotPos = VAdd(barrelPos_, SHOT_POS);

			// 弾を生成(方向は仮で正面方向)
			shot->CreateShot(shotPos, shotDir_);

			// 弾発射後の硬直時間セット
			stepShotDelay_ = SHOT_DELAY;
		}
	}

	// 弾発射後の硬直時間を減らしていく
	if (stepShotDelay_ > 0.0f)
	{
		stepShotDelay_ -= SceneManager::GetInstance().GetDeltaTime();
	}
}

void Cannon::UpdateShot(void)
{
	size_t size = shots_.size();
	for (int i = 0; i < size; i++)
	{
		if (!shots_[i]->IsAlive())
		{
			continue;
		}

		// 更新処理
		shots_[i]->Update();
	}
}

void Cannon::DrawShot(void)
{
	size_t size = shots_.size();
	for (int i = 0; i < size; i++)
	{
		if (!shots_[i]->IsAlive())
		{
			continue;
		}

		// 描画処理
		shots_[i]->Draw();
	}
}


ShotBase* Cannon::GetValidShot(ShotBase::TYPE type)
{
	size_t size = shots_.size();

	for (int i = 0; i < size; i++)
	{
		// 未使用(生存していない)で、かつ、弾の種別が同じ
		if (!shots_[i]->IsAlive() &&
			 shots_[i]->GetType() == type)
		{
			return shots_[i];
		}
	}

	// 新しい弾のインスタンスを生成する
	ShotBase* shot;
	
	if (type == ShotBase::TYPE::NORMAL)
	{
		shot = new ShotNormal(type, shotModelId_, effectIdRes_);
	}

	if (type == ShotBase::TYPE::SPECIAL)
	{
		shot = new ShotNormal(type, shotModelId_, effectIdRes_);
	}

	// 可変長配列に追加
	shots_.push_back(shot);

	return shot;
}
