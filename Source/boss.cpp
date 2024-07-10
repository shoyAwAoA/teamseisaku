#include<imgui.h>
#include "boss.h"

extern bool damage_flag;
extern bool boss_yarare_flag;

Boss::Boss()
{

    model = new Model("Data/Model/Boss/boss.mdl");

    //モデルが大きいのでスケーリング
    scale.x = scale.y = scale.z = 3.0f;

    angle.y=(DirectX::XMConvertToRadians(180));

    //幅、高さ設定
    radius = 20.0f;
    height = 20.0f;
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

    if (damage_flag)
    {
        if (health <= 0)
        {
            boss_yarare_flag = true;
        }
        else
        {
            damage_timer--;
        if (damage_timer <= 0)
        {
            damage_timer = 60;
            damage_flag = false;
        }

        }
    }

}

void Boss::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    if (damage_timer >> 3 & 0x01)//点滅
    {
        shader->Draw(dc, model);

    }

    ImGui::SetNextWindowPos(ImVec2(10, 100), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Boss", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
    {
        //トランスフォーム

        ImGui::InputInt("Health", &health);

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
