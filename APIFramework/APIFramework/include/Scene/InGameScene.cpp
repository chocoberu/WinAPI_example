#include "InGameScene.h"

CInGameScene::CInGameScene()
{

}
CInGameScene::~CInGameScene()
{

}
bool CInGameScene::Init()
{
	if (!CScene::Init())
		return false;
	return true;
}
