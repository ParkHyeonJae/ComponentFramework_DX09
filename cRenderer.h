#pragma once
class cRenderer : public cComponent
{
public:
	virtual void Init() override;

	virtual void Release() override;

	virtual void Update() override;

	virtual void Render() override;

	bool SetImage(string&& name);
	bool SetImage(string&& name, string&& path);
	constexpr bool IsExistTexture(cTexture * texture) const
	{
		return texture != nullptr;
	}

	constexpr cTexture* GetTexture() const
	{
		return texture;
	}
private:
	cTexture* texture = nullptr;
};

