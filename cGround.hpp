#pragma once
class cRectRenderer;
class cGround : public cComponent
{
public:
	struct Node
	{
		int data;
		shared_ptr<cObject> cell;
	};

	enum class EGroundType
	{
		EMPTY = 0,
		WALL = 1,
		PLAYER_GROUND,
		PLAYER_LINE,
		BOSS,
	};


	virtual void Init() override;

	virtual void Release() override;

	virtual void Update() override;

	virtual void Render() override;

	Vector2 GetUnitPerWinSize() const
	{
		return Vector2(WINSIZE_X / MAX, WINSIZE_Y / MAX);
	}

	Vector2 ConvertLocalPosToIndexUnit(Vector2 pos)
	{
		Vector2 curIndex;
		curIndex.x = MAX - ((WINSIZE_X - pos.x) / GetUnitPerWinSize().x);
		curIndex.y = MAX - ((WINSIZE_Y - pos.y) / GetUnitPerWinSize().y);

		return curIndex;
	}

	Vector2 ConvertIndexUnitToLocalPos(Vector2 indexUnit)
	{
		return Vector2(indexUnit.x * GetUnitPerWinSize().x, indexUnit.y * GetUnitPerWinSize().y);
	}

	int GetGroundMaxSize() const
	{
		return MAX;
	}

	void SetGroundMap(int y, int x, int val);


	bool IsOutOfMapRange(int y, int x)
	{
		if (x < 0 || x > MAX || y < 0 || y > MAX)
			return true;
		return false;
	}

	bool IsOwnGround(int y, int x)
	{
		if (IsOutOfMapRange(y, x))
			return false;
		return m_Ground[y][x].data == (int)EGroundType::PLAYER_GROUND;
	}

	bool IsContact(int y, int x, int val)
	{
		if (IsOutOfMapRange(y, x))
			return false;
		return m_Ground[y][x].data == val;
	}

	void EnableGroundCell(int y, int x);

	void Visited(int y, int x);
	void FLOOD_FILL(int y, int x);

	void PrintGround()
	{
		for (size_t y = 0; y < MAX; y++)
		{
			for (size_t x = 0; x < MAX; x++)
			{
				std::cout << m_Ground[y][x].data;
			}
			std::cout << "\n";
		}
	}

	int GetGround(int y, int x)
	{
		if (IsOutOfMapRange(y, x))
			return 0;
		return m_Ground[y][x].data;
	}

	vector<Vector2> GetRemainGround()
	{
		return m_RemainGround;
	}

	template<typename T>
	const vector<T> FindElementInVector(const vector<T>& indexs, T& val, function<bool(T, T)> predicate)
	{
		vector<T> newVector;
		newVector.reserve(indexs.size());

		for (auto& vec : indexs)
		{
			if (predicate(vec, val)) {
				newVector.emplace_back(vec);
			}
		}
		return newVector;
	}
	void EraseRemainGround(int y, int x)
	{
		for (auto& remainPos : m_RemainGround)
		{
			if (remainPos.y != y || remainPos.x != x)
				return;
		}
		auto iter = std::find(m_RemainGround.begin()
			, m_RemainGround.end(), Vector2(y, x));
		if (iter == m_RemainGround.end())
			return;

		m_RemainGround.erase(iter);
	}

	bool IsContainInRemainGround(int y, int x)
	{
		auto containVector = FindElementInVector<Vector2>(m_RemainGround, Vector2(y, x),
			[](Vector2 t1, Vector2 t2) -> bool
			{
				return (static_cast<int>(t1.x) == static_cast<int>(t2.x)) 
					&& (static_cast<int>(t1.y) == static_cast<int>(t2.y));
			});

		for (auto& vec : containVector)
		{
			if (GetGround(vec.y, vec.x) != (int)cGround::EGroundType::EMPTY)
				continue;
			cPrintWrapper::cVector2Print printVec = vec;
			std::cout << printVec << "\n";
		}

		//auto iter = std::find(m_RemainGround.begin()
		//	, m_RemainGround.end(), Vector2(y, x));
		//if (iter == m_RemainGround.end())
		//	return false;

		return true;
	}

private:
	const int MAX = 20;
	vector<Vector2> m_RemainGround;
	Node** m_Ground;
};