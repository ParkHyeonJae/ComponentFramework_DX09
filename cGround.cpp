#include "DXUT.h"
#include "cGround.hpp"

void cGround::Init()
{
	IMAGE->AddImage("BG", "./Assets/Images/BG.jpg");

	m_RemainGround.reserve(MAX * MAX);

	m_Ground = new Node*[MAX];
	for (int i = 0; i < MAX; i++)
		m_Ground[i] = new Node[MAX];

	for (size_t y = 0; y < MAX; y++)
	{
		for (size_t x = 0; x < MAX; x++)
		{
			if (y == 0 || y == MAX - 1 || x == 0 || x == MAX - 1)
				m_Ground[y][x].data = 1;
			else m_Ground[y][x].data = 0;

			m_RemainGround.emplace_back(Vector2(y, x));

			m_Ground[y][x].cell = OBJECT->CreateEmptyObject();
			auto rectRenderer = m_Ground[y][x].cell->AddComponent<cRectRenderer>();
			rectRenderer->SetSprite("BG");
			
			auto localPos =  ConvertIndexUnitToLocalPos(Vector2(x, y));
			std::cout << localPos.x << " : " << localPos.y << "\t";
			m_Ground[y][x].cell->transform->position = Vector2(
				(WINSIZE_X / 2) + (localPos.x - GetUnitPerWinSize().x)
				, (WINSIZE_Y / 2) + (localPos.y - GetUnitPerWinSize().y));
			RECT rc = { localPos.x,localPos.y,localPos.x + GetUnitPerWinSize().x,localPos.y + GetUnitPerWinSize().y };
			rectRenderer->SetRect(rc);
			rectRenderer->SetEnable(false);
		}
		std::cout << "\n";
	}

}

void cGround::Release()
{
	for (int i = 0; i < MAX; i++)
		delete[] m_Ground[i];
	delete[] m_Ground;
}

void cGround::Update()
{
}

void cGround::Render()
{
}

void cGround::SetGroundMap(int y, int x, int val)
{
	if (IsOutOfMapRange(y, x))
		return;

	m_Ground[y][x].data = val;
}

void cGround::EnableGroundCell(int y, int x)
{
	auto cell = m_Ground[y][x].cell;
	auto renderer = cell->GetComponent<cRectRenderer>();
	renderer->SetEnable(true);

	EraseRemainGround(y, x);
}

void cGround::Visited(int y, int x)
{
	m_Ground[y][x].data = (int)EGroundType::PLAYER_GROUND;
	EnableGroundCell(y, x);
}

void cGround::FLOOD_FILL(int y, int x)
{
	if (IsOutOfMapRange(y, x))
		return;

	if (m_Ground[y][x].data == (int)EGroundType::EMPTY)
	{
		Visited(y, x);

		FLOOD_FILL(y, x + 1);
		FLOOD_FILL(y, x - 1);
		FLOOD_FILL(y + 1, x);
		FLOOD_FILL(y - 1, x);
	}
}
