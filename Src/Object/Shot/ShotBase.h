#pragma once
#include <DxLib.h>

class ShotBase
{
public:

	// 弾の種類
	enum class TYPE
	{
		NORMAL,
		SPECIAL,
	};

	// 弾の状態
	enum class STATE
	{
		NONE,
		SHOT,
		BLAST,
		END
	};


	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">弾の種別</param>
	/// <param name="baseModelId">元となるモデルのハンドルID</param>
	ShotBase(TYPE type, int baseModelId);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ShotBase(void) = default;


	// 弾の生成(表示開始座標、弾の進行方向)
	virtual void CreateShot(VECTOR pos, VECTOR dir);

	// 更新ステップ
	virtual void Update(void);

	// 描画
	void Draw(void);

	// 解放処理
	void Release(void);


	// 生存判定
	bool IsAlive(void);

	// 弾の座標
	VECTOR GetPos(void);

	// 弾の衝突判定用半径
	float GetCollisionRadius(void);

	// 弾の種別
	TYPE GetType(void);

	void Blast(void);

	/// <summary>
	/// 当たり判定が有効か否か
	/// </summary>
	bool IsCollisionState(void);


protected:

	// 弾の種別
	TYPE type_;

	STATE state_;

	// 弾のモデルID
	int modelId_;

	// 方向
	VECTOR dir_;

	// 弾の大きさ
	VECTOR scl_;

	// 弾の回転
	VECTOR rot_;

	// 弾の座標
	VECTOR pos_;

	// 弾の移動速度
	float speed_;

	// 弾の生存判定
	bool isAlive_;

	// 弾の生存期間
	float aliveTime_;

	// 弾の衝突判定用半径
	float collisionRadius_;

	// 重力
	float gravityPow_;


	// パラメータ設定
	virtual void SetParam(void) = 0;

	// 弾の生存期間の減少
	void ReduceAliveTime(void);

	void ChangeState(STATE state);

};
