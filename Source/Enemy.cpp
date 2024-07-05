#include "Enemy.h"
#include"Graphics/Graphics.h"
#include"EnemyManager.h"



void Enemy::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

    //Õ“Ë”»’è—p‚ÌƒfƒoƒbƒO‹…‚ğ•`‰æ
//    debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

    debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}

void Enemy::DebugPrimitive()
{
	// ˆÊ’u
	ImGui::InputFloat3("Position", &position.x);
	// ”¼Œa
	ImGui::InputFloat("Radius", &radius);
	// ‚‚³
	ImGui::InputFloat("Height", &height);
	// Œ’N
	ImGui::InputInt("Health", &health);
}

//”jŠü
void Enemy::Destroy()
{
	EnemyManager::Instance().Remove(this);
}