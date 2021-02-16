#include "DXUT.h"
#include "cObjectManager.h"

void cObjectManager::Init()
{
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
}

void cObjectManager::Update()
{
    //#pragma omp parallel for
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

shared_ptr<cObject> cObjectManager::Instantiate(shared_ptr<cObject> object)
{
    shared_ptr<cObject> newObject = CreateEmptyObject();

    newObject->transform->position = object->transform->position;
    newObject->transform->angle = object->transform->angle;
    newObject->transform->scale = object->transform->scale;
    newObject->transform->name = object->transform->name;

    newObject->transform->name += (" (Clone)");

    newObject->GetComponents() = (object->GetComponents());
    //for (auto iter : object->GetComponents())
    //{
    //    newObject->AddComponent(iter);
    //}
    return newObject;
}

shared_ptr<cObject> cObjectManager::CreateEmptyObject()
{
    shared_ptr<cObject> object = make_shared<cObject>();
    m_Objects.emplace_back(object);
    return object;
}
