#pragma once

#include <stdafx.h>

inline float DegToRad(float deg)
{
    return deg * (3.14159265358979323846f / 180.0f);
}
inline float RadToDeg(float rad)
{
    return rad * (180.0f / 3.14159265358979323846f);
}


