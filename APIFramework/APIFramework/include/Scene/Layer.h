#pragma once
#include "..\Game.h"
class CLayer
{
private:
	CLayer();
	class CScene* m_pScene;
	friend class CScene;
	string m_strTag;
	int m_iZOrder;
	list<class CObj*> m_ObjList;
public:
	~CLayer();
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}
	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;

	}
	string GetTag() const
	{
		return m_strTag;
	}
	int GetZOrder() const
	{
		return m_iZOrder;
	}
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}
	CScene* GetScene() const
	{
		return m_pScene;
	}
};

