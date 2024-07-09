#include "kowasenai.h"
//コンストラクタ
kowasenai::kowasenai()
{
    model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");
    scale.x = scale.y = scale.z = 0.1f;

    radius = 5.0f;
    height = 1.0f;

}
kowasenai::~kowasenai()
{
    delete model;
}
void kowasenai::Update(float elapsedTime)
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
void kowasenai::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);
}
void kowasenai::MoveSpeed(float elapsedTime)
{
    if (health > 0)
    {
        velocity.z = 0.5f;
        position.z -= velocity.z;
    }
}