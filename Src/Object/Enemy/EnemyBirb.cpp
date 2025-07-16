#include "EnemyBirb.h"
#include "./EnemyBase.h"


EnemyBirb::EnemyBirb(void)
{
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
