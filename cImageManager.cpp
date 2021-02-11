#include "DXUT.h"
#include "cImageManager.h"

void cImageManager::Init()
{
	D3DXCreateSprite(g_DEVICE, &m_Sprite);
	D3DXCreateFont(g_DEVICE, 64, 0, 0, 1, 0, DEFAULT_CHARSET, 0, 0, 0, L"µ¸¿ò", &m_Font);
}

void cImageManager::Release()
{
	for (auto& iter : m_Images)
	{
		g_SAFE_RELEASE(iter.second->Image);
		g_SAFE_DELETE(iter.second);
	}
	for (auto& iter : m_Animations)
	{
		g_SAFE_DELETE(iter.second);
	}
	g_SAFE_RELEASE(m_Sprite);
	g_SAFE_RELEASE(m_Font);
}

void cImageManager::OnBeginRender()
{
	m_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	g_DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DX_FILTER_NONE);
	g_DEVICE->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DX_FILTER_NONE);
	g_DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DX_FILTER_NONE);
}

void cImageManager::OnEndRender()
{
	m_Sprite->End();
}

void cImageManager::OnLostDevice()
{
	m_Sprite->OnLostDevice();
}

void cImageManager::OnResetDevice()
{
	m_Sprite->OnResetDevice();
}

cTexture* cImageManager::AddImage(string key, string path)
{
	cTexture* Texture = new cTexture();
	if (SUCCEEDED(D3DXCreateTextureFromFileExA(g_DEVICE, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_POINT, D3DX_FILTER_POINT, 0, &Texture->Info, 0, &Texture->Image)))
	{
		m_Images.insert(make_pair(key, Texture));
		return Texture;
	}
	return nullptr;
}

cTexture* cImageManager::FindTexture(string key)
{
	return m_Images[key];
}

void cImageManager::AddAnimation(string key)
{
	char Key[64];
	vector<cTexture*>* AnimationFrame = new vector<cTexture*>();
	for (int i = 1; true; i++)
	{
		sprintf(Key, "%s%d", key.c_str(), i);
		auto iter = m_Images.find(Key);
		if (iter != m_Images.end())
			AnimationFrame->emplace_back((*iter).second);
		else {
			m_Animations.insert(make_pair(key, AnimationFrame));
			break;
		}
	}

}

vector<cTexture*>* cImageManager::FindAnimation(string key)
{
	return m_Animations[key];
}

void cImageManager::Render(cRenderPart renderStruct)
{
	Matrix Mat;
	Vector2 Center = VECTOR2_ZERO;
	cRenderStructure renderSt = renderStruct.GetPart();

	cTexture* Texture = renderSt.Image;
	Vector2 Pivot = renderSt.Pivot;
	Vector2 Scale = renderSt.Scale;
	float Rot = renderSt.RotateAngle;
	float Depth = renderSt.Depth;

	Vector2 Position = renderSt.Position;
	bool IsView = renderSt.IsCameraView;

	Color Color = renderSt.Color;

	RECT Rect = renderSt.Rect;

	if (Pivot != VECTOR2_ZERO)
		Center = renderStruct.CalcuatePivotToCenter(Pivot);
	D3DXMatrixTransformation2D(&Mat, &Center, 0, &Scale, &Center, Rot, &(Position - Center));

	if (IsView)
		Mat *= CAMERA->GetViewMatrix();

	Mat._43 = Depth;
	m_Sprite->SetTransform(&Mat);
	m_Sprite->Draw(Texture->Image, nullptr, nullptr, nullptr, Color);
}
