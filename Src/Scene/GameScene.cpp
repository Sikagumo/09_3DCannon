#include "GameScene.h"
#include <DxLib.h>
#include "../Object/Stage.h"
#include "../Object/Cannon.h"


GameScene::GameScene(void)
{
}

void GameScene::Init(void)
{
	stage_ = new Stage();
	stage_->Init();

	cannon_ = new Cannon();
	cannon_->Init();
}

void GameScene::Update(void)
{
	stage_->Update();
	cannon_->Update();
}

void GameScene::Draw(void)
{
	stage_->Draw();
	cannon_->Draw();
}

void GameScene::Release(void)
{
	cannon_->Release();
	delete cannon_;

	stage_->Release();
	delete stage_;
}
