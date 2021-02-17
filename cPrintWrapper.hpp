#pragma once
class cTexture;
class cTransform;

class cPrintWrapper
{
protected:

	template<typename T>
	class IPrintWrappper abstract
	{
	public:
		IPrintWrappper(shared_ptr<T> pObject) : pObject(pObject) {}

		shared_ptr<T> GetElement() const
		{
			return pObject;
		}
	private:
		shared_ptr<T> pObject;
	};
public:
	class cTransformPrint : public IPrintWrappper<cTransform>
	{
	public:
		cTransformPrint(shared_ptr<cTransform> transform) : IPrintWrappper(transform) {}
		void PrintTransform(const shared_ptr<cTransform> transfrom) const;
		friend std::ostream& operator<<(std::ostream& lhs, const cPrintWrapper::cTransformPrint& rhs);
	};

	class cTexturePrint : public IPrintWrappper<cTexture>
	{
	public:
		cTexturePrint(shared_ptr<cTexture> texture) : IPrintWrappper(texture) {}
		void PrintTexture(const shared_ptr<cTexture> ths) const;
		friend std::ostream& operator<<(std::ostream& lhs, const cPrintWrapper::cTexturePrint& rhs);
	};

};
