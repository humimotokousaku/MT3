#pragma once
#include "Sphere.h"
#include "Segment.h"
#include "Plane.h"
#include "Triangle.h"
#include "AABB.h"
#include <algorithm>

// 球体同士の衝突判定
bool IsCollision(const Sphere& s1, const Sphere& s2);

// 球体と平面の衝突判定
bool IsCollision(const Sphere& s1, const Plane& s2);

// 平面と線分の衝突判定
bool IsCollision(const Segment& segment, const Plane& plane);

// 三角形と線分の衝突判定
bool IsCollision(const Triangle& triangle , const Segment& segment);

// 三次元の衝突判定
bool IsCollision(const AABB& aabb1, const AABB& aabb2);

bool IsCollision(const AABB& aabb, const Sphere& sphere);