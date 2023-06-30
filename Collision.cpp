#include "Collision.h"
#include "MyMatrix.h"
#define _USE_MATH_DEFINES
#include <math.h>

bool IsCollision(const Sphere& s1, const Sphere& s2) {
	// 二つの球体の中心点間の距離を求める
	Vector3 dist{
		{s2.center.x - s1.center.x},
		{s2.center.y - s1.center.y},
		{s2.center.z - s1.center.z}
	};
	float distance = Length(dist);
	if (distance >= s1.radius + s2.radius) {
		// 当たってなかったら早期return
		return false;
	}
	// 半径の合計よりも短ければ衝突
	else if (distance <= s1.radius + s2.radius) {
		// 当たった処理
		return true;
	}
}

bool IsCollision(const Sphere& sphere, const Plane& plane) {
	float distance = fabs(Dot(plane.normal, sphere.center) - plane.distance);
	if (distance >= sphere.radius) {
		return false;
	}
	else if (distance <= sphere.radius) {
		return true;
	}
};

bool IsCollision(const Segment& segment, const Plane& plane) {
	float dot = Dot(plane.normal, segment.diff);

	// 垂直=平行であるので、衝突しているはずがない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;
	// tの値と線の種類によって衝突しているかを判断する
	if (t < 0 || t > 1.0f) {
		return false;
	}
	return true;

}