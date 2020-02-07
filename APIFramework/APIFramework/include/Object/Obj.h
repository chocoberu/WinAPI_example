#pragma once
#include "../Ref.h"
#include "../Scene/Layer.h"
class CObj : public CRef
{
protected:
	CObj();
	CObj(const CObj& obj);
	virtual ~CObj();

	class CScene* m_pScene;
	class CLayer* m_pLayer;

	string m_strTag;
	POSITION m_tPos;
	_SIZE m_tSize;
	POSITION m_tPivot;
	

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

	template <typename T>
	static T* CreateObject(const string& strTag, class CLayer* pLayer = nullptr)
	{
		T* pObj = new T;
		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}
		if (pLayer)
		{
			pLayer->AddObject(pObj);
		}
		pObj->AddRef();
		return pObj;
	}

	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}
	void SetPos(const POSITION& tPos)
	{
		m_tPos = tPos;
	}
	void SetPos(float x, float y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}
	void SetSize(const _SIZE& tSize)
	{
		m_tSize = tSize;
	}
	void SetSize(float x, float y)
	{
		m_tSize.x = x;
		m_tSize.y = y;
	}
	string GetTag() const
	{
		return m_strTag;
	}
	POSITION GetPos() const
	{
		return m_tPos;
	}
	_SIZE GetSize() const
	{
		return m_tSize;
	}
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetLayer(class CLayer* pLayer)
	{
		m_pLayer = pLayer;
	}
	class CScene* GetScene() const
	{
		return m_pScene;
	}
	class CLayer* GetLayer() const
	{
		return m_pLayer;
	}
};

