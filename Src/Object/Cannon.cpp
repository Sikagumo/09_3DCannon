#include "Cannon.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "./Shot/ShotBase.h"
#include "./Shot/ShotNormal.h"



void Cannon::Init(void)
{
	standId_ = MV1LoadModel((Application::PATH_MODEL + "Cannon/Stand.mv1").c_str());
	barrelId_ = MV1LoadModel((Application::PATH_MODEL + "Cannon/Barrel.mv1").c_str());

	// íeÇÃÉÇÉfÉã
	shotModelId_ = MV1LoadModel((Application::PATH_MODEL + "Cannon/Shot.mv1").c_str());
	shotSpecialModelId_ = MV1LoadModel((Application::PATH_MODEL + "Cannon/SpikeShot.mv1").c_str());


	standPos_ = STAND_POS;

	// ëÂñCÉçÅ[ÉJÉãç¿ïW
	barrelLocalPos_ = BARREL_POS;

	// ëÂñCÉOÉçÅ[ÉoÉãç¿ïW
	barrelPos_ = VAdd(barrelLocalPos_, standPos_);

	standRot_ = STAND_ANGLES;
	barrelRot_ = VAdd(standRot_, BARREL_ANGLES);

	// íeî≠éÀÇÃçdíºéûä‘
	stepShotDelay_ = 0.0f;

}

void Cannon::Update(void)
{
	RotationProc();

	// î≠éÀëÄçÏ
	ProcessShot();

	// íeÇÃçXêV
	UpdateShot();
}

void Cannon::Draw(void)
{
//	MV1DrawModel(standId_);
// 	MV1DrawModel(barrelId_);

	// íeÇÃï`âÊ
	DrawShot();


#ifdef _DEBUG

	// íeÇÃî≠éÀà íu
	VECTOR pos = barrelPos_;

	// ñCêgÇ©ÇÁÇÃëäëŒç¿ïW
	VECTOR localPos = { 0.0f, 25.0f, 30.0f };

	// ñCêgÇÃâÒì]çsóÒ
	MATRIX matRot = MGetIdent();
	matRot = MMult(matRot, MGetRotX(barrelRot_.x));
	matRot = MMult(matRot, MGetRotY(barrelRot_.y));
	matRot = MMult(matRot, MGetRotZ(barrelRot_.z));

	// ï˚å¸Ç∆ìØÇ∂óvóÃÇ≈ÅAëäëŒç¿ïWÇâÒì]
	VECTOR localPosRot = VTransform(localPos, matRot);

	// ÉçÅ[ÉJÉãç¿ïWÇ©ÇÁÉèÅ[ÉãÉhç¿ïWÇ÷ïœä∑
	pos = VAdd(pos, localPosRot);

	// íeÇÃî≠éÀà íuñ⁄à¿
	DrawSphere3D(pos, 10.0f, 10, 0x00ff00, 0x00ff00, true);

	// ñCë‰ÇÃÉÇÉfÉãï`âÊ
	MV1DrawModel(standId_);

	// ñCêgÇÃÉÇÉfÉãï`âÊ(àÍéûìIÇ…îºìßñæÇ…Ç∑ÇÈ)
	MV1SetMaterialDifColor(barrelId_, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.5f));

	MV1DrawModel(barrelId_);


	DrawFormatString(0, 0, 0xFF0000, "standRot:(%.1fÅã, %.1fÅã, %.1fÅã), barrelRot:(%.1fÅã, %.1fÅã, %.1fÅã)",
					 AsoUtility::Rad2DegF(standRot_.x), AsoUtility::Rad2DegF(standRot_.y), AsoUtility::Rad2DegF(standRot_.z),
					 AsoUtility::Rad2DegF(barrelRot_.x), AsoUtility::Rad2DegF(barrelRot_.y), AsoUtility::Rad2DegF(barrelRot_.z));
#endif
}

void Cannon::Release(void)
{
	// ñCë‰ÉÇÉfÉãÇÃâï˙
	MV1DeleteModel(barrelId_);
	MV1DeleteModel(standId_);

	// íeÉÇÉfÉãÇÃâï˙
	MV1DeleteModel(shotSpecialModelId_);
	MV1DeleteModel(shotModelId_);

	for (ShotBase* shot : shots_)
	{
		shot->Release();
		delete shot;
	}

}

std::vector<ShotBase*> Cannon::GetShots(void)
{
	return shots_	;
}


