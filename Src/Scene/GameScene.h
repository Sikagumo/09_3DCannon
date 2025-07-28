#pragma once
#include "./SceneBase.h"
#include <DxLib.h>
class Stage;
class Cannon;
class EnemyManager;
class HpManager;

class GameScene : public SceneBase
{
public:

	enum class STATE
	{
		NONE = 0,
		IDLE,
		GAME_OVER,
		GAME_CLEAR,
	};

	// ゲームオーバー画像サイズ
	static constexpr int GAME_OVER_X = 651;
	static constexpr int GAME_OVER_Y = 109;

	// ゲームクリア画像サイズ
	static constexpr int GAME_CLEAR_X = 626;
	static constexpr int GAME_CLEAR_Y = 113;

	// ゲームオーバー位置
	static constexpr VECTOR GAME_OVER_POS = { 450.0f, 30.0f,75.0f };

	// ゲームオーバー半径
	static constexpr float GAME_OVER_RADIUS = 35.0f;

	// 城のHP
	static constexpr int CASTLE_HP = 3;

	// 地面の縦位置
	static constexpr float GROUND_POS_Y = 47.5f;


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

	int castleHp_;

	HpManager* hpManager_;
	// 
	EnemyManager* enemyManager_;

	// ゲームオーバー画像
	int gameOverImage_;

	// ゲームクリア画像
	int gameClearImage_;

	/// <summary>
	/// 有効時の更新処理
	/// </summary>
	void Update_Idle(void);

	/// <summary>
	/// ゲームオーバーの更新処理
	/// </summary>
	void Update_GameEnd(void);
	
	/// <summary>
	/// UI描画処理
	/// </summary>
	void Draw_UI(void);

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

	/// <summary>
	/// 城の被ダメージ処理
	/// </summary>
	/// <param name="damage">ダメージ量</param>
	void Damage(int damage = 1);
};