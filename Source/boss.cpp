#include "boss.h"

Boss::Boss()
{

    model = new Model("Data/Model/Boss/boss.mdl");

    //���f�����傫���̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 3.0f;



    //���A�����ݒ�
    radius = 5.0f;
    height = 1.0f;
    health = 1.0f;
}

Boss::~Boss()
{
    delete model;
}

void Boss::Update(float elapsedTime)
{
}

void Boss::Render(ID3D11DeviceContext* dc, Shader* shader)
{
}

void Boss::MoveSpeed(float elapsedTime)
{
}

void Boss::OnDead()
{
}
