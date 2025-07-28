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
#include "../Common/Camera.h"
#include "../Common/HpManager.h"
#include "../Application.h"


GameScene::GameScene(void)
{
	gameOverImage_ = -1;
	gameClearImage_ = -1;
	state_ = STATE::NONE;
}

void GameScene::Init(void)
{
	castleHp_ = CASTLE_HP;

	// ゲームオーバー画像
	gameOverImage_ = LoadGraph((Application::PATH_IMAGE + "GameOver.png").c_str());

	// ゲームクリア画像
	gameClearImage_ = LoadGraph((Application::PATH_IMAGE + "GameClear.png").c_str());

	state_ = STATE::IDLE;

	stage_ = new Stage();
	stage_->Init();

	cannon_ = new Cannon();
	cannon_->Init();

	enemyManager_ = new EnemyManager();
	enemyManager_->Init();

	hpManager_ = new HpManager(CASTLE_HP);
	hpManager_->Init();
}

void GameScene::Update(void)
{
	if (state_ == STATE::IDLE)
	{
		Update_Idle();
	}
	else if (state_ == STATE::GAME_OVER ||
			 state_ == STATE::GAME_CLEAR)
	{
		Update_GameEnd();
	}

	stage_->Update();
	hpManager_->Update();
	enemyManager_->Update();
}

void GameScene::Draw(void)
{
	stage_->Draw();
	cannon_->Draw();
	enemyManager_->Draw();
	hpManager_->Draw();
	
	Draw_UI();
}

void GameScene::Release(void)
{
	/*　メモリ開放処理　*/

	cannon_->Release();
	delete cannon_;

	stage_->Release();
	delete stage_;

	enemyManager_->Release();
	delete enemyManager_;

	hpManager_->Release();
	delete hpManager_;

	// ゲームクリア画像開放
	DeleteGraph(gameClearImage_);

	// ゲームオーバー画像開放
	DeleteGraph(gameOverImage_);
}


void GameScene::Update_Idle(void)
{
	cannon_->Update();

	Collision();

	hpManager_->SetHp(castleHp_);

	if (enemyManager_->IsEndWave())
	{
		// ウェーブ終了時、クリア状態化
		state_ = STATE::GAME_CLEAR;
	}
}

void GameScene::Update_GameEnd(void)
{
	InputManager& input = InputManager::GetInstance();
	SceneManager& scene = SceneManager::GetInstance();

	if (input.KeyIsTrgDown(KEY_INPUT_SPACE))
	{
		// タイトルシーンに遷移
		scene.ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameScene::Draw_UI(void)
{
	int x, y;
	int midX = (Application::SCREEN_SIZE_X / 2);
	int midY = (Application::SCREEN_SIZE_Y / 2);

	if (state_ == STATE::GAME_OVER)
	{
		x = midX - (GAME_OVER_X / 2);
		y = midY - (GAME_OVER_Y / 2);

		// ゲームオーバー画像描画
		DrawGraph(x, y, gameOverImage_, true);
	}
	if (state_ == STATE::GAME_CLEAR)
	{
		x = midX - (GAME_CLEAR_X / 2);
		y = midY - (GAME_CLEAR_Y / 2);

		// ゲームオーバー画像描画
		DrawGraph(x, y, gameClearImage_, true);
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

	Camera& camera = SceneManager::GetInstance().GetCamera();
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
			// 城被ダメージ
			Damage();

			enemy->SetInactive();

			// 振動
			camera.SetShake();
		}
	}
}

void GameScene::Damage(int damage)
{
	// 正の値でダメージを与える
	castleHp_ -= ((damage < 0) ? -damage : damage);

	// 城の色変更
	stage_->SetDamage();

	if (castleHp_ <= 0)
	{
		castleHp_ = 0;
		// ゲームオーバー化
		state_ = STATE::GAME_OVER;
	}
}