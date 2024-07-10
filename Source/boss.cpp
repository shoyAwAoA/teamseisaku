#include<imgui.h>
#include "boss.h"

extern bool damage_flag;
extern bool boss_yarare_flag;

Boss::Boss()
{

    model = new Model("Data/Model/Boss/boss.mdl");

    //���f�����傫���̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 3.0f;

    angle.y=(DirectX::XMConvertToRadians(180));

    //���A�����ݒ�
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
    //���͏����X�V
    UpdateVelocity(elapsedTime);

    //���G���ԍX�V
    UpdateInvincibleTimer(elapsedTime);

    //�I�u�W�F�N�g�s����X�V
    UpdateTransform();

    MoveSpeed(elapsedTime);

    //���f���s��X�V
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
    if (damage_timer >> 3 & 0x01)//�_��
    {
        shader->Draw(dc, model);

    }

    ImGui::SetNextWindowPos(ImVec2(10, 100), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Boss", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
    {
        //�g�����X�t�H�[��

        ImGui::InputInt("Health", &health);

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
