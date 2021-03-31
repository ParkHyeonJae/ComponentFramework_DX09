#include "DXUT.h"
#include "cPrintWrapper.hpp"

std::ostream& operator<<(std::ostream& lhs, const cPrintWrapper::cTransformPrint& rhs)
{
	shared_ptr<cTransform> transform = rhs.GetElementPtr();

	// TODO: insert return statement here
	lhs << "Name = " << transform->name
		<< ", Position: x = " << transform->position.x << " y = " << transform->position.y
		<< " Angle = " << transform->angle
		<< " Scale : x = " << transform->scale.x << " y = " << transform->scale.y;
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const cPrintWrapper::cTexturePrint& rhs)
{
	// TODO: insert return statement here
	shared_ptr<cTexture> texture = rhs.GetElementPtr();
	auto Info = texture->Info;
	lhs << "IsExistTexture = " << (texture != nullptr)
		<< ", Width = " << Info.Width
		<< ", Height = " << Info.Height;
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const cPrintWrapper::cVector2Print rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
	auto Info = rhs.GetElement();
	rhs.PrintVector2(Info);
	return lhs;
}

void cPrintWrapper::cTransformPrint::PrintTransform(const shared_ptr<cTransform> rhs) const
{
	std::cout << "Name = " << rhs->name
		<< ", Position: x = " << rhs->position.x << " y = " << rhs->position.y
		<< " Angle = " << rhs->angle
		<< " Scale : x = " << rhs->scale.x << " y = " << rhs->scale.y << "\n";
}

void cPrintWrapper::cTexturePrint::PrintTexture(const shared_ptr<cTexture> rhs) const
{
	std::cout << "IsExistTexture = " << (rhs != nullptr)
		<< ", Width = " << rhs->Info.Width
		<< ", Height = " << rhs->Info.Height;
}

void cPrintWrapper::cVector2Print::PrintVector2(const Vector2 vector2) const
{
	std::cout << "Vector2 : " << "x = " << vector2.x
		<< ", y = " << vector2.y;
}
