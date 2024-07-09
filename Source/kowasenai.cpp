#include "kowasenai.h"


//�R���X�g���N�^
kowasenai::kowasenai()
{
    model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");
    scale.x = scale.y = scale.z = 0.1f;

    radius = 5.0f;
    height = 2.0f;

}
kowasenai::~kowasenai()
{
    delete model;
}
void kowasenai::Update(float elapsedTime)
{
    if (health > 0)
    {
        radius = 4.0f;
    }
    else if (health <= 0)
    {
        radius = 0;
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
void kowasenai::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    if (health > 0)
    {
        shader->Draw(dc, model);
    }
    else if (health <= 0)
    {

    }
}
void kowasenai::MoveSpeed(float elapsedTime)
{
    if (health > 0)
    {
        velocity.z = 0.5f;
        position.z -= velocity.z;
    }
}

void kowasenai::OnDead()
{ 
    notEnemy::Destoroy();
}
