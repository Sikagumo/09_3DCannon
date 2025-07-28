#pragma once
#include "./EnemyBase.h"
#include <DxLib.h>

class EnemyGhost : public EnemyBase
{
public:

	// アニメーション種別
	enum class ANIM_TYPE
	{
		DEATH,
		FLY,
		FLY_IDLE,
		HEAD_BUTT,
		HIT_REACT,
		NO,
		PUNCH,
		YES,
		MAX,
	};

	static constexpr float ANIM_SPEED = 25.0f;

	static constexpr float SCALE = 0.425f;

	static constexpr float SPEED = 0.01f;

	static constexpr int HP = 2;

	static constexpr VECTOR DEFAULT_ANGLES = { 0.0f, -90.0f * (DX_PI_F / 180.0f), 0.0f };

	static constexpr VECTOR COL_POS_LOCAL = { 0.0f, 50.0f, 0.0f };

	static constexpr float COL_RADIUS = 35.0f;

	static constexpr float MOVE_ACC_X = 0.015f;
	static constexpr float ROT_ACC_Y = 0.25f * (DX_PI_F / 180.0f);


	// コンストラクタ
	EnemyGhost(void);

	// デストラクタ
	~EnemyGhost(void) = default;


protected:

	void InitAnim(void) override;

	void SetParam(void) override;

	// 状態遷移
	void ChangeStandby(void) override;
	void ChangeDeadReact(void) override;
	//void ChangeEnd(void) override;

	// 状態別更新
	//void UpdateStandby(void) override;
	//void UpdateDeadReact(void) override;
	//void UpdateEnd(void) override;

	void Move(void) override;

private:

	float rotUpY_;
	float moveUpX_;
};
