#include "Camera.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Utility/AsoUtility.h"


Camera::Camera(void)
{
	// DxLibの初期設定では、
	// カメラの位置が x = 320.0f, y = 240.0f, z = (画面のサイズによって変化)、
	// 注視点の位置は x = 320.0f, y = 240.0f, z = 1.0f
	// カメラの上方向は x = 0.0f, y = 1.0f, z = 0.0f
	// 右上位置からZ軸のプラス方向を見るようなカメラ
}


void Camera::Init(void)
{
	pos_ = DEFAULT_POS;
	prePos_ = pos_;
	angles_ = DEFAULT_ANGLES;

	mode_ = MODE::FIXED_POINT;
}

void Camera::Update(void)
{
	Shake();
}

void Camera::SetBeforeDraw(void)
{
	// クリップ距離を設定する(SetDrawScreenでリセットされる)
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

	if (mode_ == MODE::FIXED_POINT)
	{
		SetBeforeDrawFixedPoint();
	}
	else if (mode_ == MODE::FREE)
	{
		SetBeforeDrawFree();
	}


	// カメラの設定(位置と角度による制御)
	SetCameraPositionAndAngle(
		pos_,
		angles_.x,
		angles_.y,
		angles_.z
	);

	// DXライブラリのカメラとEffekseerのカメラを同期する
	Effekseer_Sync3DSetting();
}

void Camera::DrawDebug(void)
{
	/*
	DrawFormatString(0, 0, 0xFF0000, "cameraParam:pos(%.1f, %.1f, %.1f),angle(%.1f, %.1f, %.1f)",
					 pos_.x, pos_.y, pos_.z, angles_.x, angles_.y, angles_.z);
					 */
}

void Camera::Release(void)
{

}

void Camera::ChangeMode(MODE mode)
{
	// カメラモードの変更
	mode_ = mode;
	
	// 変更時の初期化処理
	switch (mode_)
	{
		case Camera::MODE::FIXED_POINT:
		break;

		case Camera::MODE::FREE:
		break;
	}
}

void Camera::SetBeforeDrawFixedPoint(void)
{
}

void Camera::SetBeforeDrawFree(void)
{
	auto& ins = InputManager::GetInstance();

	// WASDでカメラの位置を変える
	float movePow = 3.0f;
	if (ins.KeyIsNew(KEY_INPUT_W)) { pos_.z += movePow; }
	if (ins.KeyIsNew(KEY_INPUT_A)) { pos_.x -= movePow; }
	if (ins.KeyIsNew(KEY_INPUT_S)) { pos_.z -= movePow; }
	if (ins.KeyIsNew(KEY_INPUT_D)) { pos_.x += movePow; }
	if (ins.KeyIsNew(KEY_INPUT_Q)) { pos_.y += movePow; }
	if (ins.KeyIsNew(KEY_INPUT_E)) { pos_.y -= movePow; }

	// 矢印キーでカメラの角度を変える
	float rotPow = 1.0f * (DX_PI_F / 180.0f);
	if (ins.KeyIsNew(KEY_INPUT_DOWN)) { angles_.x += rotPow; }
	if (ins.KeyIsNew(KEY_INPUT_UP)) { angles_.x -= rotPow; }
	if (ins.KeyIsNew(KEY_INPUT_RIGHT)) { angles_.y += rotPow; }
	if (ins.KeyIsNew(KEY_INPUT_LEFT)) { angles_.y -= rotPow; }
}


void Camera::SetShake(void)
{
	shakeTime_ = SHAKE_TIME;

	// 位置を一時保存
	prePos_ = pos_;
}

void Camera::Shake(void)
{
	float delta = SceneManager::GetInstance().GetDeltaTime();

	if (shakeTime_ > 0.0f)
	{
		shakeTime_ -= delta;
		int team = static_cast<int>(shakeTime_ * 10.0f);
		if ((team % SHAKE_TEAM) == 0)
		{
			pos_.x = prePos_.x + SHAKE_MAX_X;
			pos_.y = prePos_.y + SHAKE_MAX_Y;
		}
		else
		{
			pos_.x = prePos_.x - SHAKE_MAX_X;
			pos_.y = prePos_.y - SHAKE_MAX_Y;
		}
	}
	else if (!AsoUtility::Equals(pos_, prePos_))
	{
		// 座標が同一で無いとき、もとの位置に戻す
		pos_ = prePos_;
	}
}
