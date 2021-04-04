#pragma once

class cObject;
class cComponent
{
public:
	cComponent() {}
	virtual ~cComponent() {
	}


	virtual void Init();

	virtual void Release();

	virtual void Update();

	virtual void Render();

	bool IsEnable() const
	{
		return m_IsEnable;
	}

	void SetEnable(bool condition)
	{
		m_IsEnable = condition;
	}

	void SetOwner(cObject* owner)
	{
		m_Owner = owner;
	}

	cObject* GetOwner()
	{
		return m_Owner;
	}

	template<typename T>
	shared_ptr<T> AddComponent()
	{
		return m_Owner->AddComponent<T>();
	}

	template<typename T>
	shared_ptr<T> GetComponent()
	{
		return m_Owner->GetComponent<T>();
	}

private:
	cObject* m_Owner;
	bool m_IsEnable = true;
};

