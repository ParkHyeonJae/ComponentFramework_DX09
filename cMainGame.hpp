#pragma once
class cMainGame : public IFlowBase, public IFlowDeviceBase
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void OnLostDevice() override;
	virtual void OnResetDevice() override;
};

