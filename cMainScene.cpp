#include "DXUT.h"
#include "cMainScene.hpp"

shared_ptr<cLineRenderer> lineRenderer;

vector<Vector2> vertData;
Vector2 m_BossPos = Vector2(15, 15);
vector<Vector2> playerLines;


enum class ECONTACTWALL
{
	UP,
	LEFT,
	DOWN,
	RIGHT
};
enum class EPLAYER2BOSSDIR
{
	UP,
	LEFT,
	DOWN,
	RIGHT
};


cMoveable::MoveDirection startDir;
cMoveable::MoveDirection endDir;

bool bIsDrawStart = false;

int prevCell = 0;
int nowCell = 0;

void cMainScene::Init()
{
	CAMERA->SetCenterOrigin(false);

	IMAGE->AddImage("NANANA", "./Assets/Images/nanana.png");
	
	//auto nanana = OBJECT->CreateEmptyObject();
	//auto renderer = nanana->AddComponent<cRenderer>();
	//renderer->SetSprite("NANANA");
	//cPrintWrapper::cTransformPrint printWrapper = nanana->transform;
	//cPrintWrapper::cTexturePrint textureWrapper = renderer->GetTexture();
	//nanana->transform->position = Vector2(200, 300);
	//std::cout << printWrapper << "\n";
	//std::cout << textureWrapper << "\n";

	


	//auto BG = OBJECT->CreateEmptyObject();
	//auto rectRenderer = BG->AddComponent<cRectRenderer>();
	//
	//
	//RECT rc = { 0,0,0,0 };
	//rectRenderer->SetRect(rc);

	auto groundObj = OBJECT->CreateEmptyObject();
	auto ground = groundObj->AddComponent<cGround>();

	auto player = OBJECT->CreateEmptyObject();
	auto renderer = player->AddComponent<cRenderer>();

	auto bossObj = OBJECT->CreateEmptyObject();
	auto boss = bossObj->AddComponent<cBoss>();

	renderer->SetSprite("NANANA");
	
	Vector2 unitPerWinSize = ground->GetUnitPerWinSize();
	int MAX = ground->GetGroundMaxSize();
	vertData.reserve(MAX * MAX);

	cPrintWrapper::cVector2Print vec = unitPerWinSize;
	std::cout << vec << std::endl;

	lineRenderer = player->AddComponent<cLineRenderer>();
	

	

	ground->SetGroundMap(m_BossPos.y, m_BossPos.x, (int)cGround::EGroundType::BOSS);

	std::cout << WINSIZE_X << " : " << WINSIZE_Y << "\n";
	player->transform->scale = Vector2(0.1f, 0.1f);
	auto moveable = player->AddComponent<cMoveable>();
	moveable->SetMoveOffset(unitPerWinSize);
	moveable->SetMoveOwnerTransform(player->transform);
	moveable->SetPos(moveable->MoveToUnit(0, 2));
	vertData.emplace_back(moveable->GetPos());
	
	moveable->SetNextMoveCallback([=](Vector2 nextPos) {
		std::cout << "Current : " << nextPos.x << ": " << nextPos.y << "\n";
		Vector2 nextIndex = ground->ConvertLocalPosToIndexUnit(nextPos);

		prevCell = nowCell;
		auto cell = ground->GetGround(nextIndex.y, nextIndex.x);
		nowCell = cell;


		if (ground->IsOwnGround(nextIndex.y, nextIndex.x)) {
			std::cout << "Own Ground" << "\n";
			moveable->SetMoveable(false);
		}
	});

	moveable->SetMoveCallback([=](Vector2 pos, cMoveable::MoveDirection dir) {
		cPrintWrapper::cVector2Print nextMoveWrapper = pos;
		std::cout << nextMoveWrapper << std::endl;
		Vector2 curIndex = ground->ConvertLocalPosToIndexUnit(pos);

		cPrintWrapper::cVector2Print curPoint = curIndex;
		std::cout << "CurPoint : " <<  curPoint << "\n";

		vertData.emplace_back(Vector2(pos));
		if (prevCell == (int)cGround::EGroundType::PLAYER_LINE
			&& nowCell == (int)cGround::EGroundType::PLAYER_LINE)
			return;
		
		playerLines.emplace_back(curIndex);

		if (ground->IsContact(curIndex.y, curIndex.x, (int)cGround::EGroundType::WALL)
			|| ground->IsContact(curIndex.y, curIndex.x, (int)cGround::EGroundType::PLAYER_LINE))
		{
			endDir = dir;
			std::cout << "FLOOD FILL" << "\n";

			for (auto pos : playerLines)
				ground->EnableGroundCell(pos.y, pos.x);
			playerLines.clear();


			auto distanceXY = Vector2(
				m_BossPos.x - curIndex.x
				, m_BossPos.y - curIndex.y);

			// 플레이어에서 보스까지의 방향 (플레이어 중심)
			EPLAYER2BOSSDIR bossDirX = distanceXY.x >= 0 ? EPLAYER2BOSSDIR::RIGHT : EPLAYER2BOSSDIR::LEFT;
			EPLAYER2BOSSDIR bossDirY = distanceXY.y >= 0 ? EPLAYER2BOSSDIR::DOWN : EPLAYER2BOSSDIR::UP;

			//auto dirX = distanceXY.x >= 0 ? "RIGHT" : "LEFT";
			//auto dirY = distanceXY.y >= 0 ? "DOWN"  : "UP";
			//
			//std::cout << "dirX : " << dirX << ", dirY : " << dirY << "\n";

			auto x = bossDirX == EPLAYER2BOSSDIR::RIGHT ? -1 : +1;
			auto y = bossDirY == EPLAYER2BOSSDIR::DOWN ? -1 : +1;

			cPrintWrapper::cVector2Print playerPoint = curIndex;
			cPrintWrapper::cVector2Print bossPoint = m_BossPos;
			std::cout << "PLAYER = " << playerPoint << "\n";
			std::cout << "BOSS = " << bossPoint << "\n";
			std::cout << "distanceXY = " << distanceXY.x << " : " << distanceXY.y << "\n";
			std::cout << "xy = " << x << " : " << y << "\n";

#pragma region TEST




			// UP, LEFT, DOWN, RIGHT
			//FLOAT startDirX[(int)cMoveable::MoveDirection::COUNT] = { 0, 1, 0, -1 };
			//FLOAT startDirY[(int)cMoveable::MoveDirection::COUNT] = { 1, 0, -1, 0 };

			//FLOAT endDirX[(int)cMoveable::MoveDirection::COUNT] = { x, 0, x, 0 };
			//FLOAT endDirY[(int)cMoveable::MoveDirection::COUNT] = { 0, -y, 0, y };



			int dirX = 0;
			int dirY = 0;
			switch (startDir)
			{
			case cMoveable::MoveDirection::UP:
				if (endDir == cMoveable::MoveDirection::LEFT) {
					dirX = 1;
					dirY = y;
				}

				if (endDir == cMoveable::MoveDirection::RIGHT) {
					dirX = -1;
					dirY = y;
				}

				if (endDir == cMoveable::MoveDirection::UP) {
					dirX = x;
					dirY = 1;
				}

				if (endDir == cMoveable::MoveDirection::DOWN) {
					dirX = x;
					dirY = -1;
				}

				break;
			case cMoveable::MoveDirection::LEFT:
				if (endDir == cMoveable::MoveDirection::LEFT) {
					dirX = 1;
					dirY = y;
				}

				if (endDir == cMoveable::MoveDirection::RIGHT) {
					dirX = -1;
					dirY = y;
				}

				if (endDir == cMoveable::MoveDirection::UP) {
					dirX = x;
					dirY = 1;
				}

				if (endDir == cMoveable::MoveDirection::DOWN) {
					dirX = x;
					dirY = -1;
				}
				break;
			case cMoveable::MoveDirection::DOWN:
				if (endDir == cMoveable::MoveDirection::LEFT) {
					dirX = 1;
					dirY = y;
				}

				if (endDir == cMoveable::MoveDirection::RIGHT) {
					dirX = -1;
					dirY = y;
				}

				if (endDir == cMoveable::MoveDirection::UP) {
					dirX = x;
					dirY = 1;
				}

				if (endDir == cMoveable::MoveDirection::DOWN) {
					dirX = x;
					dirY = -1;
				}
				break;
			case cMoveable::MoveDirection::RIGHT:
				if (endDir == cMoveable::MoveDirection::LEFT) {
					dirX = 1;
					dirY = y;
				}

				if (endDir == cMoveable::MoveDirection::RIGHT) {
					dirX = -1;
					dirY = y;
				}

				if (endDir == cMoveable::MoveDirection::UP) {
					dirX = x;
					dirY = 1;
				}

				if (endDir == cMoveable::MoveDirection::DOWN) {
					dirX = x;
					dirY = -1;
				}
				break;
			default:
				break;
			}


			//std::cout << "startDirX[(int)startDir] : " << startDirX[(int)startDir] << "\n";
			//std::cout << "startDirY[(int)startDir] : " << startDirY[(int)startDir] << "\n";

			//std::cout << "endDirX[(int)endDir] : " << endDirX[(int)endDir] << "\n";
			//std::cout << "endDirY[(int)endDir] : " << endDirY[(int)endDir] << "\n";
#pragma endregion
			Vector2 sideCheckVec[] = {
				Vector2(-1, 0),
				Vector2(1,	0),
				Vector2(0, -1),
				Vector2(0,	1),
				Vector2(-1,	-1),
				Vector2(-1,	1),
				Vector2(1,	-1),
				Vector2(1,	1),
			};

			auto sideIndexSize = sizeof(sideCheckVec) / sizeof(Vector2);

			for (decltype(sideIndexSize) i = 0; i < sideIndexSize; i++) {
				decltype(curIndex.x) x;
				decltype(curIndex.y) y;

				auto condition = ground->IsContainInRemainGround(
					x = (curIndex.x + sideCheckVec[i].x)
					, y = (curIndex.y + sideCheckVec[i].y));
				if (condition)
					continue;
				ground->FLOOD_FILL(x, y);
			}

			//ground->FLOOD_FILL(curIndex.y + dirY, curIndex.x + dirX);
			//ground->FLOOD_FILL(curIndex.y + y, curIndex.x + x);
			//ground->FLOOD_FILL(curIndex.y + startDirY[(int)startDir] + endDirY[(int)endDir]
			//	, curIndex.x + startDirX[(int)startDir] + endDirX[(int)endDir]);

			nowCell = prevCell = (int)cGround::EGroundType::PLAYER_LINE;
			bIsDrawStart = false;
			ground->PrintGround();
			return;
		}
		//int destIndex = static_cast<int>(curIndex.x + ((curIndex.y - 1) * MAX));
		ground->SetGroundMap(curIndex.y, curIndex.x, (int)cGround::EGroundType::PLAYER_LINE);
		if (!bIsDrawStart) {
			std::cout << "Line Draw Start !" << "\n";
			startDir = dir;
			bIsDrawStart = true;
		}
		

		ground->PrintGround();
	});
}

void cMainScene::Release()
{
}

void cMainScene::Update()
{
	if (INPUT->KeyDown('K'))
		OBJECT->ClearAllObject();
}

void cMainScene::Render()
{

	lineRenderer->SetLineVertex(vertData.data(), vertData.size());
	
}
