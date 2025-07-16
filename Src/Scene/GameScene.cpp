#include "GameScene.h"
#include <DxLib.h>
#include <vector>
#include "../Object/Stage.h"
#include "../Object/Cannon.h"
#include "../Object/Shot/ShotBase.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Manager/EnemyManager.h"
#include "../Utility/AsoUtility.h"


GameScene::GameScene(void)
{
}

void GameScene::Init(void)
{
	stage_ = new Stage();
	stage_->Init();

	cannon_ = new Cannon();
	cannon_->Init();

	enemyManager_ = new EnemyManager();
	enemyManager_->Init();
}

void GameScene::Update(void)
{
	stage_->Update();
	cannon_->Update();
	enemyManager_->Update();

	Collision();
}

void GameScene::Draw(void)
{
	stage_->Draw();
	cannon_->Draw();
	enemyManager_->Draw();
}

void GameScene::Release(void)
{
	cannon_->Release();
	delete cannon_;

	stage_->Release();
	delete stage_;

	enemyManager_->Release();
	delete enemyManager_;
}

void GameScene::Collision(void)
{
	Collision_ShotAndStage();

	Collision_ShotAndEnemy();
}

void GameScene::Collision_ShotAndStage(void)
{
	/* ステージと弾の当たり判定 */
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
			shot->Blast(ShotBase::EFFECT_TYPE::GROUND);
		}

		// 当たり判定結果ポリゴン配列の後始末をする
		MV1CollResultPolyDimTerminate(info);
	}
}

void GameScene::Collision_ShotAndEnemy(void)
{
	/* ステージと弾の当たり判定 */
	std::vector<EnemyBase*> enemys = enemyManager_->GetEnemys();
	std::vector<ShotBase*> shots = cannon_->GetShots();

	for (ShotBase* shot : shots)
	{
		if (!shot->IsCollisionState())
		{
			continue;
		}

		for (EnemyBase* enemy : enemys)
		{
			if (!enemy->IsCollisionState())
			{
				continue;
			}

			if (AsoUtility::IsHitSpheres(shot->GetPos(), shot->GetCollisionRadius(),
										 enemy->GetCollisionPos(), enemy->GetCollisionRadius()))
			{
				enemy->Damage();

				shot->Blast(ShotBase::EFFECT_TYPE::HIT);
			}
		}
	}
}
