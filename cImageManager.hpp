#pragma once
struct cTexture
{
	D3DXIMAGE_INFO Info;
	LPDIRECT3DTEXTURE9 Image;
};

struct cRenderStructure
{
	shared_ptr<cTexture> Image = nullptr;
	Vector2 Position = VECTOR2_ZERO;
	float RotateAngle = 0;
	Vector2 Scale = VECTOR2_ZERO;

	float Depth = 0;
	Vector2 Pivot = VECTOR2_ZERO;
	Color Color = D3DCOLOR_ARGB(255, 255, 255, 255);

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

		cRenderPartBuilder* SetImage(shared_ptr<cTexture> _Image)
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
		cRenderPartBuilder* SetColor(Color Color = D3DCOLOR_ARGB(255,255,255,255))
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
	: public cSingleton<cImageManager, IFlowInitializeBase>
	, public IFlowInitializeBase
	, public IFlowRenderDeviceBase
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

	map<string, shared_ptr<cTexture>> m_Images;
	map<string, vector<shared_ptr<cTexture>>*>  m_Animations;

	LPD3DXSPRITE m_Sprite;
	LPD3DXFONT m_Font;

	shared_ptr<cTexture> AddImage(string key, string path);
	shared_ptr<cTexture> FindTexture(string key);
	void AddAnimation(string key);
	vector<shared_ptr<cTexture>>* FindAnimation(string key);

	void Render(cRenderPart renderStruct);

};
#define IMAGE cImageManager::GetInstance()