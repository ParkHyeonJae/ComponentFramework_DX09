#include "DXUT.h"
#include "cMainScene.hpp"

void cMainScene::Init()
{
	IMAGE->AddImage("NANANA", "./Assets/Images/nanana.png");
	auto nanana = OBJECT->CreateEmptyObject();
	auto renderer = nanana->AddComponent<cRenderer>();
	renderer->SetSprite("NANANA");
	cPrintWrapper::cTransformPrint printWrapper = nanana->transform;
	cPrintWrapper::cTexturePrint textureWrapper = renderer->GetTexture();
	nanana->transform->position = Vector2(200, 300);
	std::cout << printWrapper << "\n";
	std::cout << textureWrapper << "\n";
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
}
