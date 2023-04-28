#pragma once
#include "Matrix4x4.h"

// X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radius);
// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radius);
// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radius);

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// 4x4行列の数値表示
static const int kRowWidth = 60;
static const int kColumnHeight = 20;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);