#include<imgui.h>
#include "boss.h"
#include"Graphics/Graphics.h"
#include"Effect.h"

extern bool damage_flag;
extern bool boss_yarare_flag;

int damage_timer = 60;


Effect* Boss_sinu=nullptr;

Boss::Boss()
{

    model = new Model("Data/Model/Boss/boss.mdl");
    
    Boss_sinu = new Effect("Data/Effect/Boss_Sinu.efk");

    //���f�����傫���̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 3.0f;

    angle.y=(DirectX::XMConvertToRadians(180));


    //���A�����ݒ�
    radius = 30.0f;
    height = 55.0f;
    health = 10.0f;
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
        if (health <=0)
        {
            boss_yarare_flag = true;
            Boss_sinu->Play()

        }
        damage_timer--;
        if (damage_timer <= 0)
        {
            damage_timer = 60;
            damage_flag = false;
        }
    }

   

    //���͏����X�V
    UpdateVelocity(elapsedTime);

    //���G���ԍX�V
    UpdateInvincibleTimer(elapsedTime);

    //�I�u�W�F�N�g�s����X�V
    UpdateTransform();

    MoveSpeed(elapsedTime);

    //���f���s��X�V
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
        Boss_Sinu = false;
    }
            
    

}

void Boss::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    if (damage_timer >> 3 & 0x02)//�_��
    {
        shader->Draw(dc, model);

    }


    ImGui::SetNextWindowPos(ImVec2(10, 100), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Boss", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
    {
        //�g�����X�t�H�[��

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

    //�����ŏ���
    //�����܂����B
}
