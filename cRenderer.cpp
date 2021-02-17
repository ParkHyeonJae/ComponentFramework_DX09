#include "DXUT.h"
#include "cRenderer.hpp"

void cRenderer::Init()
{
}

void cRenderer::Release()
{
}

void cRenderer::Update()
{
}

void cRenderer::Render()
{
	cRenderPart::cRenderPartBuilder builder;
	shared_ptr<cTransform> transform = GetOwner()->transform;
	IMAGE->Render(builder.SetImage(texture)
		->SetPosition(transform->position)
		->SetAngle(transform->angle)
		->SetScale(transform->scale)
		->SetPivot(VECTOR2_HALF)
		->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255))
		->Build());
}

bool cRenderer::SetSprite(string&& name, string&& path)
{
	texture = IMAGE->FindTexture(name);
	if (IsExistTexture(texture))
		return true;
	return IsExistTexture((texture = IMAGE->AddImage(name, path)));
}

bool cRenderer::SetSprite(string&& name)
{
	texture = IMAGE->FindTexture(name);
	return IsExistTexture(texture);
}
