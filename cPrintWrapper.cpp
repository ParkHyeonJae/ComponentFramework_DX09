#include "DXUT.h"
#include "cPrintWrapper.hpp"

std::ostream& operator<<(std::ostream& lhs, const cPrintWrapper::cTransformPrint& rhs)
{
	shared_ptr<cTransform> transform = rhs.GetElement();

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
	shared_ptr<cTexture> texture = rhs.GetElement();
	auto Info = texture->Info;
	lhs << "IsExistTexture = " << (texture != nullptr)
		<< ", Width = " << Info.Width
		<< ", Height = " << Info.Height;
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
