#pragma once
#include "Scene.h"

class InGameScene :
	public Scene
{
private:
	friend class Scenemanager; //������� �����ϸ� �����̺��� ���ؼ� ������ �� �ִ�.

private:
	InGameScene();
	~InGameScene();

public:
	virtual bool Init();
};

