#include "DXUT.h"
#include "cMainGame.h"

void cMainGame::Init()
{
	IMAGE->CreateInstance();
	CAMERA->CreateInstance();
}

void cMainGame::Update()
{
	CAMERA->Update();
}

void cMainGame::Render()
{
	IMAGE->OnBeginRender();

	CAMERA->Render();

	IMAGE->OnEndRender();
}

void cMainGame::Release()
{
	IMAGE->ReleaseInstance();
	CAMERA->ReleaseInstance();
}

void cMainGame::OnLostDevice()
{
	IMAGE->OnLostDevice();
}

void cMainGame::OnResetDevice()
{
	IMAGE->OnResetDevice();
}
