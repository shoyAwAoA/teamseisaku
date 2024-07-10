#include"EnemySlime.h"
#include"Graphics/Graphics.h"



//コンストラクタ
EnemySlime::EnemySlime()
{
    model = new Model("Data/Model/Slime/Slime.mdl");

    //モデルが大きいのでスケーリング
    scale.x = scale.y = scale.z = 0.1f;
    angle.y = 180.0f;
   /* position.y = 0;*/
    TransitionIdleState();
    //幅、高さ設定
    radius = 5.0f;
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
    //ステート毎の更新処理
    switch (state)
    {
    case State::Wander:
        UpdateWanderState(elapsedTime);
        break;
    case State::Idle:
        UpdateIdleState(elapsedTime);
        break;
    }

    if (health > 0)
    {
        radius = 5.0f;
    }
    else if (health <= 0)
    {
        radius = 0;
    }



    //速力処理更新
    UpdateVelocity(elapsedTime);

    //無敵時間更新
    UpdateInvincibleTimer(elapsedTime);

    //オブジェクト行列を更新
    UpdateTransform();

    MoveSpeed(elapsedTime);


    model->UpdateAnimation(elapsedTime);

    //モデル行列更新
    model->UpdateTransform(transform);
}

//描画処理
void EnemySlime::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    if (health > 0)
    {
        shader->Draw(dc, model);
    }
}

void EnemySlime::MoveSpeed(float elapsedTime)
{

    if (health > 0)
    {
        velocity.z = 0.5f;
        position.z -= velocity.z;
    }
}

//徘徊ステートへ遷移
void EnemySlime::TransitionWanderState()
{
    state = State::Wander;

    model->PlayAnimation(Anim_WalkFWD, true);
}
//徘徊ステート更新処理
void EnemySlime::UpdateWanderState(float elapsedTime)
{
}

//待機ステートへ遷移
void EnemySlime::TransitionIdleState()
{
    state = State::Idle;

    //待機アニメーション再生
    model->PlayAnimation(Anim_GetHit, true);
}

//待機アニメーション更新処理
void EnemySlime::UpdateIdleState(float elapsedTime)
{

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
