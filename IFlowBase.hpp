#pragma once

class IFlowInitializeBase abstract
{
	virtual void Init()		PURE;
	virtual void Release()	PURE;
};

class IFlowContinousBase abstract
{
public:
	virtual void Update()	PURE;
	virtual void Render()	PURE;
};

class IFlowBase : public IFlowInitializeBase, public IFlowContinousBase
{
};

class IFlowDeviceBase abstract
{
public:
	virtual void OnLostDevice() PURE;
	virtual void OnResetDevice() PURE;
};

class IFlowRenderDeviceBase : public IFlowDeviceBase
{
public:
	virtual void OnBeginRender() PURE;
	virtual void OnEndRender() PURE;
	virtual void OnLostDevice() PURE;
	virtual void OnResetDevice() PURE;
};