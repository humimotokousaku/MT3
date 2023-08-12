#include <Novice.h>
#include <stdint.h>
#include "MyMatrix.h"
#include "Collision.h"
#include "Segment.h"
#include "ImGuiManager.h"

const char kWindowTitle[] = "LE2B_22_フミモト_コウサク";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// 宣言
	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };

	Vector3 rotate{};
	Vector3 translate{};

	AABB aabb1{
		{-0.5f, -0.5f, -0.5f},
		{ 0.0f, 0.0f, 0.0f}
	};
	AABB aabb2{
		{0.2f, 0.2f, 0.2f},
		{ 1.0f, 1.0f, 1.0f}
	};

	uint32_t colorS1 = WHITE;
	uint32_t colorS2 = WHITE;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (IsCollision(aabb1, aabb2)) {
			colorS1 = RED;
		}
		else {
			colorS1 = WHITE;
		}

		// カメラ設定
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(1280) / float(720), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);

		ImGui::Begin("Debug");
		ImGui::DragFloat3("camera.Translate", &cameraTranslate.x, 0.1f, -50.0f, 50.0f);
		ImGui::DragFloat3("camera.Rotate", &cameraRotate.x, 0.1f, -50.0f, 50.0f);
		ImGui::DragFloat3("AABB1min", &aabb1.min.x, 0.1f, -1.0f, 5.0f);
		ImGui::DragFloat3("AABB1max", &aabb1.max.x, 0.1f, -1.0f, 5.0f);
		ImGui::DragFloat3("AABB2min", &aabb2.min.x, 0.1f, -1.0f, 5.0f);
		ImGui::DragFloat3("AABB2max", &aabb2.max.x, 0.1f, -1.0f, 5.0f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		DrawAABB(aabb1, worldViewProjectionMatrix, viewportMatrix, colorS1);
		DrawAABB(aabb2, worldViewProjectionMatrix, viewportMatrix, colorS2);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
