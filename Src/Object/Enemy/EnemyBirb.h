#pragma once
#include "./EnemyBase.h"
#include <DxLib.h>

class EnemyBirb : public EnemyBase
{
public:

	static constexpr float SCALE = 0.3f;

	static constexpr float SPEED = 0.25f;

	static constexpr int HP = 2;

	static constexpr VECTOR DEFAULT_ANGLES = { 0.0f, -90.0f * (DX_PI_F / 180.0f), 0.0f};

	static constexpr VECTOR COL_POS_LOCAL = { 0.0f, 50.0f, 0.0f};

	static constexpr float COL_RADIUS = 35.0f;


	// コンストラクタ
	EnemyBirb(void);

	// デストラクタ
	~EnemyBirb(void) = default;


protected:

	void SetParam(void) override;

	// 状態遷移
	//void ChangeStandby(void) override;
	//void ChangeDeadReact(void) override;
	//void ChangeEnd(void) override;

	// 状態別更新
	//void UpdateStandby(void) override;
	//void UpdateDeadReact(void) override;
	//void UpdateEnd(void) override;

};
