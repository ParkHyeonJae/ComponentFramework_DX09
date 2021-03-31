#pragma once
class cBoss : public cComponent
{
public:
	virtual void Init() override;

	virtual void Release() override;

	virtual void Update() override;

	virtual void Render() override;

};

