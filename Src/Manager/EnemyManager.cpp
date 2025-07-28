#include "EnemyManager.h"
#include <DxLib.h>
#include "../Application.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Enemy/EnemyBirb.h"
#include "../Object/Enemy/EnemyGhost.h"
#include "./SceneManager.h"

using ENEMY_TYPE = EnemyBase::TYPE;


EnemyManager::EnemyManager(void)
{
}

void EnemyManager::Init(void)
{
	LoadEnemyModel();

	// 最初から出現させる
	spawnTime_ = 0.0f;
	waveTime_ = WAVE_TIME_01;
}
void EnemyManager::LoadEnemyModel(void)
{
	// エネミーモデルのロード
	enemyModelIds_.emplace_back(MV1LoadModel((Application::PATH_MODEL + "Enemy/Birb.mv1").c_str()));

	enemyModelIds_.emplace_back(MV1LoadModel((Application::PATH_MODEL + "Enemy/Ghost.mv1").c_str()));
}

void EnemyManager::Update(void)
{
	Update_Waves();

	if (enemys_.empty()) return;

	// エネミーの更新
	for (EnemyBase* enemy : enemys_)
	{
 		enemy->Update();
	}
}

void EnemyManager::Draw(void)
{
	// 描画処理
	for (EnemyBase* enemy : enemys_)
	{
		enemy->Draw();
	}
}
void EnemyManager::Release(void)
{
	// インスタンスのメモリ解放処理を書く！
	// ベースとなるモデルのメモリ解放処理を書く！
	for (EnemyBase* enemy : enemys_)
	{
		enemy->Release();
		delete enemy;
	}

	enemys_.clear();
}


void EnemyManager::SpawnEnemy(int type)
{
	EnemyBase* enemy = nullptr;
	ENEMY_TYPE enemyType = static_cast<ENEMY_TYPE>(type);

	if (enemyType == ENEMY_TYPE::BIRB)
	{
		enemy = new EnemyBirb();
	}
	else if (enemyType == ENEMY_TYPE::GHOST)
	{
		enemy = new EnemyGhost();
	}

	enemy->Init(enemyType,
				enemyModelIds_[type]);
	enemys_.emplace_back(enemy);
}

void EnemyManager::Update_Waves(void)
{
	float delta = SceneManager::GetInstance().GetDeltaTime();

	// 出現カウンタ
	spawnTime_ -= delta;

	Update_WaveTime();

	if (wave_ == WAVE::FIRST)
	{
		Update_WaveFirst();
	}
	else if (wave_ == WAVE::SECOND)
	{
		Update_WaveSecond();
	}
	else if (wave_ == WAVE::LAST)
	{
		Update_WaveLast();
	}
}

void EnemyManager::Update_WaveTime(void)
{
	float delta = SceneManager::GetInstance().GetDeltaTime();
	int wave = static_cast<int>(wave_);

	if (wave_ == WAVE::LAST || wave_ == WAVE::END)
	{
		return;
	}

	waveTime_ -= delta;

	if (waveTime_ < 0.0f)
	{
		// ウェーブ変更
		wave++;
		wave_ = static_cast<WAVE>(wave);

		// 生成時間初期化
		spawnTime_ = 0.0f;

		if (wave_ == WAVE::SECOND)
		{
			// ウェーブ時間割り当て
			waveTime_ = WAVE_TIME_02;
		}

	}
}

void EnemyManager::Update_WaveFirst(void)
{
	// 一定間隔でエネミーを出現させる
	int type = static_cast<int>(ENEMY_TYPE::BIRB);

	if (spawnTime_ < 0.0f)
	{
		spawnTime_ = SPAWN_INTERVAL_01;
		SpawnEnemy(type);
	}
}

void EnemyManager::Update_WaveSecond(void)
{
	// 一定間隔でエネミーを出現させる
	int type = static_cast<int>(ENEMY_TYPE::GHOST);

	if (spawnTime_ < 0.0f)
	{
		spawnTime_ = SPAWN_INTERVAL_02;
		SpawnEnemy(type);
	}
}

void EnemyManager::Update_WaveLast(void)
{
	bool allDestroy = true;
	for (auto& enemy : enemys_)
	{
		if (enemy->IsActive())
		{
			allDestroy = false;
			break;
		}
	}

	if (allDestroy)
	{
		wave_ = WAVE::END;
	}
}


const std::vector<EnemyBase*>& EnemyManager::GetEnemys(void) const
{
	return enemys_;
}

bool EnemyManager::IsEndWave(void)
{
	return (wave_ == WAVE::END);
}
