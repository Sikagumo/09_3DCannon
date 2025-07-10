/* ---------------------
　フレームレート制御処理
 ----------------------- */

#include "FrameRate.h"
#include <DxLib.h>

FrameRate* FrameRate::instance_ = nullptr; // シングルトンインスタンス

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
FrameRate::FrameRate(void)
{
	fpsAverage_ = FRAME_RATE_AVE;

	curTime_ = lateTime_ = 0;

	counter_ = updateTime_ = 0;

	viewFramelate_ = 0;
}

/// <summary>
/// インスタンス生成処理
/// </summary>
void FrameRate::CreateInstance(void)
{
	// インスタンス未生成時に生成する
	if (instance_ == nullptr) instance_ = new FrameRate();
}

/// <summary>
/// 静的インスタンス取得
/// </summary>
/// <returns>フレームレートマネージャ</returns>
FrameRate& FrameRate::GetInstance(void)
{
	return *instance_;
}


/// <summary>
/// 更新処理
/// </summary>
void FrameRate::Update(void)
{
	Sleep(1); // システムに処理を返す。「世界」ッ！時よ止まれ！

	//現在時刻を取得する
	curTime_ = GetNowCount();
}

/// <summary>
/// 描画処理
/// </summary>
void FrameRate::Draw(void)
{
	if (CheckHitKey(KEY_INPUT_TAB))
	{
		// 平均フレームレート 描画
		DrawFormatString(0, 0, 0xFFFFFF, "%.1ffps", viewFramelate_);
	}
}

/// <summary>
/// インスタンス削除処理
/// </summary>
void FrameRate::Release(void)
{
	if (instance_ == nullptr)
	{
		OutputDebugString("\nマネージャが生成されていません。\n");
		return;
	}
	delete instance_;
}


/// <summary>
/// フレームレート割り当て処理
/// </summary>
void FrameRate::SetFrameRate(void)
{
	lateTime_ = curTime_; // 前フレームの時間 割り当て

	counter_++; // フレームカウント増加

	// 現在時間との差分
	int nDifTime = curTime_ - updateTime_;

	if (nDifTime > 1000)
	{
		// フレームレート単位変更(ミリ秒 → 秒)
		float fFrameCount = (float)(counter_ * 1000);

		// 描画フレーム単位 取得
		viewFramelate_ = fFrameCount / nDifTime;

		counter_ = 0; // フレームカウント 初期化

		// フレームレート 更新
		updateTime_ = curTime_;
	}
}

/// <summary>
/// フレームレート制限判定
/// </summary>
/// <returns>制限するか否か</returns>
bool FrameRate::GetLimitFrameRate(void)
{
	/*　フレームレート制限　*/

	// 設定フレームレート(ミリ秒単位)
	float frameRate = (1000 / fpsAverage_);

	if ((curTime_ - lateTime_) >= frameRate)
	{
		return false;
	}

	return true;
}

void FrameRate::SetFpsAverage(unsigned int fps)
{
	fpsAverage_ = fps;
}

int FrameRate::GetFpsAverage(void)
{
	return fpsAverage_;
}
