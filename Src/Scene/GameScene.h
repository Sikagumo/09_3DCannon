#pragma once
#include "./SceneBase.h"
#include <DxLib.h>
class Stage;
class Cannon;
class EnemyManager;

class GameScene : public SceneBase
{
public:

	enum class STATE
	{
		NONE = 0,
		IDLE,
		GAME_OVER
	};

	// ゲームオーバー画像サイズ
	static constexpr int GAME_OVER_SIZE_X = 651;
	static constexpr int GAME_OVER_SIZE_Y = 109;

	// ゲームオーバー位置
	static constexpr VECTOR GAME_OVER_POS = { 450.0f, 30.0f,75.0f };

	// ゲームオーバー半径
	static constexpr float GAME_OVER_RADIUS = 35.0f;


	GameScene(void);

	~GameScene(void) = default;

	void Init(void);

	void Update(void);

	void Draw(void);

	void Release(void);


private:

	STATE state_;
	
	Stage* stage_;

	Cannon* cannon_;

	// 
	EnemyManager* enemyManager_;

	// ゲームオーバー画像
	int gameOverImage_;

	/// <summary>
	/// 有効時の更新処理
	/// </summary>
	void Update_Idle(void);

	/// <summary>
	/// ゲームオーバーの更新処理
	/// </summary>
	void Update_GameOver(void);
		
	/// <summary>
	/// 当たり判定処理
	/// </summary>
	void Collision(void);

	/// <summary>
	/// 弾とステージの当たり判定
	/// </summary>
	void Collision_ShotAndStage(void);

	/// <summary>
	/// 弾と敵の当たり判定
	/// </summary>
	void Collision_ShotAndEnemy(void);

	/// <summary>
	/// 城と敵の当たり判定
	/// </summary>
	void Collision_CastleAndEnemy(void);
};