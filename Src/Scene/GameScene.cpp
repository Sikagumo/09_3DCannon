#include "GameScene.h"
#include <DxLib.h>
#include <vector>
#include "../Object/Stage.h"
#include "../Object/Cannon.h"


GameScene::GameScene(void)
{
}

void GameScene::Init(void)
{
	stage_ = new Stage();
	stage_->Init();

	cannon_ = new Cannon();
	cannon_->Init();
}

void GameScene::Update(void)
{
	stage_->Update();
	cannon_->Update();

	Collision();
}

void GameScene::Draw(void)
{
	stage_->Draw();
	cannon_->Draw();
}

void GameScene::Release(void)
{
	cannon_->Release();
	delete cannon_;

	stage_->Release();
	delete stage_;
}

void GameScene::Collision(void)
{
	int stageId = stage_->GetModelId();

	std::vector<ShotBase*> shots = cannon_->GetShots();
	for (ShotBase* shot : shots)
	{
		if (!shot->IsCollisionState())
		{
			continue;
		}

		auto info = MV1CollCheck_Sphere(stageId, -1,
										shot->GetPos(), shot->GetCollisionRadius());
		if (info.HitNum > 0)
		{
			shot->Blast();
		}

		// “–‚½‚è”»’èŒ‹‰Êƒ|ƒŠƒSƒ“”z—ñ‚ÌŒãn––‚ğ‚·‚é
		MV1CollResultPolyDimTerminate(info);

	}
}
