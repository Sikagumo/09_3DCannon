#pragma once
#include <chrono>
#include <DxLib.h>
class SceneBase;
class Camera;
class Fader;

class SceneManager
{

public:

	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		GAME,
	};

	// 重力
	static constexpr float GRAVITY = 8.91f;

	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static SceneManager& GetInstance(void);

	// 初期化
	void Init(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// リソースの破棄
	void Destroy(void);

	// 状態遷移
	void ChangeScene(SCENE_ID nextId);

	// シーンIDの取得
	SCENE_ID GetSceneID(void);

	// デルタタイムの取得
	float GetDeltaTime(void) const;


	Camera& GetCamera(void) const;

private:

	// 背景色
	static constexpr COLOR_F BACK_COLOR = { 0,139,139 };

	// ライトの向き
	static constexpr VECTOR LIGHT_DIR = { 0.0f, -1.0f, 1.0f };

	static constexpr COLOR_F FOG_COLOR = { 150,150,200 };
	static constexpr float FOG_START = 750.0f;
	static constexpr float FOG_END   = 2000.0f;


	// 静的インスタンス
	static SceneManager* instance_;

	// カメラオブジェクト
	Camera* camera_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// フェード
	Fader* fader_;

	// 各種シーン
	SceneBase* scene_;

	// シーン遷移中判定
	bool isSceneChanging_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;
	

	// ライト位置
	VECTOR pointLightPos_;
	VECTOR pointLight1Pos_;
	VECTOR pointLight2Pos_;

	int pointLight1_;
	int pointLight2_;

	VECTOR spotLightPos_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager(void);

	// コピーコンストラクタも同様
	SceneManager(const SceneManager& instance) = default;

	// デストラクタも同様
	~SceneManager(void) = default;

	// デルタタイムをリセットする
	void ResetDeltaTime(void);

	// シーン遷移
	void DoChangeScene(SCENE_ID sceneId);

	// フェード
	void Fade(void);

	/// <summary>
	///  3Dの初期化処理
	/// </summary>
	void Init3D(void);
};