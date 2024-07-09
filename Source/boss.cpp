#include "boss.h"

Boss::Boss()
{

    model = new Model("Data/Model/Boss/boss.mdl");

    //���f�����傫���̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 3.0f;

    angle.y=(DirectX::XMConvertToRadians(180));

    //���A�����ݒ�
    radius = 5.0f;
    height = 1.0f;
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
}

void Boss::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);
}

void Boss::MoveSpeed(float elapsedTime)
{

}

void Boss::OnDead()
{
    //�����ŏ���

}
