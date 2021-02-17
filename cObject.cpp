#include "DXUT.h"
#include "cObject.hpp"

void cObject::Init()
{
}


void cObject::Update()
{
	for (auto& iter : m_Components)
	{
		if (iter->IsEnable())
			iter->Update();
	}
}

void cObject::Render()
{
	for (auto& iter : m_Components)
	{
		if (iter->IsEnable())
			iter->Render();
	}
}

void cObject::Release()
{
	for (auto& iter : m_Components)
	{
		iter->Release();
	}
}