#pragma once
#include "Scene.h"
class CInGameScene : public CScene
{
private:
	CInGameScene();
	~CInGameScene();
	friend class CSceneManager;
public:
	virtual bool Init() override;
};

