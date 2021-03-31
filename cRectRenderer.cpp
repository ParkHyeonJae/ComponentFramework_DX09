#include "DXUT.h"
#include "cRectRenderer.hpp"

void cRectRenderer::Init()
{
}

void cRectRenderer::Release()
{
}

void cRectRenderer::Update()
{
}

void cRectRenderer::Render()
{
	cRenderPart::cRenderPartBuilder builder;
	shared_ptr<cTransform> transform = GetOwner()->transform;
	IMAGE->RectRender(builder.SetImage(texture)
		->SetPosition(transform->position)
		->SetAngle(transform->angle)
		->SetScale(transform->scale)
		->SetPivot(VECTOR2_HALF)
		->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255))
		->SetRect(m_rect)
		->Build());
}
