#pragma once
class cObject : public cFlowBase
{
	// cFlowBase��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	Vector2 m_Position;

};

