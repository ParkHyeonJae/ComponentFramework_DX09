#pragma once
class cRectRenderer;
class cGround : public cComponent
{
public:
	class Node
	{
	public:
		Node() = default;
		~Node() { cell.reset(); }

		int data = 0;
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
		return Vector2(WINSIZE_X / MAX.x, WINSIZE_Y / MAX.y);
	}

	Vector2 ConvertLocalPosToIndexUnit(Vector2 pos)
	{
		Vector2 curIndex;
		curIndex.x = MAX.x - ((WINSIZE_X - pos.x) / GetUnitPerWinSize().x);
		curIndex.y = MAX.y - ((WINSIZE_Y - pos.y) / GetUnitPerWinSize().y);

		return curIndex;
	}

	Vector2 ConvertIndexUnitToLocalPos(Vector2 indexUnit)
	{
		return Vector2(indexUnit.x * GetUnitPerWinSize().x, indexUnit.y * GetUnitPerWinSize().y);
	}

	Vector2 GetGroundMaxSize() const
	{
		return MAX;
	}

	void SetGroundMap(int y, int x, int val);


	bool IsOutOfMapRange(const int y, const int x) const
	{
		if (x < 0 || x > MAX.x || y < 0 || y > MAX.y)
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
	void RenewGroundData();
	bool SearchBoss_FLOOD_FILL(int y, int x);

	void PrintGround()
	{
		for (size_t y = 0; y < MAX.y; y++)
		{
			for (size_t x = 0; x < MAX.x; x++)
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

	vector<Vector2> GetRemainGround() const
	{
		return m_RemainGround;
	}

	template<typename T>
	const vector<T> FindElementInVector(const vector<T>& indexs, const T& val
		, const function<const bool(const T&, const T&)> predicate);
	void EraseRemainGround(int y, int x);

	const bool IsContainInRemainGround(const int y, const int x);

private:
	Vector2 MAX = Vector2(20, 20);
	vector<Vector2> m_RemainGround;
	Node** m_findGround;
	Node** m_Ground;
};

template<typename T>
inline const vector<T> cGround::FindElementInVector(const vector<T>& indexs
	, const T& val, const function<const bool(const T&, const T&)> predicate)
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
