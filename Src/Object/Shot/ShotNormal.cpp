#include "ShotNormal.h"
#include "./ShotBase.h"


ShotNormal::ShotNormal(TYPE type, int baseModelId) : ShotBase(type, baseModelId)
{
}

void ShotNormal::SetParam(void)
{
	// ’e‚Ì‘å‚«‚³‚ğİ’è
	scl_ = { SCALE, SCALE, SCALE };

	// ’e‚ÌŠp“x‚ğİ’è
	rot_ = ANGLES;

	// ’e‚Ì‘¬“x
	speed_ = SPEED;

	// ’e‚Ì¶‘¶ŠúŠÔ
	aliveTime_ = ALIVE_TIME;

	// ’e‚Ì”¼Œa
	collisionRadius_ = RADIUS;

}
