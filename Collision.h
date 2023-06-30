#pragma once
#include "Sphere.h"
#include "Segment.h"
#include "Plane.h"

// 球体同士の衝突判定
bool IsCollision(const Sphere& s1, const Sphere& s2);

// 球体と平面の衝突判定
bool IsCollision(const Sphere& s1, const Plane& s2);

// 平面と線分の衝突判定
bool IsCollision(const Segment& segment, const Plane& plane);