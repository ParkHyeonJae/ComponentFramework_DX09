#pragma once
class cCameraManager : public cSingleton<cCameraManager>, public cFlowBase
{
public:
	// cFlowBase��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	Matrix GetViewMatrix()
	{
		return m_Mat;
	}

private:
	Vector2 WIN_HALF;

	Vector2 m_Position;
	float m_Scale;
	float m_Rot;
	
	Matrix m_Mat;
	Matrix m_InversedMat;

	
};
#define CAMERA cCameraManager::GetInstance()