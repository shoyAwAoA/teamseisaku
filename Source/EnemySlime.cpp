#include"EnemySlime.h"
#include"Graphics/Graphics.h"
#include"Audio/Audio.h"
#include"SceneGame.h"



extern Effect* hitEffect;

Effect* kurogiri = nullptr;
extern  bool player_yarare_flag;
extern  int  owari_timer;
bool Effect0_flag;
bool Effect1_flag;
bool Effect2_flag;
bool Effect3_flag;
bool Effect4_flag;
bool effect_flag ;

int count = 0;

//コンストラクタ
EnemySlime::EnemySlime()
{
    Audio& audioManager = Audio::Instance();
    model = new Model("Data/Model/Enemy/teki.mdl");
    zako = 0;
    zako_flag = false;
    idle_timer = 0;
    idle_flag = true;
    effect_flag = true;
    

    //モデルが大きいのでスケーリング
    scale.x = scale.y = scale.z = 0.2f;
    angle.y = DirectX::XMConvertToRadians(180);
    //angle.y = 180.0f;
   /* position.y = 0;*/
    //TransitionIdleState();
    TransitionWanderState();

   /* kurogiri->Stopp();*/

    zakosi_bgm = audioManager.LoadAudioSource("Data/Audio/zakosi.wav");
   

    //エフェクトの読み込み
    kurogiri = new Effect("Data/Effect/kurogiri2.efk");


   
    //幅、高さ設定
    radius = 5.0f;
    height = 5.0f;
    health = 1.0f;
}

//デストラクタ
EnemySlime::~EnemySlime()
{
    if (model != nullptr)
    {
        model = nullptr;
        delete model;
    }

}

//更新処理
void EnemySlime::Update(float elapsedTime)
{
    //if (player_yarare_flag)
    //{
    //    //Effect_death();
    //    owari_timer++;
    //   /* owari = true;*/
    //}
   
    //ステート毎の更新処理
    switch (state)
    {
    case State::Wander:
        UpdateWanderState(elapsedTime);
        break;
    case State::Idle:
        UpdateIdleState(elapsedTime);
        break;
    case State::Move:
        UpdateMoveState(elapsedTime);
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

    if (position.z<-140)
    {
        Destroy();
    }

    //if (state==State::Move&&idle_flag==false&&idle_timer>90)
    //{

    //    Effect_death(GetType());
    //}
  //  Effect_create();

    Effect_flag(idle_timer, idle_flag, count);
    //速力処理更新
    UpdateVelocity(elapsedTime);

    //無敵時間更新
    UpdateInvincibleTimer(elapsedTime);

    //オブジェクト行列を更新
    

    //MoveSpeed(elapsedTime);

    
    UpdateTransform();
    model->UpdateAnimation(elapsedTime);
    model->UpdateTransform(transform);

    
  
    //モデル行列更新

   

    idle_timer++;
}


//描画処理
void EnemySlime::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    if (health > 0&&state!=State::Wander)
    {
        shader->Draw(dc, model);
    }

    if (ImGui::Begin("Idle_flag", nullptr, ImGuiWindowFlags_None))
    {

        if (idle_flag)
        {
            ImGui::Checkbox(u8"Idle_flag", &idle_flag);
        }
        else
        {
            ImGui::Checkbox(u8"Idle_flag", &idle_flag);
        }
        ImGui::InputInt("Idle_Timer", &idle_timer);
        ImGui::InputInt("count", &count);
     
      
    }
    ImGui::End();

}

void EnemySlime::MoveSpeed(float elapsedTime)
{
   
    if (health > 0)
    {
       // velocity.z = 0.85f;
        velocity.z = 1.7f;
        position.z -= velocity.z;
    }
}

//エフェクトステートへ遷移
void EnemySlime::TransitionWanderState()
{
    state = State::Wander;
   // model->PlayAnimation(Anim_WalkFWD, true);
}
//エフェクトステート更新処理
void EnemySlime::UpdateWanderState(float elapsedTime)
{
    
    if (effect_timer <= 90)
    {

        // if (GetType() == 0)
        if (effect_flag)
        {

            Effect_create();

        }
    }
    if (effect_timer > 90)
    {
        TransitionIdleState();
    }
    effect_timer++;
}

//待機ステートへ遷移
void EnemySlime::TransitionIdleState()
{
    state = State::Idle;

    //待機アニメーション再生
    model->PlayAnimation(Anim_IdleNormal, true);
}

