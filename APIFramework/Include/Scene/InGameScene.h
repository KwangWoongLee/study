#pragma once
#include "Scene.h"

class InGameScene :
	public Scene
{
private:
	friend class Scenemanager; //프렌드로 설정하면 프라이빗에 대해서 접근할 수 있다.

private:
	InGameScene();
	~InGameScene();

public:
	virtual bool Init();
};


