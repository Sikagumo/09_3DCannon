#include "EnemyBirb.h"
#include "./EnemyBase.h"


void EnemyBirb::SetParam(void)
{
	// エネミーの大きさを設定
	scales_ = { SCALE, SCALE, SCALE };

	// エネミーの角度を設定
	angles_ = DEFAULT_ANGLES;

	// エネミーの移動速度
	speed_ = SPEED;

	// エネミーのHP
	hp_ = HP;
}

void EnemyBirb::ChangeStandby(void)
{

}

void EnemyBirb::ChangeDeadReact(void)
{
}

void EnemyBirb::ChangeEnd(void)
{
}

void EnemyBirb::UpdateStandby(void)
{
}

void EnemyBirb::UpdateDeadReact(void)
{
}

void EnemyBirb::UpdateEnd(void)
{
}