//待機アニメーション更新処理
void EnemySlime::UpdateIdleState(float elapsedTime)
{

   // if (idle_timer <= 90)
   // {
   //        
   //    // if (GetType() == 0)
   //     if(idle_flag)
   //     {
   //       
   //             Effect_create();
   //      
   //     }
   // }
   // 
   //// else if(idle_timer>90)
    //else if(!idle_flag&&idle_timer>90)
   
     
        if (idle_timer > 120&&!idle_flag) { 
           
            TransitionMoveState();
            idle_timer = 0;
        }
       
       //idle_timer = 0;
    
    
    ++idle_timer;
}

//移動ステートへ遷移
void EnemySlime::TransitionMoveState()
{
    state = State::Move;
 
    //移動アニメーション再生
    model->PlayAnimation(Anim_WalkBWD, true);
}

void EnemySlime::Effect_create()
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    int EffectCount = kurogiri->GetEffectCount();
    int enemy_Count=enemyManager.GetEnemyCount();
  

    for (int i = 0; i < enemy_Count; ++i)
    {
        if (Effect_flag(idle_timer, idle_flag, count))
        {
            if (owari_timer==0)
            {
                if (GetType() == 0)
                {
                    DirectX::XMFLOAT3 p = { 0,0,90 };
                    p.y += 2.5f;
                    kurogiri->Play(p, 8);

                    idle_flag = false;
                    effect_flag = false;
                }
                if (GetType() == 1)
                {
                    DirectX::XMFLOAT3 p = { 12,0,90 };
                    p.y += 2.5f;
                    kurogiri->Play(p, 8);

                    idle_flag = false;
                    effect_flag = false;
                }
                if (GetType() == 2)
                {
                    DirectX::XMFLOAT3 p = { 24,0,90 };
                    p.y += 2.5f;
                    kurogiri->Play(p, 8);

                    idle_flag = false;
                    effect_flag = false;
                }
                if (GetType() == 3)
                {
                    DirectX::XMFLOAT3 p = { 36,0,90 };
                    p.y += 2.5f;
                    kurogiri->Play(p, 8);

                    idle_flag = false;
                    effect_flag = false;
                }
                if (GetType() == 4)
                {
                    DirectX::XMFLOAT3 p = { 48,0,90 };
                    p.y += 2.5f;
                    kurogiri->Play(p, 8);

                    idle_flag = false;
                    effect_flag = false;
                }
            }
          
        };

    }
}

void EnemySlime::reset()
{
    //count = 0;
   /* idle_flag = true;
    idle_timer = 0;*/
   // count = 0;
 /*    kurogiri->Stopp();
    kurogiri->Stopp();*/
}


void EnemySlime::Effect_death()
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    int EffectCount = kurogiri->GetEffectCount();
    int enemy_Count = enemyManager.GetEnemyCount();
   // int enemyCount = enemyManager.Instance().GetEnemyCount();

    for (int i = 0; i < enemy_Count; ++i)
    {
        if (!Effect_flag(idle_timer, idle_flag, count))
        {
            if (GetType() == 0)
            {
               
                kurogiri->Stop(count);
                effect_flag=true;
                idle_flag = true;
            }
            if (GetType() == 1)
            {
          
                kurogiri->Stop(count);
                effect_flag = true;
                idle_flag = true;
                //  TransitionMoveState();
            }
            if (GetType() == 2)
            {
            
                kurogiri->Stop(count);
                effect_flag = true;
                idle_flag = true;
                //  TransitionMoveState();
            }
            if (GetType() == 3)
            {
           
                kurogiri->Stop(count);
                effect_flag = true;
                idle_flag = true;
                //  TransitionMoveState();
            }
            if (GetType() == 4)
            {
             
                kurogiri->Stop(count);
                effect_flag = true;
                idle_flag = true;
                // TransitionMoveState();
            }
        

        }
    }
}

bool EnemySlime::Effect_flag(int efc_timer, bool efc_flag,int count)
{
    if (efc_timer <= 90 && efc_flag)
    {
        return true;
    }
    else if (efc_timer > 90&&!efc_flag)
    {
        return false;
    }
}

//移動アニメーション更新処理
void EnemySlime::UpdateMoveState(float elapsedTime)
{
    if (idle_timer > 90 && !idle_flag) {
        Effect_death();
        count++;
    }

    //idle_timer = 0;


    ++idle_timer;
    MoveSpeed(elapsedTime);

    
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
    if (!zako_flag)
    {
        zako_flag = true;
    }
    if (zako_flag)
    {
        if (zako <= 50)
        {
            zakosi_bgm->Play(false, 12.0f);
        }
        else if (zako > 50)
        {
            zako = 0;
            zako_flag = false;
        }
        zako++;
    }
    /*if (zakosi_bgm)
    {
    }*/
   Destroy();
}

//void EnemySlime::OnDamaged()
//{
//}
