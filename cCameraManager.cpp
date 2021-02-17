#include "DXUT.h"
#include "cCameraManager.hpp"

void cCameraManager::Init()
{
	m_Position = Vector2(0, 0);

	m_Scale = 1;
	m_Rot = 0;

	WIN_HALF = WINHALF_VECTOR;
}

void cCameraManager::Update()
{
	Matrix P, S, R;
	D3DXMatrixTranslation(&P, (-m_Position.x) + WIN_HALF.x, (-m_Position.y) + WIN_HALF.y, 0);
	D3DXMatrixRotationZ(&R, m_Rot);
	D3DXMatrixScaling(&S, m_Scale, m_Scale, 1);

	m_Mat = R * S * P;
	D3DXMatrixInverse(&m_InversedMat, NULL, &m_Mat);

	D3DXMatrixTransformation2D(&m_Mat, &Vector2(WIN_HALF.x, WIN_HALF.y), 0, &(VECTOR2_ONE * m_Scale), NULL, 0, &((m_Position * -1) + WIN_HALF));
}

void cCameraManager::Render()
{
	g_DEVICE->SetTransform(D3DTS_VIEW, &m_Mat);
}

void cCameraManager::Release()
{
}