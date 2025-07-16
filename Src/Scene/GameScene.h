#pragma once
#include "./SceneBase.h"
class Stage;
class Cannon;
class EnemyManager;

class GameScene : public SceneBase
{
public:

	GameScene(void);

	~GameScene(void) = default;

	void Init(void);

	void Update(void);

	void Draw(void);

	void Release(void);


private:

	Stage* stage_;

	Cannon* cannon_;

	// 
	EnemyManager* enemyManager_;

	/// <summary>
	/// “–‚½‚è”»’èˆ—
	/// </summary>
	void Collision(void);

	/// <summary>
	/// ’e‚ÆƒXƒe[ƒW‚Ì“–‚½‚è”»’è
	/// </summary>
	void Collision_ShotAndStage(void);

	/// <summary>
	/// ’e‚Æ“G‚Ì“–‚½‚è”»’è
	/// </summary>
	void Collision_ShotAndEnemy(void);
};