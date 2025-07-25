#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "HpManager.h"

HpManager::HpManager(int maxHp)
{
	curHp_ = maxHp_ = maxHp;
}


void HpManager::Init(void)
{
	// ２Ｄ画像のロード
	imgHeart_ = LoadGraph(PATH_HEART.c_str());

	imgHeartLost_ = LoadGraph(PATH_HEART_LOST.c_str());


	for (int i = 0; i < maxHp_; i++)
	{
		// ハート初期化
		HEART heart;
		heart.size = HEART_SIZE;

		int offsetX = ((POS_X_OFFSET * HEART_SIZE) + HEART_OFFSET) * i;
		heart.posX = (POS_X_OFFSET + offsetX);

		// ハートを格納
		heart_.push_back(heart);
	}
}

void HpManager::Update(void)
{
	float delta = SceneManager::GetInstance().GetDeltaTime();

	for (int i = 0; i < heart_.size(); i++)
	{
		// HPサイズが0のとき、ループ終了
		if (heart_[i].size <= 0.0f) break;

		if (i >= curHp_ &&
			heart_[i].size > 0.0f)
		{
			// 画像のサイズ減少処理
			heart_[i].size -= (delta * HEART_SPEED_DEC);

			if (heart_[i].size < 0.0f)
			{
				// 減少制限
				heart_[i].size = 0.0f;
			}
		}
	}
}

void HpManager::Draw(void)
{
	if (heart_.empty()) return;

	for (int i = 0; i < heart_.size(); i++)
	{
		if (heart_[i].size > 0.0f)
		{
			DrawRotaGraph(POS_X + heart_[i].posX, POS_Y,
						  heart_[i].size, 0.0,
						  imgHeart_, true);
		}

		DrawRotaGraph(POS_X + heart_[i].posX, POS_Y,
					  HEART_SIZE, 0.0,
					  imgHeartLost_, true);
	}
}

void HpManager::Release(void)
{
	heart_.clear();

	// ２Ｄ画像のメモリ解放
	DeleteGraph(imgHeart_);
	DeleteGraph(imgHeartLost_);
}

void HpManager::SetHp(int curHp, int maxHp)
{
	if (maxHp > 0)
	{
		maxHp_ = maxHp;
	}
	// 現在HP更新
	curHp_ = curHp;
}
