#include "DXUT.h"
#include "cMainScene.hpp"




void cMainScene::Init()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CAMERA->SetCenterOrigin(false);

	IMAGE->AddImage("NANANA", "./Assets/Images/nanana.png");
	

	auto groundObj = OBJECT->CreateEmptyObject();
	auto ground = groundObj->AddComponent<cGround>();

	auto player = OBJECT->CreateEmptyObject();
	auto renderer = player->AddComponent<cRenderer>();

	auto bossObj = OBJECT->CreateEmptyObject();
	auto boss = bossObj->AddComponent<cBoss>();

	renderer->SetSprite("NANANA");
	
	Vector2 unitPerWinSize = ground->GetUnitPerWinSize();
	auto MAX = ground->GetGroundMaxSize();
	vertData.reserve(MAX.x * MAX.y);

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
		Vector2 prevIndex = ground->ConvertLocalPosToIndexUnit(moveable->GetPrevPos());
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
			std::cout << "FLOOD FILL" << "\n";

			for (auto pos : playerLines)
				ground->EnableGroundCell(pos.y, pos.x);


			playerLines.clear();

			cPrintWrapper::cVector2Print playerPoint = curIndex;
			cPrintWrapper::cVector2Print bossPoint = m_BossPos;
			std::cout << "PLAYER = " << playerPoint << "\n";
			std::cout << "BOSS = " << bossPoint << "\n";

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
			ground->RenewGroundData();
			for (decltype(sideIndexSize) i = 0; i < sideIndexSize; i++) {
				auto containVector = ground->FindElementInVector<Vector2>(ground->GetRemainGround()
					, Vector2(curIndex.y + (sideCheckVec[i].y)
						, curIndex.x + (sideCheckVec[i].x)),
					[](Vector2 t1, Vector2 t2) -> bool
					{
						return (static_cast<int>(t1.x) == static_cast<int>(t2.y)) && (static_cast<int>(t1.y) == static_cast<int>(t2.x));
					});

				for (auto& vec : containVector)
				{
					if (ground->IsOutOfMapRange(vec.y, vec.x))
						continue;
					if (ground->GetGround(vec.y, vec.x) != (int)cGround::EGroundType::EMPTY)
						continue;
					//cPrintWrapper::cVector2Print printVec = vec;
					//std::cout << "Print Result : " << printVec << "\n";

					if (ground->SearchBoss_FLOOD_FILL(vec.y, vec.x) == true)
						continue;
					//std::cout << "find Cout : " << printVec << "\n";
					ground->FLOOD_FILL(vec.y, vec.x);
				}
			}

			nowCell = prevCell = (int)cGround::EGroundType::PLAYER_LINE;
			bIsDrawStart = false;
			ground->PrintGround();
			return;
		}
		//int destIndex = static_cast<int>(curIndex.x + ((curIndex.y - 1) * MAX));

		
		ground->SetGroundMap(curIndex.y, curIndex.x, (int)cGround::EGroundType::PLAYER_LINE);
		if (!bIsDrawStart) {
			std::cout << "Line Draw Start !" << "\n";
			bIsDrawStart = true;
		}
		

		ground->PrintGround();
	});
}

void cMainScene::Release()
{
	_CrtDumpMemoryLeaks();
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
