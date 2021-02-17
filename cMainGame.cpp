#include "DXUT.h"
#include "cMainGame.h"

void cMainGame::Init()
{
	IMAGE->CreateInstance();
	CAMERA->CreateInstance();
	OBJECT->CreateInstance();

}

void cMainGame::Update()
{
	CAMERA->Update();
	OBJECT->Update();
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
