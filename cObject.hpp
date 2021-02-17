#pragma once

enum class TagFlag
{
	TAG_NONE = 0b0000000,
	TAG_PLAYER,
	
	TAG_END,


	TAG_COUNT
};
class cComponent;
class cObject
{
public:

	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	cObject()
	{
		m_Tags.set(static_cast<size_t>(TagFlag::TAG_NONE));
		m_Components.reserve(10);

		transform = AddComponent<cTransform>();
	}
	virtual ~cObject() {}


	template<class T = cComponent>
	shared_ptr<T> AddComponent()
	{
		shared_ptr<T> instance = make_shared<T>();
		if (dynamic_pointer_cast<T>(instance) == nullptr)
			return nullptr;
		instance->SetOwner(this);
		m_Components.emplace_back(instance);
		instance->Init();
		return instance;
	}

	template<class T = cComponent>
	shared_ptr<T> GetComponent()
	{
		for (auto& iter : m_Components)
		{
			if (typeid(iter.get()) == typeid(T*))
				return static_pointer_cast<T>(iter);
		}
		shared_ptr<T> inst = nullptr;
		for (auto& iter : m_Components)
		{
			inst = dynamic_pointer_cast<T>(iter);
			if (inst != nullptr)
				return inst;
		}
		return inst;
	}

	vector<shared_ptr<cComponent>> GetComponents()
	{
		return m_Components;
	}
public:
	shared_ptr<cTransform> transform;
private:
	bitset<static_cast<size_t>(TagFlag::TAG_COUNT)> m_Tags;
	bool m_isDestroyed = false;
	
	vector<shared_ptr<cComponent>> m_Components;
};

