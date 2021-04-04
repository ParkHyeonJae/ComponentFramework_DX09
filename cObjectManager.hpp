#pragma once
class cObjectManager : public cSingleton<cObjectManager>, public IFlowBase
{
public:

	virtual void PreInit();

	// IFlowBase��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void ClearAllObject();
	shared_ptr<cObject> CreateEmptyObject();
private:
	vector<shared_ptr<cObject>> m_Objects;

};
#define OBJECT cObjectManager::GetInstance()