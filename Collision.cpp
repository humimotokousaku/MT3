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

bool IsCollision(const Triangle& triangle, const Segment& segment) {
	Plane plane{};
	plane.normal = Normalize(
		Cross(
			Subtract(triangle.vertices[1], triangle.vertices[0]),
			Subtract(triangle.vertices[2], triangle.vertices[1])
		)
	);
	plane.distance = Dot(triangle.vertices[0], plane.normal);

	// 垂直な判定をとるために法線と線の内積をとる
	float dot = Dot(plane.normal, segment.diff);

	// 垂直な場合は平行であるため衝突はしていない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (0.0f < t && 1.0f > t) {
		// 衝突点pを求める
		Vector3 p = Add(segment.origin, Multiply(segment.diff, t));

		// 各辺を結んだベクトルと頂点と衝突点pを結んだベクトルのクロス積をとる
		Vector3 cross01 = Cross(
			Subtract(triangle.vertices[1], triangle.vertices[0]),
			Subtract(p, triangle.vertices[1])
		);

		Vector3 cross12 = Cross(
			Subtract(triangle.vertices[2], triangle.vertices[1]),
			Subtract(p, triangle.vertices[2])
		);

		Vector3 cross20 = Cross(
			Subtract(triangle.vertices[0], triangle.vertices[2]),
			Subtract(p, triangle.vertices[0])
		);

		// 全ての小三角形のクロス積と法線が同じ方向なら衝突している
		if (Dot(cross01, plane.normal) >= 0.0f &&
			Dot(cross12, plane.normal) >= 0.0f &&
			Dot(cross20, plane.normal) >= 0.0f) {

			return true;

		}

	}
	return false;
}
