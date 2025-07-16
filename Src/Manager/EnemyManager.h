#pragma once
#include <vector>
class EnemyBase;

class EnemyManager
{
public:

	// 敵の出現間隔
	static constexpr int SPAWN_INTERVAL = 300;


	EnemyManager(void);

	~EnemyManager(void) = default;

	void Init(void);

	void Update(void);

	void Draw(void);

	void Release(void);

	// エネミーの取得
	const std::vector<EnemyBase*>& GetEnemys(void) const;


private:

	// エネミー用のモデルハンドルID
	std::vector<int> enemyModelIds_;

	// エネミー
	std::vector<EnemyBase*> enemys_;

	// 出現間隔
	int cntSpawn_;

	/// <summary>
	/// 敵モデル描画
	/// </summary>
	void LoadEnemyModel(void);
};