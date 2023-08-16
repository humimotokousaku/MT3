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

	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point{ -1.5f,0.6f,0.6f };

	Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = ClosestPoint(point, segment);

	Sphere sphere2{ closestPoint,1.0f };

	Plane plane{ { 0.0f, 2.0f, 0.0f }, 1.0f };

	Triangle triangle{};
	triangle.vertices[0] = { -1,0,0 };
	triangle.vertices[1] = { 0,1,0 };
	triangle.vertices[2] = { 1,0,0 };

	unsigned int color;

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

		// 当たり判定
		if (!IsCollision(triangle, segment)) {
			color = WHITE;
		}
		else {
			color = RED;
		}

		// カメラ設定
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(1280) / float(720), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);

		Vector3 start = Transform(Transform(segment.origin, worldViewProjectionMatrix), viewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), worldViewProjectionMatrix), viewportMatrix);
		plane.normal = Normalize(plane.normal);
		ImGui::Begin("Window");
		ImGui::DragFloat3("Triangle.v0", &triangle.vertices[0].x, 0.01f);
		ImGui::DragFloat3("Triangle.v1", &triangle.vertices[1].x, 0.01f);
		ImGui::DragFloat3("Triangle.v2", &triangle.vertices[2].x, 0.01f);
		ImGui::DragFloat3("Segment.Origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("Segment.Diff", &segment.diff.x, 0.01f);
		ImGui::DragFloat3("Camera.Translate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("Camera.Rotate", &cameraRotate.x, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
		DrawTriangle(triangle, worldViewProjectionMatrix, viewportMatrix, color);

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
