#pragma once
class cScene : public IFlowBase
{
public:
	// IFlowBase��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

