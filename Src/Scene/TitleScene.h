#pragma once
#include "SceneBase.h"
class SceneManager;
class Grid;


class TitleScene : public SceneBase
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene(void);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene(void) = default;

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:

	// 画像
	int imgTitle_;

	// デバッグ用グリッド線
	Grid* grid_;
};
