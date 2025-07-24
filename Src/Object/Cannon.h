#pragma once
#include <DxLib.h>
#include <vector>
#include "./Shot/ShotBase.h"

class Cannon
{
public:

	enum class TYPE
	{
		NORMAL,
	};

	static constexpr float STAND_SCALE = 0.8f;
	static constexpr VECTOR STAND_ANGLES = { 0.0f, 0.0f, 0.0f };
	static constexpr VECTOR STAND_POS = { 0.0f, 10.0f, -200.0f };

	static constexpr float BARREL_SCALE = 0.8f;
	static constexpr VECTOR BARREL_ANGLES = { 0.0f, 0.0f, 0.0f };
	static constexpr VECTOR BARREL_POS = { 0.0f, 90.0f, -0.0f };

	static constexpr VECTOR SHOT_POS = { 0.0f, 22.5f, 30.0f };


	static constexpr float ROT_SPEED_Y = (1.5f * (DX_PI_F / 180.0f));
	static constexpr float ROT_SPEED_X = (0.85f * (DX_PI_F / 180.0f));

	// 回転速度の一時上昇値
	static constexpr float ROT_SPEED_UP = 1.85f;

	static constexpr float ROT_X_MIN = (-45.0f * (DX_PI_F / 180.0f));
	static constexpr float ROT_X_MAX = (20.0f * (DX_PI_F / 180.0f));
	static constexpr float ROT_Y_MIN = (-75.0f * (DX_PI_F / 180.0f));
	static constexpr float ROT_Y_MAX = (75.0f * (DX_PI_F / 180.0f));

	// 発射間隔
	static constexpr float SHOT_DELAY = 0.5f;


	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Cannon(void) = default;

	/// <summary>
	/// デフォルトデストラクタ
	/// </summary>
	~Cannon(void) = default;

	void Init(void);

	void Update(void);

	void Draw(void);

	void Release(void);

	std::vector<ShotBase*> GetShots(void);


private:

	TYPE shotType_;

	// 土台回転値
	VECTOR standRot_;
	VECTOR standPos_;

	// 砲身グローバル座標
	VECTOR barrelPos_;

	// 砲身ローカル座標
	VECTOR barrelLocalPos_;
	VECTOR barrelRot_;

	// 発射向き
	VECTOR shotDir_;

	// 大砲モデルID
	int barrelId_;

	// 土台モデルID
	int standId_;

	// 爆破エフェクトID
	int effectIdRes_;


	// ショット(ポインタ)
	std::vector<ShotBase*> shots_;

	// 弾のモデルID
	int shotModelId_;

	// 特殊團野モデルID
	int shotSpecialModelId_;

	// 弾発射後の硬直時間計算用
	float stepShotDelay_;


	/// <summary>
	/// 回転処理
	/// </summary>
	void RotationProc(void);

	// 発射操作
	void ProcessShot(void);

	// 弾の更新
	void UpdateShot(void);

	// 弾の描画
	void DrawShot(void);

	/// <summary>
	/// 弾の軌道
	/// </summary>
	/// <param name="shotPos">発射位置</param>
	void DrawShotOrbit(VECTOR& shotPos);

	/// <summary>
	/// 有効な弾を取得する
	/// </summary>
	/// <param name="type"></param>
	ShotBase* GetValidShot(ShotBase::TYPE type);

};