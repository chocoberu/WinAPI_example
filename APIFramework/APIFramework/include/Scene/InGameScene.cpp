#include "InGameScene.h"
#include "../Object/Player.h"
#include "../Object/Minion.h"
#include "Layer.h"

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

	CLayer* pLayer = FindLayer("Default");
	CPlayer* pPlayer = CObj::CreateObject<CPlayer>("Player", pLayer);
	SAFE_RELEASE(pPlayer);
	CMinion* pMinion = CObj::CreateObject<CMinion>("Minion", pLayer);
	SAFE_RELEASE(pMinion);
	return true;
}
