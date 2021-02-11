#pragma once
class cInputManager : public cSingleton<cInputManager>, public cFlowBase
{
public:
	// cFlowBase을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Release() override;

	virtual void Update() override;

	virtual void Render() override;


	bool m_Cur[128];
	bool m_Old[128];
	Vector2 m_MousePos;

	bool KeyPress(int key) { return m_Cur[key]; }
	bool KeyDown(int key) { return m_Cur[key] && !m_Old[key]; }
	bool KeyUp(int key) { return !m_Cur[key] && m_Old[key]; }
	Vector2 GetMousePosition() { return m_MousePos; }
	void SetMousePosition(Vector2 Position);
};

#define INPUT cInputManager::GetInstance()

