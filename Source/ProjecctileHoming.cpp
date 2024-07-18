#include"ProjectileHoming.h"

extern bool x0_flag;
extern bool x1_flag;
extern bool x2_flag;
extern bool x3_flag;
extern bool x4_flag;

//�R���X�g���N�^
ProjectileHoming::ProjectileHoming(ProjectileManager* manager)
    :Projectile(manager)
{
    model = new Model("Data/Model/Enemy/teki.mdl");
    ue = false;
    //���f�����������̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 0.2f;
}

//�f�X�g���N�^
ProjectileHoming::~ProjectileHoming()
{
    delete model;
}

//�X�V����
void ProjectileHoming::Update(float elapsedTime)
{
    //�ړ�
    {
        float moveSpeed = this->moveSpeed * elapsedTime;
        position.x += direction.x * moveSpeed;
        position.y += direction.y * moveSpeed;
        position.z += direction.z * moveSpeed;

        //direction�͕����H
        if (!ue)
        {
            if (x0_flag)
            {
                direction.x -= 0.0095f;
            }
            if (x1_flag)
            {
                direction.x -= 0.0065f;
            }
            if (x2_flag)
            {
            }
            if (x3_flag)
            {
                direction.x += 0.0065f;
            }
            if (x4_flag)
            {
                direction.x += 0.0095f;
            }
            direction.y += 0.0065f;
        }
        if (position.y> 20)
        {
            ue = true;
        }
        if (ue)
        {
            if (x0_flag)
            {
                direction.x += 0.0145f;
            }
            if (x1_flag)
            {
                direction.x += 0.0070f;
            }
            if (x2_flag)
            {  
            }
            if (x3_flag)
            {
                direction.x -= 0.0070f;
            }
            if (x4_flag)
            {
                direction.x -= 0.0145f;
            }
            direction.y -= 0.0085f;
        }
    }
    //����
    
    //���݂̍s�����]������
    DirectX::XMMATRIX Transform = DirectX::XMLoadFloat4x4(&transform);
    
    //�I�u�W�F�N�g�s��̍X�V
    UpdateTransform();

    //���f���s��X�V
    model->UpdateTransform(transform);
}

//�`�揈��
void ProjectileHoming::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);
}

//����
void ProjectileHoming::Launch(const DirectX::XMFLOAT3& direction,
    const DirectX::XMFLOAT3& position,
    const DirectX::XMFLOAT3& target)
{
    this->direction = direction;
    this->position = position;
    this->target = target;

    UpdateTransform();
}