#pragma once
class cMoveable : public cComponent
{
public:
	enum class MoveDirection
	{
		UP,
		LEFT,
		DOWN,
		RIGHT,

		COUNT
	};

	virtual void Init() override;

	virtual void Release() override;

	virtual void Update() override;

	virtual void Render() override;

	Vector2 GetPos() const
	{
		return m_Pos;
	}

	Vector2 GetPrevPos() const
	{
		return m_PrevPos;
	}

	void SetPos(Vector2 pos)
	{
		m_Pos = pos;
	}

	void SetMoveOffset(Vector2 moveOffset)
	{
		m_MoveOffset = moveOffset;
	}

	void SetMoveOwnerTransform(shared_ptr<cTransform> moveOwnerTransform)
	{
		m_MoveOwnerTransform = moveOwnerTransform;
	}

	Vector2 MoveToUnit(int offsetX, int offsetY)
	{
		return Vector2(m_MoveOffset.x * offsetX, m_MoveOffset.y * offsetY);
	}

	shared_ptr<cTransform> GetMoveOwnerTransform() const
	{
		return m_MoveOwnerTransform;
	}


	void SetMoveCallback(function<void(Vector2, MoveDirection)> moveCallback)
	{
		m_moveCallback = moveCallback;
	}

	void SetNextMoveCallback(function<void(Vector2)> nextMoveCallback)
	{
		m_nextMoveCallback = nextMoveCallback;
	}

	void SetMoveable(bool m_IsMoveable)
	{
		this->m_bIsMoveable = m_IsMoveable;
	}
private:
	bool m_bIsMoveable = true;
	Vector2 m_PrevPos;
	Vector2 m_Pos;
	Vector2 m_MoveOffset = VECTOR2_ZERO;
	shared_ptr<cTransform> m_MoveOwnerTransform;
	function<void(Vector2, MoveDirection)> m_moveCallback;
	function<void(Vector2)> m_nextMoveCallback;
};

