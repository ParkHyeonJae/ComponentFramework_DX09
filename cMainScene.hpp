#pragma once
class cLineRenderer;
class cMainScene : public cScene
{
public:
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

private:

	enum class ECONTACTWALL
	{
		UP,
		LEFT,
		DOWN,
		RIGHT
	};
	enum class EPLAYER2BOSSDIR
	{
		UP,
		LEFT,
		DOWN,
		RIGHT
	};


	cMoveable::MoveDirection startDir;
	cMoveable::MoveDirection endDir;

	bool bIsDrawStart = false;

	int prevCell = 0;
	int nowCell = 0;


	shared_ptr<cLineRenderer> lineRenderer;

	vector<Vector2> vertData;
	Vector2 m_BossPos = Vector2(15, 15);
	vector<Vector2> playerLines;
};

