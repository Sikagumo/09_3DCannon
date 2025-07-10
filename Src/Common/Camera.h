#pragma once
#include <DxLib.h>

class Camera
{
public:

	// カメラモード
	enum class MODE
	{
		NONE,
		FIXED_POINT, // 定点カメラ
		FREE, // フリーモード
	};

	// カメラの初期位置
	static constexpr VECTOR DEFAULT_POS = {0.0f, 400.0f, -500.0f};

	// カメラの初期向き
	static constexpr VECTOR DEFAULT_ANGLES = { 25.0f * (DX_PI_F / 180.0f), 0.0f, 0.0f };

	// カメラの注視点の最も近い位置
	static constexpr float CAMERA_NEAR = 3.0f;
	
	// カメラの注視点の最も遠い位置
	static constexpr float CAMERA_FAR = 5000.0f;


	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Camera(void);

	/// <summary>
	/// デフォルトデストラクタ
	/// </summary>
	~Camera(void) = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(void);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void);

	/// <summary>
	/// 描画前のカメラ設定
	/// </summary>
	void SetBeforeDraw(void);

	/// <summary>
	/// デバッグ描画処理
	/// </summary>
	void DrawDebug(void);

	/// <summary>
	/// メモリ解放処理
	/// </summary>
	void Release(void);

	// カメラモードの変更
	void ChangeMode(MODE mode);


private:

	// カメラモード
	MODE mode_;


	// カメラ位置
	VECTOR pos_;

	// カメラの角度
	VECTOR angles_;

	// カメラモード別の制御処理
	void SetBeforeDrawFixedPoint(void);

	void SetBeforeDrawFree(void);
};