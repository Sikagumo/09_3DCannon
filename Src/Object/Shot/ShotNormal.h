#pragma once
#include "./ShotBase.h"
#include <DxLib.h>

class ShotNormal : public ShotBase
{
public:

	static constexpr float SCALE = 0.8f;
	static constexpr VECTOR ANGLES = { 0.0f, 0.0f, 0.0f };
	static constexpr float SPEED = 7.5f;
	static constexpr float ALIVE_TIME = 3.0f;
	static constexpr float RADIUS = 30.0f;

	// コンストラクタ(元となるモデルのハンドルID)
	ShotNormal(TYPE type, int baseModelId);

	// デストラクタ
	~ShotNormal(void) = default;


private:

	// パラメータ設定
	void SetParam(void) override;
};
