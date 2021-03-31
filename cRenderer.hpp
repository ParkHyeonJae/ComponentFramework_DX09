#pragma once
class cRenderer : public cComponent
{
public:
	virtual void Init() override;

	virtual void Release() override;

	virtual void Update() override;

	virtual void Render() override;

	bool SetSprite(string&& name);
	bool SetSprite(string&& name, string&& path);
	bool IsExistTexture(const shared_ptr<cTexture> texture) const
	{
		return texture != nullptr;
	}

	shared_ptr<cTexture> GetTexture() const
	{
		return texture;
	}
protected:
	shared_ptr<cTexture> texture = nullptr;
};

