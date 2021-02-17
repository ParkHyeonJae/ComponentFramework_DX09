#include "DXUT.h"
#include "cMath.h"

int Math::Random(int min, int max)
{
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());
    std::uniform_int_distribution<int> uid(min, max);
    return uid(mt);
}
template<typename T = float>
float Math::Random(T min, T max)
{
    return Random(static_cast<int>(min * 10000), static_cast<int>(max * 10000)) * 0.0001f;
}

float Math::Sign(float value)
{
    if (value > 0)
        return 0;
    else if (value < 0)
        return -1;
}

float Math::Clamp(float value, float _min, float _max)
{
    return min(_max, max(value, _min));
}

Vector2 Math::RotateVector2(Vector2 vector, float rot)
{
    float Rot = D3DXToRadian(rot);
    return Vector2(vector.x * cos(Rot) + vector.y * -sin(Rot), vector.x * sin(Rot) + vector.y * cos(Rot));
}

float Math::Distance(Vector2 vector)
{
    return D3DXVec2Length(&vector);
}

float Math::Direction(Vector2 from, Vector2 to)
{
    Vector2 diff = { from.x - to.x, from.y - to.y };
    return atan2(diff.y, diff.x);
}
