#pragma once
class cTexture;
class cTransform;

class cPrintWrapper
{
protected:

	template<typename T>
	class IPrintWrapper abstract
	{
	public:
		IPrintWrapper(T _Object) : Object(_Object) {}


		T GetElement() const
		{
			return Object;
		}

	private:
		T Object;
	};

	template<typename T>
	class IPrintPointerWrappper abstract
	{
	public:
		IPrintPointerWrappper(shared_ptr<T> pObject) : pObject(pObject) {}

		shared_ptr<T> GetElementPtr() const
		{
			return pObject;
		}


	private:
		shared_ptr<T> pObject;
	};
public:
	class cTransformPrint : public IPrintPointerWrappper<cTransform>
	{
	public:
		cTransformPrint(shared_ptr<cTransform> transform) : IPrintPointerWrappper(transform) {}
		void PrintTransform(const shared_ptr<cTransform> transfrom) const;
		friend std::ostream& operator<<(std::ostream& lhs, const cPrintWrapper::cTransformPrint& rhs);
	};

	class cTexturePrint : public IPrintPointerWrappper<cTexture>
	{
	public:
		cTexturePrint(shared_ptr<cTexture> texture) : IPrintPointerWrappper(texture) {}
		void PrintTexture(const shared_ptr<cTexture> ths) const;
		friend std::ostream& operator<<(std::ostream& lhs, const cPrintWrapper::cTexturePrint& rhs);
	};

	class cVector2Print : public IPrintWrapper<Vector2>
	{
	public:
		cVector2Print(Vector2 vector2) : IPrintWrapper(vector2) {}
		void PrintVector2(const Vector2 vector2) const;
		friend std::ostream& operator<<(std::ostream& lhs, const cPrintWrapper::cVector2Print rhs);
	};

};
