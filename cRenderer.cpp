#include "DXUT.h"
#include "cRenderer.h"

void cRenderer::Init()
{
}

void cRenderer::Release()
{
}

void cRenderer::Update()
{
	//std::cout << GetOwner()->transform->name << " : 업데이트 중.." << std::endl;
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

bool cRenderer::SetImage(string&& name, string&& path)
{
	texture = IMAGE->FindTexture(name);
	if (IsExistTexture(texture))
		return true;
	return IsExistTexture((texture = IMAGE->AddImage(name, path)));
}

bool cRenderer::SetImage(string&& name)
{
	texture = IMAGE->FindTexture(name);
	return IsExistTexture(texture);
}
