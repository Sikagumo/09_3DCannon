#include "EnemyBase.h"
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../AnimationController.h"


EnemyBase::EnemyBase(void)
{
}


void EnemyBase::Init(TYPE type, int baseModelId)
{
	// エネミー種別
	type_ = type;

	// モデルのロード
	modelId_ = MV1DuplicateModel(baseModelId);

	// 角度の設定
	// メンバ変数 angles_ を使用して、右向きに設定すること！
	// 位置の設定
	pos_ = { -350.0f, 30.0f, 75.0f };

	// 移動方向
	moveDir_ = { 1.0f, 0.0f, 0.0f };

	// パラメータ設定
	SetParam();

	// 大きさ
	MV1SetScale(modelId_, scales_);

	// 角度
	MV1SetRotationXYZ(modelId_, angles_);
	
	// 位置
	//MV1SetPosition(modelId_, pos_);

	// アニメーションの設定
	animationController_ = new AnimationController(modelId_);

	for (int i = 0; i < static_cast<int>(ANIM_TYPE::MAX); i++)
	{
		animationController_->AddInFbx(i, 30.0f, i);
	}

	// アニメーションの再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));

	// 初期状態
	ChangeState(STATE::STANDBY);
}

void EnemyBase::Update(void)
{
	switch (state_)
	{
		case EnemyBase::STATE::STANDBY:
		{
			UpdateStandby();
		}
		break;

		case EnemyBase::STATE::DEAD_REACT:
		{
			UpdateDeadReact();
		}
		break;

		case EnemyBase::STATE::END:
		{
			UpdateEnd();
		}
		break;
	}

	// アニメーションの更新
	animationController_->Update();
}

void EnemyBase::Draw(void)
{
	switch (state_)
	{

		case EnemyBase::STATE::STANDBY:
		{
			DrawStandby();
		}
		break;

		case EnemyBase::STATE::DEAD_REACT:
		{
			DrawDeadReact();
		}
		break;

		case EnemyBase::STATE::END:
		{
			DrawEnd();
		}
		break;
	}
}

void EnemyBase::Release(void)
{
	// モデルの解放
	MV1DeleteModel(modelId_);

	// アニメーションコントローラの解放
	animationController_->Release();
	delete animationController_;
}


void EnemyBase::ChangeState(STATE state)
{
	state_ = state;
	switch (state_)
	{
		case EnemyBase::STATE::STANDBY:
		{
			ChangeStandby();
		}
		break;

		case EnemyBase::STATE::DEAD_REACT:
		{
			ChangeDeadReact();
		}
		break;

		case EnemyBase::STATE::END:
		{
			ChangeEnd();
		}
		break;
	}
}

VECTOR EnemyBase::GetPos(void)const
{
	return pos_;
}

float EnemyBase::GetCollisionRadius(void)const
{
	return collisionRadius_;
}

VECTOR EnemyBase::GetCollisionPos(void)const
{
	VECTOR pos = VAdd(pos_, collisionLocalPos_);
	return pos;
}

void EnemyBase::Damage(int damage)
{
	// ダメージが負の時は正に直してHPを減らす
	hp_ -= (damage < 0 ? -damage : damage);

	if (hp_ <= 0)
	{
		hp_ = 0;
		ChangeState(STATE::DEAD_REACT);
	}
}

bool EnemyBase::IsCollisionState(void)const
{
	return (state_ == STATE::STANDBY);
}


void EnemyBase::ChangeStandby(void)
{
	animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));
}

void EnemyBase::ChangeDeadReact(void)
{
	animationController_->Play(static_cast<int>(ANIM_TYPE::DEATH), false);
}

void EnemyBase::ChangeEnd(void)
{
}


void EnemyBase::UpdateStandby(void)
{
	// プレイヤーの方向へ移動
	Move();
}

void EnemyBase::UpdateDeadReact(void)
{
	if (animationController_->IsEnd())
	{
		ChangeState(STATE::END);
	}
}

void EnemyBase::UpdateEnd(void)
{
}


void EnemyBase::DrawStandby(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
}

void EnemyBase::DrawDeadReact(void)
{
	MV1DrawModel(modelId_);
}

void EnemyBase::DrawEnd(void)
{
}


void EnemyBase::Move(void)
{
	// 右に移動
	pos_ = VAdd(pos_, { speed_, 0.0f, 0.0f });

	// モデルの座標を設定する
	MV1SetPosition(modelId_, pos_);
}
