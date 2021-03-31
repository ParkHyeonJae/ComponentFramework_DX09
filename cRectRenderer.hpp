#pragma once
class cRenderer;
class cRectRenderer : public cRenderer
{
public:
	virtual void Init() override;

	virtual void Release() override;

	virtual void Update() override;

	virtual void Render() override;

	void SetRect(RECT rect)
	{
		m_rect = rect;
	}

private:
	RECT m_rect;
};

