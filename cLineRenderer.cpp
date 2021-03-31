#include "DXUT.h"
#include "cLineRenderer.hpp"

void cLineRenderer::Init()
{
	D3DXCreateLine(g_DEVICE, &m_Line);
	m_Line->SetWidth(2);
}

void cLineRenderer::Release()
{
	//if (m_vertexList)
	//	delete[] m_vertexList;
		
	if (m_Line)
		SAFE_RELEASE(m_Line);
}

void cLineRenderer::Update()
{
}

void cLineRenderer::Render()
{
	m_Line->Begin();

	m_Line->Draw(m_vertexList, m_vertexCount, D3DCOLOR_XRGB(255, 0, 0));


	m_Line->End();
}