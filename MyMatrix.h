#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

// 4x4行列の数値表示
static const int kRowWidth = 60;
static const int kColumnHeight = 20;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);