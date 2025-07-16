#include "ShotNormal.h"
#include "./ShotBase.h"


ShotNormal::ShotNormal(TYPE type, int baseModelId)
	: ShotBase(type, baseModelId)
{
}

void ShotNormal::SetParam(void)
{
	// ’e‚Ì‘å‚«‚³‚ğİ’è
	scale_ = { SCALE, SCALE, SCALE };

	// ’e‚ÌŠp“x‚ğİ’è
	angles_ = ANGLES;

	// ’e‚Ì‘¬“x
	speed_ = SPEED;

	// ’e‚Ì¶‘¶ŠúŠÔ
	aliveTime_ = ALIVE_TIME;

	// ’e‚Ì”¼Œa
	collisionRadius_ = RADIUS;

}
