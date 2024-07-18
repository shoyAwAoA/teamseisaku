#include"ProjectileHoming.h"

extern bool x0_flag;
extern bool x1_flag;
extern bool x2_flag;
extern bool x3_flag;
extern bool x4_flag;

//コンストラクタ
ProjectileHoming::ProjectileHoming(ProjectileManager* manager)
    :Projectile(manager)
{
    model = new Model("Data/Model/Enemy/teki.mdl");
    ue = false;
    //モデルが小さいのでスケーリング
    scale.x = scale.y = scale.z = 0.2f;
}

//デストラクタ
ProjectileHoming::~ProjectileHoming()
{
    delete model;
}

//更新処理
void ProjectileHoming::Update(float elapsedTime)
{
    //移動
    {
        float moveSpeed = this->moveSpeed * elapsedTime;
        position.x += direction.x * moveSpeed;
        position.y += direction.y * moveSpeed;
        position.z += direction.z * moveSpeed;

        //directionは方向？
        if (!ue)
        {
            if (x0_flag)
            {
                direction.x -= 0.0095f;
            }
            if (x1_flag)
            {
                direction.x -= 0.0065f;
            }
            if (x2_flag)
            {
            }
            if (x3_flag)
            {
                direction.x += 0.0065f;
            }
            if (x4_flag)
            {
                direction.x += 0.0095f;
            }
            direction.y += 0.0065f;
        }
        if (position.y> 20)
        {
            ue = true;
        }
        if (ue)
        {
            if (x0_flag)
            {
                direction.x += 0.0145f;
            }
            if (x1_flag)
            {
                direction.x += 0.0070f;
            }
            if (x2_flag)
            {  
            }
            if (x3_flag)
            {
                direction.x -= 0.0070f;
            }
            if (x4_flag)
            {
                direction.x -= 0.0145f;
            }
            direction.y -= 0.0085f;
        }
    }
    //旋回
    
    //現在の行列を回転させる
    DirectX::XMMATRIX Transform = DirectX::XMLoadFloat4x4(&transform);
    
    //オブジェクト行列の更新
    UpdateTransform();

    //モデル行列更新
    model->UpdateTransform(transform);
}

//描画処理
void ProjectileHoming::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);
}

//発射
void ProjectileHoming::Launch(const DirectX::XMFLOAT3& direction,
    const DirectX::XMFLOAT3& position,
    const DirectX::XMFLOAT3& target)
{
    this->direction = direction;
    this->position = position;
    this->target = target;

    UpdateTransform();
}