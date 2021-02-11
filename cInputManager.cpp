#include "DXUT.h"
#include "cInputManager.h"

void cInputManager::Init()
{
}

void cInputManager::Release()
{
}

void cInputManager::Update()
{
	memcpy(m_Old, m_Cur, 128);
	memcpy(m_Cur, false, 128);

	for (int i = 0; i < 128; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			m_Cur[i] = true;
		}
	}

	POINT Point;
	GetCursorPos(&Point);
	ScreenToClient(DXUTGetHWND(), &Point);
	m_MousePos = Vector2(Point.x, Point.y);
}

void cInputManager::Render()
{
}

void cInputManager::SetMousePosition(Vector2 Position)
{
	POINT Point = { Position.x, Position.y };
	ClientToScreen(DXUTGetHWND(), &Point);
	SetCursorPos(Point.x, Point.y);
}
