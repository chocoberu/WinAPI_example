#include "MoveObj.h"

CMoveObj::CMoveObj() : m_fAngle(0.0f), m_fSpeed(100.0f)
{
}

CMoveObj::CMoveObj(const CMoveObj& obj) : CObj(obj)
{
	m_fAngle = obj.m_fAngle;
}

CMoveObj::~CMoveObj()
{
	
}


void CMoveObj::Move(float x, float y)
{
	m_tPos.x += x;
	m_tPos.y += y;
}

void CMoveObj::Move(float x, float y, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_tPos.y += y * fDeltaTime;
}

void CMoveObj::Move(const POSITION& tMove)
{
	m_tPos += tMove;
}

void CMoveObj::Move(const POSITION& tMove, float fDeltaTime)
{
	m_tPos += tMove * fDeltaTime;
}

void CMoveObj::MoveAngle(float fSpeed)
{
	m_tPos.x += cosf(m_fAngle) * fSpeed;
	m_tPos.y += cosf(m_fAngle) * fSpeed;
}

void CMoveObj::MoveAngle(float fSpeed, float fDeltaTime)
{
	m_tPos.x += cosf(m_fAngle) * fSpeed * fDeltaTime;
	m_tPos.y += cosf(m_fAngle) * fSpeed * fDeltaTime;
}

void CMoveObj::MoveX(float x)
{
	m_tPos.x += x;
}

void CMoveObj::MoveX(float x, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
}
void CMoveObj::MoveXFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.x += m_fSpeed * fDeltaTime * eDir;
}
void CMoveObj::MoveY(float y)
{
	m_tPos.y += y;
}

void CMoveObj::MoveY(float y, float fDeltaTime)
{
	m_tPos.y += y * fDeltaTime;
}

void CMoveObj::MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.y += m_fSpeed * fDeltaTime * eDir;
}


bool CMoveObj::Init()
{
	return false;
}

void CMoveObj::Input(float fDeltaTime)
{
}

int CMoveObj::Update(float fDeltaTime)
{
	return 0;
}

int CMoveObj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CMoveObj::Collision(float fDeltaTime)
{
}

void CMoveObj::Render(HDC hDC, float fDeltaTime)
{
}
