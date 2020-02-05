#include "SceneManager.h"
#include "InGameScene.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager() : m_pScene(nullptr), m_pNextScene(nullptr)
{

}
CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pScene);
}

bool CSceneManager::Init()
{
	CreateScene<CInGameScene>(SC_CURRENT);
	return true;
}

void CSceneManager::Input(float fDeltaTime)
{
	m_pScene->Input(fDeltaTime);
}

int CSceneManager::Update(float fDeltaTime)
{
	m_pScene->Update(fDeltaTime);
}

int CSceneManager::LateUpdate(float fDeltaTime)
{
	m_pScene->LateUpdate(fDeltaTime);
}

void CSceneManager::Collision(float fDeltaTime)
{
	m_pScene->Collision(fDeltaTime);
}

void CSceneManager::Render(HDC hDC, float fDeltaTime)
{
	m_pScene->Render(hDC, fDeltaTime);
}