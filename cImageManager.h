#pragma once
struct cTexture
{
	D3DXIMAGE_INFO Info;
	LPDIRECT3DTEXTURE9 Image;
};

struct cRenderStructure
{
	cTexture* Image = nullptr;
	Vector2 Position = VECTOR2_ZERO;
	float RotateAngle = 0;
	Vector2 Scale = VECTOR2_ZERO;

	float Depth = 0;
	Vector2 Pivot = VECTOR2_ZERO;
	Color Color = 0x0fffffff;

	bool IsCameraView = false;

	RECT Rect;
};

class cRenderPart
{
public:
	cRenderPart(cRenderStructure part) : m_part(part) {}

	cRenderStructure GetPart()
	{
		return m_part;
	}

	Vector2 CalcuatePivotToCenter(Vector2 pivot)
	{
		D3DXIMAGE_INFO info = GetPart().Image->Info;
		return Vector2(pivot.x * static_cast<float>(info.Width), pivot.y * static_cast<float>(info.Height));
	}
public:
	class cRenderPartBuilder
	{
	public:
		cRenderPart Build()
		{
			return cRenderPart(part);
		}

		cRenderPartBuilder* SetImage(cTexture* _Image)
		{
			part.Image = _Image;
			return this;
		}
		cRenderPartBuilder* SetPosition(Vector2 Position)
		{
			part.Position = Position;
			return this;
		}
		cRenderPartBuilder* SetAngle(float RotateAngle)
		{
			part.RotateAngle = RotateAngle;
			return this;
		}
		cRenderPartBuilder* SetScale(Vector2 Scale)
		{
			part.Scale = Scale;
			return this;
		}
		cRenderPartBuilder* SetDepth(float Depth)
		{
			part.Depth = Depth;
			return this;
		}
		cRenderPartBuilder* SetPivot(Vector2 Pivot)
		{
			part.Pivot = Pivot;
			return this;
		}
		cRenderPartBuilder* SetColor(Color Color)
		{
			part.Color = Color;
			return this;
		}
		cRenderPartBuilder* SetCameraView(bool IsCameraView)
		{
			part.IsCameraView = IsCameraView;
			return this;
		}
		cRenderPartBuilder* SetRect(RECT Rect)
		{
			part.Rect = Rect;
			return this;
		}
	private:
		cRenderStructure part;
	};
private:
	cRenderStructure m_part;
};

class cImageManager 
	: public cSingleton<cImageManager, cFlowInitializeBase>
	, public cFlowInitializeBase
	, public cFlowRenderDeviceBase
{
public:
	// cFlowInitializeBase을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Release() override;


	// cFlowRenderDeviceBase을(를) 통해 상속됨
	virtual void OnBeginRender() override;

	virtual void OnEndRender() override;

	virtual void OnLostDevice() override;

	virtual void OnResetDevice() override;

	map<string, cTexture*> m_Images;
	map<string, vector<cTexture*>*>  m_Animations;

	LPD3DXSPRITE m_Sprite;
	LPD3DXFONT m_Font;

	cTexture* AddImage(string key, string path);
	cTexture* FindTexture(string key);
	void AddAnimation(string key);
	vector<cTexture*>* FindAnimation(string key);

	void Render(cRenderPart renderStruct);

};
#define IMAGE cImageManager::GetInstance()