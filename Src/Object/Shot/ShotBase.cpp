#include "ShotBase.h"
#include <EffekseerForDxLib.h>
#include "../../Manager/SceneManager.h"
#include "../../Manager/EffectResManager.h"


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

	// 重力
	gravityPow_ = 0.0f;

	state_ = STATE::SHOT;

	// パラメータ設定
	SetParam();

	// 大きさの設定
	MV1SetScale(modelId_, scale_);


	// 回転の設定
	MV1SetRotationXYZ(modelId_, angles_);

	// 位置の設定
	MV1SetPosition(modelId_, pos_);
}

void ShotBase::Update(void)
{
	if (state_ == STATE::SHOT)
	{
		Update_Shot();
	}
	if (state_ == STATE::BLAST)
	{
		Update_Blast();
	}
}

void ShotBase::Draw(void)
{
	if (!IsAlive())
	{
		// 生存していなければ処理中断
		return;
	}

	MV1DrawModel(modelId_);


#ifdef _DEBUG
	/*
	// デバッグ用：衝突判定用球体
	DrawSphere3D(pos_, collisionRadius_,
				 10, 0x0000ff, 0x0000ff, false);*/
#endif
}

void ShotBase::Release(void)
{
	MV1DeleteModel(modelId_);
}

void ShotBase::Update_Shot(void)
{
	float delta = SceneManager::GetInstance().GetDeltaTime();

	if (!IsAlive())
	{
		// 生存していなければ処理中断
		return;
	}

	// 弾を移動させる
	pos_ = VAdd(pos_, VScale(dir_, speed_));

	// 重力加算
	gravityPow_ += SceneManager::GRAVITY * delta;

	pos_.y -= gravityPow_;


	// 大きさの設定
	MV1SetScale(modelId_, scale_);

	// 角度の設定
	MV1SetRotationXYZ(modelId_, angles_);

	// 位置の設定
	MV1SetPosition(modelId_, pos_);

	// 生存カウンタの減少
	ReduceAliveTime();
}

void ShotBase::Update_Blast(void)
{
	ChangeBlast();

	if (!IsEffekseer3DEffectPlaying(effectIdPlay_))
	{
		isAlive_ = false;
	}
}

void ShotBase::Blast(EFFECT_TYPE type)
{
	effectType_ = type;

	ChangeState(STATE::BLAST);
}

bool ShotBase::IsCollisionState(void)
{
	return (state_ == STATE::SHOT);
}

void ShotBase::ReduceAliveTime(void)
{
	float delta = SceneManager::GetInstance().GetDeltaTime();

	aliveTime_ -= delta;

	if (aliveTime_ < 0.0f)
	{
		isAlive_ = false;
		state_ = STATE::END;
	}
}

void ShotBase::ChangeState(STATE state)
{
	state_ = state;
}

void ShotBase::ChangeBlast(void)
{
	EffectResManager::TYPE type;

	switch (effectType_)
	{
		case ShotBase::EFFECT_TYPE::GROUND:
		{
			type = EffectResManager::TYPE::BLAST_GROUND;
		}
		break;

		case ShotBase::EFFECT_TYPE::HIT:
		{
			type = EffectResManager::TYPE::BLAST_HIT;
		}
		break;

		default:
		break;
	}
		
	// エフェクトの再生
	int resId = EffectResManager::GetInstance().GetResourceId(type);
	effectIdPlay_ = PlayEffekseer3DEffect(resId);


	// エフェクトの大きさ
	float SCALE = 10.0f;
	SetScalePlayingEffekseer3DEffect(
		effectIdPlay_, SCALE, SCALE, SCALE);

	// エフェクトの回転
	VECTOR angles = {};
	SetRotationPlayingEffekseer3DEffect(
		effectIdPlay_, angles.x, angles.y, angles.z);

	// エフェクトの位置
	SetPosPlayingEffekseer3DEffect(
		effectIdPlay_, pos_.x, pos_.y, pos_.z);
}

void ShotBase::ChangeEnd(void)
{
	// エフェクトの停止
	StopEffekseer3DEffect(effectIdPlay_);
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