void Cannon::RotationProc(void)
{
	InputManager& input = InputManager::GetInstance();

	VECTOR rot = {};
	float speedX = ROT_SPEED_X;
	float speedY = ROT_SPEED_Y;

	if (input.KeyIsNew(KEY_INPUT_LSHIFT) || input.KeyIsNew(KEY_INPUT_RSHIFT))
	{
		speedX *= ROT_SPEED_UP;
		speedY *= ROT_SPEED_UP;
	}

	if (input.KeyIsNew(KEY_INPUT_A) || input.KeyIsNew(KEY_INPUT_LEFT))
	{
		standRot_.y -= speedY;
		if (standRot_.y < ROT_Y_MIN)
		{
			standRot_.y = ROT_Y_MIN;
		}
	}
	if (input.KeyIsNew(KEY_INPUT_D) || input.KeyIsNew(KEY_INPUT_RIGHT))
	{
		standRot_.y += speedY;
		if (standRot_.y > ROT_Y_MAX)
		{
			standRot_.y = ROT_Y_MAX;
		}
	}

	if (input.KeyIsNew(KEY_INPUT_W) || input.KeyIsNew(KEY_INPUT_UP))
	{
		barrelRot_.x += speedX;
		if (barrelRot_.x > ROT_X_MAX)
		{
			barrelRot_.x = ROT_X_MAX;
		}
	}
	if (input.KeyIsNew(KEY_INPUT_S) || input.KeyIsNew(KEY_INPUT_DOWN))
	{
		barrelRot_.x -= speedX;
		if (barrelRot_.x < ROT_X_MIN)
		{
			barrelRot_.x = ROT_X_MIN;
		}
	}

	// ìyë‰ÇÃYé≤âÒì]ÇëÂñCÇÃYé≤Ç…îΩâfÇ∑ÇÈ
	barrelRot_.y = standRot_.y;

	// âÒì]ÇîΩâf
	MV1SetRotationXYZ(standId_, standRot_);
	MV1SetRotationXYZ(barrelId_, barrelRot_);

}

void Cannon::ProcessShot(void)
{
	auto& ins = InputManager::GetInstance();
	VECTOR forward = { 0.0f, 0.0f, 1.0f };

	// çUåÇÉLÅ[ÇâüÇ∑Ç∆ÅAíeÇê∂ê¨
	if (stepShotDelay_ <= 0.0f)
	{
		if (ins.KeyIsNew(KEY_INPUT_Z) ||
			ins.KeyIsNew(KEY_INPUT_SPACE))
		{
			// óLå¯Ç»íeÇéÊìæÇ∑ÇÈ
			ShotBase* shot = GetValidShot(ShotBase::TYPE::NORMAL);

			// íPà çsóÒ
			MATRIX matRot = MGetIdent();

			// äeé≤ÇÃçsóÒÇçÏÇËÅAçsóÒÇçáê¨Ç∑ÇÈ
			matRot = MMult(matRot, MGetRotX(barrelRot_.x));
			matRot = MMult(matRot, MGetRotY(barrelRot_.y));
			matRot = MMult(matRot, MGetRotZ(barrelRot_.z));

			// Xé≤ÇÃçsóÒ
			MATRIX xMat = MGetRotX(barrelRot_.x);
			MATRIX yMat = MGetRotX(barrelRot_.y);

			// âÒì]çsóÒìØémÇçáê¨
			MATRIX mixA = MMult(xMat, yMat);
			MATRIX mixB = MMult(yMat, xMat);


			// âÒì]çsóÒÇégópÇµÇƒÅAÉxÉNÉgÉãÇâÒì]Ç∑ÇÈ
			shotDir_ = VTransform(forward, matRot);

			// î≠éÀà íuÇí≤êÆ
			VECTOR shotPos = VAdd(barrelPos_, SHOT_POS);

			// íeÇê∂ê¨(ï˚å¸ÇÕâºÇ≈ê≥ñ ï˚å¸)
			shot->CreateShot(shotPos, shotDir_);

			// íeî≠éÀå„ÇÃçdíºéûä‘ÉZÉbÉg
			stepShotDelay_ = SHOT_DELAY;
		}
	}

	// íeî≠éÀå„ÇÃçdíºéûä‘Çå∏ÇÁÇµÇƒÇ¢Ç≠
	if (stepShotDelay_ > 0.0f)
	{
		stepShotDelay_ -= SceneManager::GetInstance().GetDeltaTime();
	}
}

void Cannon::UpdateShot(void)
{
	size_t size = shots_.size();
	for (int i = 0; i < size; i++)
	{
		if (!shots_[i]->IsAlive())
		{
			continue;
		}

		// çXêVèàóù
		shots_[i]->Update();
	}
}

void Cannon::DrawShot(void)
{
	size_t size = shots_.size();
	for (int i = 0; i < size; i++)
	{
		if (!shots_[i]->IsAlive())
		{
			continue;
		}

		// ï`âÊèàóù
		shots_[i]->Draw();
	}
}


ShotBase* Cannon::GetValidShot(ShotBase::TYPE type)
{
	size_t size = shots_.size();

	for (int i = 0; i < size; i++)
	{
		// ñ¢égóp(ê∂ë∂ÇµÇƒÇ¢Ç»Ç¢)Ç≈ÅAÇ©Ç¬ÅAíeÇÃéÌï Ç™ìØÇ∂
		if (!shots_[i]->IsAlive() &&
			 shots_[i]->GetType() == type)
		{
			return shots_[i];
		}
	}

	// êVÇµÇ¢íeÇÃÉCÉìÉXÉ^ÉìÉXÇê∂ê¨Ç∑ÇÈ
	ShotBase* shot;
	
	if (type == ShotBase::TYPE::NORMAL)
	{
		shot = new ShotNormal(type, shotModelId_);
	}

	if (type == ShotBase::TYPE::SPECIAL)
	{
		shot = new ShotNormal(type, shotModelId_);
	}

	// â¬ïœí∑îzóÒÇ…í«â¡
	shots_.push_back(shot);

	return shot;
}
