#include "ShotBase.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/SceneManager.h"

ShotBase::ShotBase(TYPE type, int baseModelId)
{
	// 使用メモリ容量と読み込み時間の削減のため
	// モデルデータをいくつもメモリ上に存在させない
	// CreateShotで処理してしまうと、再利用する度にモデルが複製され、
	// Releaseもされない状況になってしまう
	modelId_ = MV1DuplicateModel(baseModelId);
	type_ = type;
}


void ShotBase::CreateShot(VECTOR pos, VECTOR dir)
{
	// 弾の発射位置を設定
	pos_ = pos;

	// 弾の発射方向の設定
	dir_ = dir;

	// 弾の生存判定
	isAlive_ = true;

	// パラメータ設定
	SetParam();

	// 大きさの設定
	MV1SetScale(modelId_, scl_);


	// 回転の設定
	MV1SetRotationXYZ(modelId_, rot_);

	// 位置の設定
	MV1SetPosition(modelId_, pos_);
}

void ShotBase::Update(void)
{
	if (!IsAlive())
	{
		// 生存していなければ処理中断
		return;
	}

	// 弾を移動させる
	pos_ = VAdd(pos_, VScale(dir_, speed_));

	// 大きさの設定
	MV1SetScale(modelId_, scl_);

	// 角度の設定
	MV1SetRotationXYZ(modelId_, rot_);
	
	// 位置の設定
	MV1SetPosition(modelId_, pos_);

	// 生存カウンタの減少
	ReduceAliveTime();
}

void ShotBase::Draw(void)
{
	if (!IsAlive())
	{
		// 生存していなければ処理中断
		return;
	}

	MV1DrawModel(modelId_);
}

void ShotBase::Release(void)
{
	MV1DeleteModel(modelId_);
}


bool ShotBase::IsAlive(void)
{
	return isAlive_;
}

VECTOR ShotBase::GetPos(void)
{
	return pos_;
}

float ShotBase::GetCollisionRadius(void)
{
	return collisionRadius_;
}

ShotBase::TYPE ShotBase::GetType(void)
{
	return type_;
}

void ShotBase::ReduceAliveTime(void)
{
	float delta = SceneManager::GetInstance().GetDeltaTime();

	aliveTime_ -= delta;

	if (aliveTime_ < 0.0f)
	{
		isAlive_ = false;
	}
}