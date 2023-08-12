#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Segment.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include <stdint.h>

#pragma region 回転行列

// X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

#pragma endregion

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);

// 単位行列の生成
Matrix4x4  MakeIdentity4x4();

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2);

// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

// 積
Vector3 Multiply(const Vector3& v1, const Vector3& v2);

// スカラー倍
Vector3 Multiply(const Vector3& v1, float scale);

// 内積
float Dot(const Vector3& v1, const Vector3& v2);

// 長さ(ノルム)
float Length(const Vector3& v);

// 正規化
Vector3 Normalize(const Vector3& v);

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

// cross積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

// 正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2);

// 最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

// グリッド
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

// 球体
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color);

Vector3 Perpendicular(const Vector3& vector);

// 平面
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

static const int kRowWidth = 60;
static const int kColumnHeight = 20;
// 4x4行列の数値表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);
// 三次元ベクトルの数値表示
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);