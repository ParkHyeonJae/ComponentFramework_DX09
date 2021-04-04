#pragma once
class cBoss : public cComponent
{
public:
	virtual void Init() override;

	virtual void Release() override;

	virtual void Update() override;

	virtual void Render() override;

	Vector2 GetBossPos() const
	{
		return m_BossPos;
	}

	void SetGround(shared_ptr<cGround> ground)
	{
		m_Ground = ground;
	}

private:
	Vector2 m_BossPos;
	shared_ptr<cGround> m_Ground;
};

