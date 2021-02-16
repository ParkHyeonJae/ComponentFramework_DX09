#include "DXUT.h"
#include "cMainGame.h"

shared_ptr<cObject> Nanana;
shared_ptr<cObject> Nanana2;
void cMainGame::Init()
{
	IMAGE->CreateInstance();
	CAMERA->CreateInstance();
	OBJECT->CreateInstance();


	Nanana = OBJECT->CreateEmptyObject();
	Nanana->transform->name = "nanana";
	shared_ptr<cRenderer> renderer = Nanana->AddComponent<cRenderer>();
	assert(renderer->SetImage("NANANA", "./Assets/Images/nanana.png"));
	
	Nanana2 = OBJECT->CreateEmptyObject();
	shared_ptr<cRenderer> renderer2 = Nanana2->AddComponent<cRenderer>();
	assert(renderer2->SetImage("NANANA"));
	Nanana2->transform->position = Vector2(200, 0);
}

void cMainGame::Update()
{
	CAMERA->Update();
	OBJECT->Update();
	Nanana->transform->angle-= 0.01f;
	Nanana->transform->scale = Vector2(0.5f, 0.5f);
	Nanana2->transform->angle+= 0.01f;
	Nanana2->transform->scale = Vector2(0.5f, 0.5f);
}

void cMainGame::Render()
{
	IMAGE->OnBeginRender();

	CAMERA->Render();
	OBJECT->Render();

	IMAGE->OnEndRender();
}

void cMainGame::Release()
{
	IMAGE->ReleaseInstance();
	CAMERA->ReleaseInstance();
	OBJECT->ReleaseInstance();
}

void cMainGame::OnLostDevice()
{
	IMAGE->OnLostDevice();
}

void cMainGame::OnResetDevice()
{
	IMAGE->OnResetDevice();
}
