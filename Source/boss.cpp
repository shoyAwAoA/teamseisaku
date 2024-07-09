#include "boss.h"

Boss::Boss()
{

    model = new Model("Data/Model/Boss/boss.mdl");

    //モデルが大きいのでスケーリング
    scale.x = scale.y = scale.z = 3.0f;



    //幅、高さ設定
    radius = 5.0f;
    height = 1.0f;
    health = 1.0f;
}

Boss::~Boss()
{
    delete model;
}

void Boss::Update(float elapsedTime)
{
}

void Boss::Render(ID3D11DeviceContext* dc, Shader* shader)
{
}

void Boss::MoveSpeed(float elapsedTime)
{
}

void Boss::OnDead()
{
}
