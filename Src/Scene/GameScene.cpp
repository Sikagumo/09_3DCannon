#include "GameScene.h"
#include <DxLib.h>
#include <vector>
#include "../Object/Stage.h"
#include "../Object/Cannon.h"
#include "../Object/Shot/ShotBase.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Manager/EnemyManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Utility/AsoUtility.h"
#include "../Application.h"


GameScene::GameScene(void)
{
	gameOverImage_ = -1;
	state_ = STATE::NONE;
}

void GameScene::Init(void)
{
	// ゲームオーバー画像
	gameOverImage_ = LoadGraph((Application::PATH_IMAGE + "GameOver.png").c_str());

	state_ = STATE::IDLE;

	stage_ = new Stage();
	stage_->Init();

	cannon_ = new Cannon();
	cannon_->Init();

	enemyManager_ = new EnemyManager();
	enemyManager_->Init();
}

void GameScene::Update(void)
{
	if (state_ == STATE::IDLE)
	{
		Update_Idle();
	}
	else if (state_ == STATE::GAME_OVER)
	{
		Update_GameOver();
	}
}

void GameScene::Draw(void)
{
	stage_->Draw();
	cannon_->Draw();
	enemyManager_->Draw();
	if (state_ == STATE::GAME_OVER)
	{
		int x = (Application::SCREEN_SIZE_X / 2) - (GAME_OVER_SIZE_X / 2);
		int y = (Application::SCREEN_SIZE_Y / 2) - (GAME_OVER_SIZE_Y / 2);

		// ゲームオーバー画像描画
		DrawGraph(x, y, gameOverImage_, true);
	}
}

void GameScene::Release(void)
{
	/*　メモリ開放処理　*/

	// ゲームオーバー画像開放
	DeleteGraph(gameOverImage_);

	cannon_->Release();
	delete cannon_;

	stage_->Release();
	delete stage_;

	enemyManager_->Release();
	delete enemyManager_;
}


void GameScene::Update_Idle(void)
{
	stage_->Update();
	cannon_->Update();
	enemyManager_->Update();

	Collision();
}

void GameScene::Update_GameOver(void)
{
	InputManager& input = InputManager::GetInstance();
	SceneManager& scene = SceneManager::GetInstance();

	if (input.KeyIsTrgDown(KEY_INPUT_SPACE))
	{
		// タイトルシーンに遷移
		scene.ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}


void GameScene::Collision(void)
{
	Collision_ShotAndStage();

	Collision_ShotAndEnemy();

	Collision_CastleAndEnemy();
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

void GameScene::Collision_CastleAndEnemy(void)
{
	/* ステージと弾の当たり判定 */
	std::vector<EnemyBase*> enemys = enemyManager_->GetEnemys();

	for (EnemyBase* enemy : enemys)
	{
		if (!enemy->IsCollisionState())
		{
			continue;
		}

		if (AsoUtility::IsHitSpheres(GAME_OVER_POS, GAME_OVER_RADIUS,
			enemy->GetCollisionPos(), enemy->GetCollisionRadius()))
		{
			// ゲームオーバー化
			state_ = STATE::GAME_OVER;
		}
	}
}
