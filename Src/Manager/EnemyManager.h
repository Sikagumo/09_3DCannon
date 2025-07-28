#pragma once
#include <vector>
class EnemyBase;

class EnemyManager
{
public:

	enum class WAVE
	{
		FIRST,
		SECOND,
		LAST,
		END
	};

	// 敵の出現間隔
	static constexpr float SPAWN_INTERVAL_01 = 1.5f;
	static constexpr float SPAWN_INTERVAL_02 = 2.5f;

	static constexpr float WAVE_TIME_01 = 15.0f;
	static constexpr float WAVE_TIME_02 = 20.0f;


	EnemyManager(void);

	~EnemyManager(void) = default;

	void Init(void);

	void Update(void);

	void Draw(void);

	void Release(void);

	// エネミーの取得
	const std::vector<EnemyBase*>& GetEnemys(void) const;

	/// <summary>
	/// ウェーブが終了しているか否か
	/// </summary>
	bool IsEndWave(void);


private:

	WAVE wave_;

	// エネミー用のモデルハンドルID
	std::vector<int> enemyModelIds_;

	// エネミー
	std::vector<EnemyBase*> enemys_;

	// 出現間隔
	float spawnTime_;

	float waveTime_;

	/// <summary>
	/// 敵モデル描画
	/// </summary>
	void LoadEnemyModel(void);

	void SpawnEnemy(int type);

	void Update_Waves(void);

	void Update_WaveTime(void);

	void Update_WaveFirst(void);

	void Update_WaveSecond(void);

	void Update_WaveLast(void);
};