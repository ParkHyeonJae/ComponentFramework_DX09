#include "DXUT.h"
#include "cObjectManager.hpp"

void cObjectManager::PreInit()
{
    m_Objects.reserve(200);
}

void cObjectManager::Init()
{
    PreInit();
    for (int i = 0; i < m_Objects.size(); i += 1)
    {
        m_Objects[i]->Init();
    }
}

void cObjectManager::Release()
{
    for (int i = 0; i < m_Objects.size(); i += 1)
    {
        m_Objects[i]->Release();
    }

    ClearAllObject();

}

void cObjectManager::Update()
{
    #pragma omp parallel for
    for (int i = 0; i < m_Objects.size(); i += 1)
    {
        m_Objects[i]->Update();
    }
}

void cObjectManager::Render()
{
    //#pragma omp parallel for
    for (int i = 0; i < m_Objects.size(); i += 1)
    {
        m_Objects[i]->Render();
    }
}

void cObjectManager::ClearAllObject()
{
    m_Objects.clear();
}

shared_ptr<cObject> cObjectManager::CreateEmptyObject()
{
    //auto object = make_shared<cObject>(ArrayDeleter<cObject>());
    shared_ptr<cObject> object(new cObject);
    m_Objects.emplace_back(object);
    return object;
}
