#pragma once
class cTransform : public cComponent
{
public:
	cTransform() = default;
	cTransform(cTransform& other) 
		: position(other.position)
		, scale(other.scale)
		, angle(other.angle)
		, name(other.name){}

	string name = "GameObject";
	Vector2 position = VECTOR2_ZERO;
	Vector2 scale = VECTOR2_ONE;
	float angle = 0;

	
};

