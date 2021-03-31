#pragma once
class cCameraManager : public cSingleton<cCameraManager>, public IFlowBase
{
public:
	// cFlowBase을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	Matrix GetViewMatrix()
	{
		return m_Mat;
	}

	void SetCenterOrigin(bool centerOrigin)
	{
		m_IsCenterOrigin = centerOrigin;
	}

private:
	Vector2 WIN_HALF;

	Vector2 m_Position;
	float m_Scale;
	float m_Rot;
	
	Matrix m_Mat;
	Matrix m_InversedMat;

	bool m_IsCenterOrigin;
	
};
#define CAMERA cCameraManager::GetInstance()