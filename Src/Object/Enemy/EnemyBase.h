#pragma once
#include <vector>
#include <DxLib.h>
class AnimationController;


class EnemyBase
{
public:

	// エネミー種別
	enum class TYPE
	{
		BIRB,
		MAX,
	};

	// 状態
	enum class STATE
	{
		NONE,
		STANDBY,
		DEAD_REACT,
		END,
	};

	// アニメーション種別
	enum class ANIM_TYPE
	{
		DEATH,
		DUCK,
		HIT_REACT,
		IDLE,
		JUMP,
		JUMP_IDLE,
		JUMP_LAND,
		NO,
		PUNCH,
		RUN,
		WALK,
		WAVE,
		WEAPON,
		YES,
		MAX,
	};


	// コンストラクタ
	EnemyBase(void);

	// デストラクタ
	virtual ~EnemyBase(void) = default;

	// 初期処理
	void Init(TYPE type, int baseModelId);

	// 更新処理
	void Update(void);

	// 描画処理
	void Draw(void);

	// 解放処理
	void Release(void);


	// 状態遷移
	void ChangeState(STATE state);

	// 座標取得
	VECTOR GetPos(void)const;

	// 衝突判定用半径
	float GetCollisionRadius(void)const;

	// 衝突判定用調整後座標取得
	VECTOR GetCollisionPos(void)const;

	// ダメージを与える
	void Damage(int damage = 1);

	// 衝突判定が有効な状態
	bool IsCollisionState(void)const;

	/// <summary>
	/// 非表示化
	/// </summary>
	void SetInactive(void);


protected:

	// 無敵時間
	static constexpr float INV_TIME = 1.5f;

	// 通常色
	static constexpr COLOR_F COLOR_DEFAULT = { 1.0f, 1.0f, 1.0f, 1.0f };

	// ダメージ色
	static constexpr COLOR_F COLOR_DAMAGE = { 125.0f, 0.0f, 0.0f, 1.0f };

	// 色変化間隔
	static constexpr int DAMAGE_TEAM = 3;

	// アニメーションコントローラ
	AnimationController* animationController_;

	// 種別
	TYPE type_;

	// 状態
	STATE state_;

	// モデルのハンドルID
	int modelId_;

	// 座標
	VECTOR pos_;

	// 角度
	VECTOR angles_;

	// 大きさ
	VECTOR scales_;

	// 移動方向
	VECTOR moveDir_;

	// 移動速度
	float speed_;

	// HP
	int hp_;

	// 無敵時間
	float invTime_;

	// 衝突判定用半径
	float collisionRadius_;
		
	// 衝突判定用の球体中心座標の調整
	VECTOR collisionLocalPos_;


	// パラメータ設定(純粋仮想関数)
	virtual void SetParam(void) = 0;

	// 状態遷移
	virtual void ChangeStandby(void);
	virtual void ChangeDeadReact(void);
	virtual void ChangeEnd(void);

	// 状態別更新
	virtual void UpdateStandby(void);
	virtual void UpdateDeadReact(void);
	virtual void UpdateEnd(void);

	// 状態別描画
	virtual void DrawStandby(void);
	virtual void DrawDeadReact(void);
	virtual void DrawEnd(void);

	// 移動
	void Move(void);
};