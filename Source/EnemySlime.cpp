#include"EnemySlime.h"


//コンストラクタ
EnemySlime::EnemySlime()
{
    model = new Model("Data/Model/Slime/Slime.mdl");

    //モデルが大きいのでスケーリング
    scale.x = scale.y = scale.z = 0.01f;

    position.y = 0;

    //幅、高さ設定
    radius = 0.5f;
    height = 1.0f;
    health = 1.0f;
}

//デストラクタ
EnemySlime::~EnemySlime()
{
    delete model;
}

//更新処理
void EnemySlime::Update(float elapsedTime)
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

//描画処理
void EnemySlime::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);
}

void EnemySlime::MoveSpeed(float elapsedTime)
{
    velocity.z = 0.05f;
    position.z -= velocity.z;
}

//void EnemySlime::DrawDebugGUI()
//{
//    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
//    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
//
////    if (ImGui::Begin("EnemySlime", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
////    {
////        //トランスフォーム
////
////        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
////        {
////
////            //位置
////            ImGui::InputFloat3("Position", &position.x);
////            //回転
////            DirectX::XMFLOAT3 a;
////            a.x = DirectX::XMConvertToDegrees(angle.x);
////            a.y = DirectX::XMConvertToDegrees(angle.y);
////            a.z = DirectX::XMConvertToDegrees(angle.z);
////
////            ImGui::InputFloat3("Angle", &a.x);
////
////            angle.x = DirectX::XMConvertToRadians(a.x);
////            angle.y = DirectX::XMConvertToRadians(a.y);
////            angle.z = DirectX::XMConvertToRadians(a.z);
////
////            //スケール
////            ImGui::InputFloat3("Scale", &scale.x);
////
////            //HP
////            //ImGui::InputFloat("health", &health);
////        }
////    }
////    ImGui::End();
////
////}

//死亡した時に呼ばれる
void EnemySlime::OnDead()
{
   Destroy();
}

//void EnemySlime::OnDamaged()
//{
//}
