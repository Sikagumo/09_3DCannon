#include "EnemyManager.h"
#include <DxLib.h>
#include "../Application.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Enemy/EnemyBirb.h"


EnemyManager::EnemyManager(void)
{
}

void EnemyManager::Init(void)
{
	LoadEnemyModel();

	// 最初から出現させる
	cntSpawn_ = SPAWN_INTERVAL - 1;
}
void EnemyManager::LoadEnemyModel(void)
{
	// エネミーモデルのロード
	enemyModelIds_.emplace_back(MV1LoadModel((Application::PATH_MODEL + "Enemy/Birb.mv1").c_str()));
}


void EnemyManager::Update(void)
{
	// 出現カウンタ
	cntSpawn_++;

	// 一定間隔でエネミーを出現させる
	if (cntSpawn_ % SPAWN_INTERVAL == 0)
	{
		EnemyBase* enemy = new EnemyBirb();
		enemy->Init(
			EnemyBase::TYPE::BIRB,
			enemyModelIds_[static_cast<int>(EnemyBase::TYPE::BIRB)]);
			enemys_.emplace_back(enemy);
	}

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

const std::vector<EnemyBase*>& EnemyManager::GetEnemys(void) const
{
	return enemys_;
}
