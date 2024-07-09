#include "Enemy.h"
#include"Graphics/Graphics.h"
#include"EnemyManager.h"



void Enemy::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

    //衝突判定用のデバッグ球を描画
//    debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

    debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}

void Enemy::DebugPrimitive()
{
	// 位置
	ImGui::InputFloat3("Position", &position.x);
	// 半径
	ImGui::InputFloat("Radius", &radius);
	// 高さ
	ImGui::InputFloat("Height", &height);
	// 健康
	ImGui::InputInt("Health", &health);
}

//破棄
void Enemy::Destroy()
{
	EnemyManager::Instance().Remove(this);
}

void notEnemy::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//衝突判定用のデバッグ球を描画
//    debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

	debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}
