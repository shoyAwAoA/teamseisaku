#include"ProjectileHoming.h"

//extern bool ran_flag0;
//extern bool ran_flag1;
//extern bool ran_flag2;
//extern bool ran_flag3;
//extern bool ran_flag4;

extern bool x0_flag;
extern bool x1_flag;
extern bool x2_flag;
extern bool x3_flag;
extern bool x4_flag;

//コンストラクタ
ProjectileHoming::ProjectileHoming(ProjectileManager* manager)
    :Projectile(manager)
{
    model = new Model("Data/Model/Sword/Sword.mdl");
    ue = false;
    //モデルが小さいのでスケーリング
    scale.x = scale.y = scale.z = 30.0f;
}

//デストラクタ
ProjectileHoming::~ProjectileHoming()
{
    delete model;
}

//更新処理
void ProjectileHoming::Update(float elapsedTime)
{
   // lifeTimer -= elapsedTime;
    ////寿命処理
    //if (lifeTimer < 0)
    //{
    //    Destroy();
    //}



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
                direction.x -= 0.0065f;
            }
            if (x1_flag)
            {
                direction.x -= 0.0035f;
            }
            if (x2_flag)
            {
            }
            if (x3_flag)
            {
                direction.x += 0.0035f;
            }
            if (x4_flag)
            {
                direction.x += 0.0065f;
            }
            direction.y += 0.0055f;
        }
        if (position.y> 25)
        {
            ue = true;
        }
        if (ue)
        {
            if (x0_flag)
            {
                direction.x += 0.0085f;
            }
            if (x1_flag)
            {
                direction.x += 0.0050f;
            }
            if (x2_flag)
            {  
            }
            if (x3_flag)
            {
                direction.x -= 0.0050f;
            }
            if (x4_flag)
            {
                direction.x -= 0.009f;
            }
            direction.y -= 0.0055f;
        }
    }

    //旋回
    {


        //float turnSpeed = this->turnSpeed * elapsedTime;
        ////ターゲットまでのベクトルを算出
        //DirectX::XMVECTOR Position = DirectX::XMLoadFloat3(&position);
        //DirectX::XMVECTOR Target = DirectX::XMLoadFloat3(&target);
        //DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Target,Position);

        ////ゼロベクトルでないなら回転処理
        //DirectX::XMVECTOR LengthSq = DirectX::XMVector3LengthSq(Vec);
        //float lengthSq;
        //DirectX::XMStoreFloat(&lengthSq, LengthSq);
        //if (lengthSq > 0.00001f)
        //{
        //    //ターゲットまでのベクトルを単位ベクトル化(正規化？）
        //    Vec = DirectX::XMVector3Normalize(Vec);

        //    //向いている方向ベクトルを算出
        //    DirectX::XMVECTOR Direction = DirectX::XMLoadFloat3(&direction);

        //   // 前方方向ベクトルとターゲットまでのベクトルの内積（角度）を算出
        //    DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(Direction, Vec);

        //    float dot;
        //    DirectX::XMStoreFloat(&dot, Dot);//VECTORからFLOAT3に変換

        //    //２つの単位ベクトルの角度が小さいほど
        //    //1.0に近づくという性質を利用して回転速度を調整する
        //    float rot = 1.0 - dot;
        //    if (rot > turnSpeed)//turnSpeed//回転速度？
        //    {
        //        rot = turnSpeed;
        //    }



        //    //回転角度があるなら回転処理をする
        //    //  //任意軸回転
        //    if (fabsf(rot)>0.0001f)//fabsfはfloat型の絶対値を計算するための関数
        //    {
        //        //回転軸を算出
        //        DirectX::XMVECTOR Axis = DirectX::XMVector3Cross(Direction,Vec);

        //        //回転軸と回転量から回転行列を算出
        //        DirectX::XMMATRIX Rotation = DirectX::XMMatrixRotationAxis(Axis, rot);

        //        //現在の行列を回転させる
        //        DirectX::XMMATRIX Transform = DirectX::XMLoadFloat4x4(&transform);
        //        Transform = DirectX::XMMatrixMultiply(Transform, Rotation);

        //            //回転後の前方方向を取り出し、単位ベクトル化する
        //        Direction = DirectX::XMVector3Normalize(Transform.r[2]);
        //            DirectX::XMStoreFloat3(&direction, Direction);
        //    }
        //}
    }

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