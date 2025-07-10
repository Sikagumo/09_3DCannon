#pragma once
#include "ShotBase.h"
#include <DxLib.h>

class ShotNormal : public ShotBase
{
public:

	// コンストラクタ(元となるモデルのハンドルID)
	ShotNormal(TYPE type, int baseModelId);

	// デストラクタ
	~ShotNormal(void) = default;


private:

	static constexpr float SCALE = 0.8f;
	static constexpr VECTOR ANGLES = { 0.0f, 0.0f, 0.0f };
	static constexpr float SPEED = 10.0f;

	// パラメータ設定
	void SetParam(void) override;
};
