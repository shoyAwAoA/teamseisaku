#include<imgui.h>
#include "boss.h"
#include"Graphics/Graphics.h"
#include"Effect.h"

extern bool damage_flag;
extern bool boss_yarare_flag;

int damage_timer = 60;

bool Boss_Sinu = false;
bool Boss_T = false;

Effect* Boss_sinu=nullptr;

Boss::Boss()
{

    model = new Model("Data/Model/Boss/boss.mdl");
    
    Boss_sinu = new Effect("Data/Effect/Boss_Sinu.efk");

    //モデルが大きいのでスケーリング
    scale.x = scale.y = scale.z = 3.0f;

    angle.y=(DirectX::XMConvertToRadians(180));

    Boss_T = false;

    //幅、高さ設定
    radius = 30.0f;
    height = 55.0f;
    health = 10.0f;
    Boss_Sinu = false;
    damage_timer = 60;
}

Boss::~Boss()
{
    if (model != nullptr)
    {
        model = nullptr;
    delete model;
    }
}

void Boss::Update(float elapsedTime)
{
    if (damage_flag)
    {
        if (health ==0)
        {

            Boss_Sinu = true;
            health--;
            //boss_yarare_flag = true;
        }
        damage_timer--;
        if (damage_timer <= 0)
        {
            damage_timer = 60;
            damage_flag = false;
        }
    }

   

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

void Boss::BossSinu(bool Boss_Sinu)
{
    if (boss_sinu_timer > 180)
    {
        boss_yarare_flag = true;
        //Boss_T = false;
    }
        
        
    if (Boss_Sinu)
    {
        DirectX::XMFLOAT3 p = GetPosition();
        Boss_sinu->Play(p, 5);
        Boss_T = true;
        Boss_Sinu = false;
    }
            
    if (Boss_T)
    {
        boss_sinu_timer++;
    }
    

}

void Boss::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    if (damage_timer >> 3 & 0x02)//点滅
    {
        shader->Draw(dc, model);

    }


    ImGui::SetNextWindowPos(ImVec2(10, 100), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Boss", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
    {
        //トランスフォーム

        ImGui::InputInt("Health", &health);

        if (damage_flag)
        {
            ImGui::Checkbox(u8"damage_flag", &damage_flag);

        }
        else
        {
            ImGui::Checkbox(u8"damage_flag", &damage_flag);
        }

    }
  
        ImGui::End();
}

void Boss::MoveSpeed(float elapsedTime)
{
}


void Boss::OnDead()
{

    //ここで勝利
    //勝ちました。
}
