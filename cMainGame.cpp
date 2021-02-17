#include "DXUT.h"
#include "cMainGame.hpp"

void cMainGame::Init()
{
	INPUT->CreateInstance();
	IMAGE->CreateInstance();
	CAMERA->CreateInstance();
	OBJECT->CreateInstance();

	SCENE->CreateInstance();

	SCENE->AddScene(SCENE->CreateScenePair<cMainScene>(SceneKey(0, "MainScene")));
	SCENE->LoadScene(SceneKey(0, "MainScene"));
}

void cMainGame::Update()
{
	INPUT->Update();
	CAMERA->Update();
	SCENE->Update();
	OBJECT->Update();
}

void cMainGame::Render()
{
	INPUT->Render();
	IMAGE->OnBeginRender();

	SCENE->Render();
	CAMERA->Render();
	OBJECT->Render();

	IMAGE->OnEndRender();
}

void cMainGame::Release()
{
	SCENE->ReleaseInstance();
	IMAGE->ReleaseInstance();
	CAMERA->ReleaseInstance();
	OBJECT->ReleaseInstance();
	INPUT->ReleaseInstance();
}

void cMainGame::OnLostDevice()
{
	IMAGE->OnLostDevice();
}

void cMainGame::OnResetDevice()
{
	IMAGE->OnResetDevice();
}
