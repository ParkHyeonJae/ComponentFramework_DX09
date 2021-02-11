#pragma once

class cFlowInitializeBase abstract
{
	virtual void Init()		PURE;
	virtual void Release()	PURE;
};

class cFlowContinousBase abstract
{
public:
	virtual void Update()	PURE;
	virtual void Render()	PURE;
};

class cFlowBase : public cFlowInitializeBase, public cFlowContinousBase
{
public:
	cFlowBase() = default;
};

class cFlowDeviceBase abstract
{
public:
	virtual void OnLostDevice() PURE;
	virtual void OnResetDevice() PURE;
};

class cFlowRenderDeviceBase : public cFlowDeviceBase
{
public:
	virtual void OnBeginRender() PURE;
	virtual void OnEndRender() PURE;
	virtual void OnLostDevice() PURE;
	virtual void OnResetDevice() PURE;
};