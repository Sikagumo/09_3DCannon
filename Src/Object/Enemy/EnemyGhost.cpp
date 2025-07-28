#include "EnemyGhost.h"
#include "./EnemyBase.h"
#include "../../Object/AnimationController.h"
#include "../../Manager/SceneManager.h"
#include "../../Scene/GameScene.h"


EnemyGhost::EnemyGhost(void)
{
}

void EnemyGhost::InitAnim(void)
{
	for (int i = 0; i < static_cast<int>(ANIM_TYPE::MAX); i++)
	{
		animationController_->AddInFbx(i, ANIM_SPEED, i);
	}

	// アニメーションの再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::FLY));
}

void EnemyGhost::SetParam(void)
{
	// エネミーの大きさを設定
	scales_ = { SCALE, SCALE, SCALE };

	// エネミーの角度を設定
	angles_ = DEFAULT_ANGLES;

	// エネミーの当たり判定のローカル座標
	collisionLocalPos_ = COL_POS_LOCAL;

	// エネミーの当たり判定の半径
	collisionRadius_ = COL_RADIUS;

	// エネミーの移動速度
	speed_ = SPEED;

	// エネミーのHP
	hp_ = HP;

	rotUpY_ = 0.0f;
	moveUpX_ = 0.0f;
}

void EnemyGhost::ChangeStandby(void)
{
	// アニメーションの再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::FLY));
}

void EnemyGhost::ChangeDeadReact(void)
{
	// アニメーションの再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::DEATH), false);
}

void EnemyGhost::Move(void)
{
	float delta = SceneManager::GetInstance().GetDeltaTime();
	
	moveUpX_ += MOVE_ACC_X;
	pos_.x += speed_ + moveUpX_;

	rotUpY_ += ROT_ACC_Y;
	angles_.y += rotUpY_;




	// モデルの座標を設定する
	MV1SetPosition(modelId_, pos_);

	MV1SetRotationXYZ(modelId_, angles_);
}