#include "Collision.h"
#define _USE_MATH_DEFINES

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