#pragma once
class cLineRenderer : public cComponent
{
public:
	virtual void Init() override;

	virtual void Release() override;

	virtual void Update() override;

	virtual void Render() override;

	void SetLineVertex(Vector2* vertexData, int vertexCount)
	{	
		m_vertexList = vertexData;
		m_vertexCount = vertexCount;
	}

private:
	ID3DXLine* m_Line;
	Vector2* m_vertexList;
	int m_vertexCount;
};

