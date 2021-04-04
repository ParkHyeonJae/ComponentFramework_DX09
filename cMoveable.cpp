#include "DXUT.h"
#include "cMoveable.hpp"

void cMoveable::Init()
{
	m_PrevPos = m_Pos;
}

void cMoveable::Release()
{
}

void cMoveable::Update()
{
	if (!m_bIsMoveable) {
		m_bIsMoveable = !m_bIsMoveable;
		return;
	}
	if (INPUT->KeyDown('W')) {
		m_nextMoveCallback(Vector2(m_Pos.x, m_Pos.y - m_MoveOffset.y));
		m_PrevPos = m_Pos;
		m_Pos.y -= m_MoveOffset.y;
		m_moveCallback(m_Pos, MoveDirection::UP);
	}
	if (INPUT->KeyDown('S')) {
		m_nextMoveCallback(Vector2(m_Pos.x, m_Pos.y + m_MoveOffset.y));
		m_PrevPos = m_Pos;
		m_Pos.y += m_MoveOffset.y;
		m_moveCallback(m_Pos, MoveDirection::DOWN);
	}
	if (INPUT->KeyDown('A')) {
		m_nextMoveCallback(Vector2(m_Pos.x - m_MoveOffset.x, m_Pos.y));
		m_PrevPos = m_Pos;
		m_Pos.x -= m_MoveOffset.x;
		m_moveCallback(m_Pos, MoveDirection::LEFT);
	}
	if (INPUT->KeyDown('D')) {
		m_nextMoveCallback(Vector2(m_Pos.x + m_MoveOffset.x, m_Pos.y));
		m_PrevPos = m_Pos;
		m_Pos.x += m_MoveOffset.x;
		m_moveCallback(m_Pos, MoveDirection::RIGHT);
	}
	GetMoveOwnerTransform()->position = m_Pos;
	
}

void cMoveable::Render()
{
}
