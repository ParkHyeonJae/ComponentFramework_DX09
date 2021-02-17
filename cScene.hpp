#pragma once
class cScene : public IFlowBase
{
public:
	// IFlowBase을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

