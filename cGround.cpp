#include "DXUT.h"
#include "cGround.hpp"

void cGround::Init()
{
	IMAGE->AddImage("BG", "./Assets/Images/BG.jpg");

	m_RemainGround.reserve(MAX.x * MAX.y);

	m_Ground = new Node*[MAX.y];
	for (int i = 0; i < MAX.x; i++)
		m_Ground[i] = new Node[MAX.x];

	m_findGround = new Node*[MAX.y];
	for (int i = 0; i < MAX.x; i++)
		m_findGround[i] = new Node[MAX.x];


	for (size_t y = 0; y < MAX.y; y++)
	{
		for (size_t x = 0; x < MAX.x; x++)
		{
			if (y == 0 || y == MAX.y - 1 || x == 0 || x == MAX.x - 1)
				m_Ground[y][x].data = 1;
			else m_Ground[y][x].data = 0;

			m_RemainGround.emplace_back(Vector2(y, x));

			m_Ground[y][x].cell = OBJECT->CreateEmptyObject();
			auto rectRenderer = m_Ground[y][x].cell->AddComponent<cRectRenderer>();
			rectRenderer->SetSprite("BG");
			
			auto localPos =  ConvertIndexUnitToLocalPos(Vector2(x, y));
			//std::cout << localPos.x << " : " << localPos.y << "\t";
			m_Ground[y][x].cell->transform->position = Vector2(
				(WINSIZE_X / 2) + (localPos.x - GetUnitPerWinSize().x)
				, (WINSIZE_Y / 2) + (localPos.y - GetUnitPerWinSize().y));
			RECT rc = { localPos.x,localPos.y,localPos.x + GetUnitPerWinSize().x,localPos.y + GetUnitPerWinSize().y };
			rectRenderer->SetRect(rc);
			rectRenderer->SetEnable(false);
		}
		//std::cout << "\n";
	}

}

void cGround::Release()
{
	for (int i = 0; i < MAX.y; i++) {
		//m_findGround[i]->cell.reset();
		delete[] m_findGround[i];
	}
	delete[] m_findGround;

	for (int i = 0; i < MAX.y; i++) {
		//m_Ground[i]->cell.reset();
		delete[] m_Ground[i];
	}
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

void cGround::RenewGroundData()
{
	for (size_t i = 0; i < MAX.y; i++)
	{
		for (size_t j = 0; j < MAX.x; j++)
		{
			m_findGround[i][j] = m_Ground[i][j];
		}
	}
}

bool cGround::SearchBoss_FLOOD_FILL(int y, int x)
{
	if (IsOutOfMapRange(y, x))
		return false;

	//std::cout << "BOSS FLOOD FILL : " << x << " : " << y << "\n";

	if (m_findGround[y][x].data == (int)EGroundType::BOSS)
		return true;

	if (m_findGround[y][x].data == (int)EGroundType::EMPTY)
	{
		m_findGround[y][x].data = (int)EGroundType::PLAYER_GROUND;

		if (SearchBoss_FLOOD_FILL(y, x + 1) == true)
			return true;
		if (SearchBoss_FLOOD_FILL(y, x - 1) == true)
			return true;
		if (SearchBoss_FLOOD_FILL(y + 1, x) == true)
			return true;
		if (SearchBoss_FLOOD_FILL(y - 1, x) == true)
			return true;
	}
	return false;
}

void cGround::EraseRemainGround(int y, int x)
{
	for (auto& remainPos : m_RemainGround)
	{
		if (remainPos.y != y || remainPos.x != x)
			return;
	}
	auto iter = std::find(m_RemainGround.begin()
		, m_RemainGround.end(), Vector2(y, x));
	if (iter == m_RemainGround.end())
		return;

	m_RemainGround.erase(iter);
}

const bool cGround::IsContainInRemainGround(const int y, const int x)
{
	auto containVector = FindElementInVector<Vector2>(m_RemainGround, Vector2(y, x),
		[](Vector2 t1, Vector2 t2) -> bool
		{
			return (static_cast<int>(t1.x) == static_cast<int>(t2.x))
				&& (static_cast<int>(t1.y) == static_cast<int>(t2.y));
		});

	for (auto& vec : containVector)
	{
		if (GetGround(vec.y, vec.x) != (int)cGround::EGroundType::EMPTY)
			continue;
		//cPrintWrapper::cVector2Print printVec = vec;
		//std::cout << printVec << "\n";
	}

	//auto iter = std::find(m_RemainGround.begin()
	//	, m_RemainGround.end(), Vector2(y, x));
	//if (iter == m_RemainGround.end())
	//	return false;

	return true;
}
