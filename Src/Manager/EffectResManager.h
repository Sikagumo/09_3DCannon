#pragma once
#include <map>

class EffectResManager
{
public:

	// エフェクトの種類
	enum class TYPE
	{
		BLAST_GROUND, // 地面に着弾
		BLAST_HIT,    // 敵に着弾
	};


	/// <summary>
	/// インスタンスの生成
	/// </summary>
	static void CreateInstance(void);

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static EffectResManager& GetInstance(void);


	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(void);

	/// <summary>
	/// リソースの破棄
	/// </summary>
	void Destroy(void);

	/// <summary>
	/// エフェクシアのリソースハンドルを取得
	/// </summary>
	/// <param name="type">取得する対象</param>
	int GetResourceId(TYPE type);


private:

	// 静的インスタンス
	static EffectResManager* instance_;

	// エフェクシアのリソースハンドル
	std::map<TYPE, int> resourceIds_;


	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	EffectResManager(void);

	// コピーコンストラクタも同様
	EffectResManager(const EffectResManager & instance) = default;

	// デストラクタも同様
	~EffectResManager(void) = default;

	/// <summary>
	/// リソースのロード
	/// </summary>
	void Load(void);
};