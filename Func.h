#pragma once
#include "Matrix4x4.h"

// X����]�s��
Matrix4x4 MakeRotateXMatrix(float radius);
// Y����]�s��
Matrix4x4 MakeRotateYMatrix(float radius);
// Z����]�s��
Matrix4x4 MakeRotateZMatrix(float radius);

// �s��̐�
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// 4x4�s��̐��l�\��
static const int kRowWidth = 60;
static const int kColumnHeight = 20;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

