#include "EffectResManager.h"
#include <EffekseerForDXLib.h>
#include <string>
#include "../Application.h"

EffectResManager* EffectResManager::instance_ = nullptr;

void EffectResManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new EffectResManager();
	}
	instance_->Init();
}

EffectResManager& EffectResManager::GetInstance(void)
{
	return *instance_;
}

EffectResManager::EffectResManager(void)
{
}


void EffectResManager::Init(void)
{
	// リソースのロード
	Load();
}

void EffectResManager::Destroy(void)
{
	for (const auto& pair : resourceIds_)
	{
		// 爆発エフェクトのメモリ解放
		DeleteEffekseerEffect(pair.second);
	}
	// インスタンスのメモリ解放
	delete instance_;
}

int EffectResManager::GetResourceId(TYPE type)
{
	if (resourceIds_.count(type) == 0)
	{
		return -1;
	}
	return resourceIds_[type];
}

void EffectResManager::Load(void)
{
	std::string path = "";

	// 爆発地面エフェクトのロード
	path = (Application::PATH_EFFECT + "Blast/Blast.efkefc").c_str();
	resourceIds_.emplace(TYPE::BLAST_GROUND,
						 LoadEffekseerEffect(path.c_str()));

	// 爆発ヒットエフェクトのロード
	path = (Application::PATH_EFFECT + "BlastHit/BlastHit.efkefc").c_str();
	resourceIds_.emplace(TYPE::BLAST_HIT,
						 LoadEffekseerEffect(path.c_str()));
}