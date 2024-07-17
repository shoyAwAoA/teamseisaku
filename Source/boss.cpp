#include<imgui.h>
#include "boss.h"
#include"Graphics/Graphics.h"
#include"Effect.h"

extern bool damage_flag;
extern bool boss_yarare_flag;

int damage_timer = 60;
int boss_sinu_timer = 0;
bool Boss_Sinu;
bool Boss_T;
bool Bosss;

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
    health = 1.0f;
    Boss_Sinu = false;
    damage_timer = 60;

    boss_sinu_timer = 0;
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
        if (health == 0)
        {
            //Boss_Sinu = true;
           // health--;
            //boss_yarare_flag = true;
        }
        damage_timer--;
        if (damage_timer <= 0)
        {
            damage_timer = 60;
            damage_flag = false;
        }
    }
    if (health == 0 && !Bosss)
    {
        Boss_Sinu = true;
        //health--;
        //boss_yarare_flag = true;
    }
    BossSinu();
    //速力処理更新
    UpdateVelocity(elapsedTime);
    //無敵時間更新
    UpdateInvincibleTimer(elapsedTime);
    //オブジェクト行列を更新
    UpdateTransform();
    MoveSpeed(elapsedTime);
    //モデル行列更新
    model->UpdateTransform(transform);
    if (health <= 0)
    {
        health = 0;
        boss_sinu_timer++;
    }
}

void Boss::BossSinu()
{
    if (boss_sinu_timer > 620)
    {
        boss_yarare_flag = true;
        Boss_T = false;
    }
    if (Boss_Sinu && !Bosss)
    {
        DirectX::XMFLOAT3 p = GetPosition();
        Boss_sinu->Play(p, 5);
        Boss_T = true;
        Boss_Sinu = false;
        Bosss = true;
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
        ImGui::InputInt("sinu_timer", &boss_sinu_timer);

        if (damage_flag)
        {
            ImGui::Checkbox(u8"damage_flag", &damage_flag);

        }
        else
        {
            ImGui::Checkbox(u8"damage_flag", &damage_flag);
        }
        if (Boss_Sinu)
        {
            ImGui::Checkbox(u8"boss_Sinu", &Boss_Sinu);
        }
        else
        {
            ImGui::Checkbox(u8"boss_Sinu", &Boss_Sinu);
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
