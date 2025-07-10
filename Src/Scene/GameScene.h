#pragma once
#include "./SceneBase.h"
class Stage;
class Cannon;

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
};