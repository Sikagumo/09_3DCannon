#pragma once

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


private:

	// ３ＤモデルのハンドルID
	int modelId_;

	// 背景モデルID
	int modelIdBack_;

	// 背景画像ID
	int imageBackId_;
};
