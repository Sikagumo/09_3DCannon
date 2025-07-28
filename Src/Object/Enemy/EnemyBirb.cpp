#include "EnemyBirb.h"
#include "./EnemyBase.h"
#include "../../Object/AnimationController.h"


EnemyBirb::EnemyBirb(void)
{
}

void EnemyBirb::InitAnim(void)
{
	for (int i = 0; i < static_cast<int>(ANIM_TYPE::MAX); i++)
	{
		animationController_->AddInFbx(i, ANIM_SPEED, i);
	}

	// アニメーションの再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));
}


void EnemyBirb::SetParam(void)
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
}

void EnemyBirb::ChangeStandby(void)
{
	animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));
}

void EnemyBirb::ChangeDeadReact(void)
{
	animationController_->Play(static_cast<int>(ANIM_TYPE::DEATH), false);
}
