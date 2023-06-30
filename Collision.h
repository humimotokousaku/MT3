#pragma once
#include "Sphere.h"
#include "Plane.h"

// 球体同士の衝突判定
bool IsCollision(const Sphere& s1, const Sphere& s2);

// 球体と平面の衝突判定
bool IsCollision(const Sphere& s1, const Plane& s2);
