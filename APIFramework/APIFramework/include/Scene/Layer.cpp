#include "Layer.h"
#include "../Object/Obj.h"

CLayer::CLayer() : m_iZOrder(0), m_strTag(""),m_pScene(nullptr)
{

}
CLayer::~CLayer()
{
	Safe_Release_VecList(m_ObjList);
}

void CLayer::Input(float fDeltaTime)
{
	for (auto iter = m_ObjList.begin(); iter != m_ObjList.end(); iter++)
		(*iter)->Input(fDeltaTime);
}

int CLayer::Update(float fDeltaTime)
{
	for (auto iter = m_ObjList.begin(); iter != m_ObjList.end(); iter++)
		(*iter)->Update(fDeltaTime);
	return 0;
}

int CLayer::LateUpdate(float fDeltaTime)
{
	for (auto iter = m_ObjList.begin(); iter != m_ObjList.end(); iter++)
		(*iter)->LateUpdate(fDeltaTime);
	return 0;
}

void CLayer::Collision(float fDeltaTime)
{
	for (auto iter = m_ObjList.begin(); iter != m_ObjList.end(); iter++)
		(*iter)->Collision(fDeltaTime);
}

void CLayer::Render(HDC hDC, float fDeltaTime)
{
	for (auto iter = m_ObjList.begin(); iter != m_ObjList.end(); iter++)
		(*iter)->Render(hDC, fDeltaTime);
}

void CLayer::AddObject(CObj* pObj)
{
	pObj->SetScene(m_pScene);
	pObj->SetLayer(this);
	//pObj->AddRef();

	m_ObjList.push_back(pObj);
}
