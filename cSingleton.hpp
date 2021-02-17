#pragma once

template<typename T, class B = IFlowInitializeBase>
class cSingleton
{
public:
	cSingleton() {}
	virtual ~cSingleton() {}

private:
	static T* instance;
public:
	static void CreateInstance()
	{
		instance = new T;

		if (dynamic_cast<B*>(instance) != NULL)
			instance->Init();
	}

	static T* GetInstance()
	{
		return instance;
	}

	static void ReleaseInstance()
	{
		if (dynamic_cast<B*>(instance) != NULL)
			instance->Release();
		delete instance;
	}
};
template<typename T, class B>
T* cSingleton<T, B>::instance = nullptr;