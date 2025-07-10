
class FrameRate
{
public:

	// 開始平均フレームレート
	static constexpr int FRAME_RATE_AVE = 60;

	// テキスト横位置
	static constexpr int TEXT_POS_X = 70;

	// テキスト縦位置
	static constexpr int TEXT_POS_Y = 25;


	/// <summary>
	/// インスタンス生成
	/// </summary>
	static void CreateInstance(void);

	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>フレームレートマネージャ</returns>
	static FrameRate& GetInstance(void);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(void);

	/// <summary>
	/// インスタンス削除処理
	/// </summary>
	void Release(void);

	/// <summary>
	/// フレームレート割り当て
	/// </summary>
	void SetFrameRate(void);

	/// <summary>
	/// フレームレート制限 判定
	/// </summary>
	/// <returns>制御するか否か</returns>
	bool GetLimitFrameRate(void);

	/// <summary>
	/// 平均フレームレート値割り当て
	/// </summary>
	void SetFpsAverage(unsigned int fps);

	/// <summary>
	/// 平均フレームレート値取得
	/// </summary>
	int GetFpsAverage(void);


private:

	// 静的インスタンス
	static FrameRate* instance_;

	// 平均フレームレート値
	unsigned int fpsAverage_;

	// 現在の時間
	int curTime_;

	// 前フレーム実行時間
	int lateTime_;

	// フレームカウンタ
	int counter_;

	// フレーム更新時間
	int updateTime_;

	// フレームレート(描画用)
	float viewFramelate_;


	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	FrameRate(void);

	/// <summary>
	/// デストラクタ(private)
	/// </summary>
	~FrameRate(void) = default;

	/// <summary>
	/// コピーコンストラクタ
	/// </summary>
	FrameRate(FrameRate& other) = default;
};