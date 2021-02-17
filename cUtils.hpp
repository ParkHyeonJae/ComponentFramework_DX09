#pragma once

namespace Utils
{
	class cUtils
	{
	public:
		template<typename T, typename U, typename K>
		static U HasMapKey(map<T, U> &tMap, K key);
	};

	template<typename T, typename U, typename K>
	inline U cUtils::HasMapKey(map<T, U> &tMap, K key)
	{
		auto iter = tMap.find(key);
		if (iter != tMap.end())
			return tMap[key];
		return nullptr;
	}
}