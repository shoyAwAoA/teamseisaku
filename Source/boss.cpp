#include "boss.h"

Boss::Boss()
{

    model = new Model("Data/Model/Boss/boss.mdl");

    //モデルが大きいのでスケーリング
    scale.x = scale.y = scale.z = 3.0f;

    angle.y=(DirectX::XMConvertToRadians(180));

    //幅、高さ設定
    radius = 5.0f;
    height = 1.0f;
    health = 10.0f;
}

Boss::~Boss()
{
    delete model;
}

void Boss::Update(float elapsedTime)
{
    //速力処理更新
    UpdateVelocity(elapsedTime);

    //無敵時間更新
    UpdateInvincibleTimer(elapsedTime);

    //オブジェクト行列を更新
    UpdateTransform();

    MoveSpeed(elapsedTime);

    //モデル行列更新
    model->UpdateTransform(transform);
}

void Boss::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);
}

void Boss::MoveSpeed(float elapsedTime)
{

}

void Boss::OnDead()
{
    //ここで勝利

}
