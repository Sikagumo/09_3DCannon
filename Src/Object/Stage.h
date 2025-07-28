#pragma once
#include <DxLib.h>

class Stage
{
public:

	// コンストラクタ
	Stage(void);

	// デストラクタ
	~Stage(void) = default;

	void Init(void);

	void Update(void);

	void Draw(void);

	void Release(void);

	/// <summary>
	/// ステージのモデルを取得
	/// </summary>
	int GetModelId(void);

	/// <summary>
	/// ダメージ時有効処理
	/// </summary>
	void SetDamage(void);

private:

	static constexpr COLOR_F TOWER_DAMAGE_DIF = { 50.0f, 0,0,1.0f };
	// 城のフレーム番号
	static constexpr int TOWER_FRAME_NUM = 72;

	// ダメージ時の色変更時間
	static constexpr float COLOR_TIME = 1.0f;

	// 点滅間隔
	static constexpr int COLOR_TEAM = 2;


	// ３ＤモデルのハンドルID
	int modelId_;

	// 背景モデルID
	int modelIdBack_;

	// 背景画像ID
	int imageBackId_;

	// 色変更時間
	float colorTime_;
};
