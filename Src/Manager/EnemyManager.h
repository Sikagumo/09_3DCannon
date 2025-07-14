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


private:

	// エネミー用のモデルハンドルID
	std::vector<int> enemyModelIds_;

	// エネミー
	std::vector<EnemyBase*> enemys_;

	// 出現間隔
	int cntSpawn_;

};