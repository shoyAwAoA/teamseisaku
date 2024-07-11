#include"ProjectileHoming.h"

//extern bool ran_flag0;
//extern bool ran_flag1;
//extern bool ran_flag2;
//extern bool ran_flag3;
//extern bool ran_flag4;

extern bool x0_flag;
extern bool x1_flag;
extern bool x2_flag;
extern bool x3_flag;
extern bool x4_flag;

//�R���X�g���N�^
ProjectileHoming::ProjectileHoming(ProjectileManager* manager)
    :Projectile(manager)
{
    model = new Model("Data/Model/Sword/Sword.mdl");
    ue = false;
    //���f�����������̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 30.0f;
}

//�f�X�g���N�^
ProjectileHoming::~ProjectileHoming()
{
    delete model;
}

//�X�V����
void ProjectileHoming::Update(float elapsedTime)
{
   // lifeTimer -= elapsedTime;
    ////��������
    //if (lifeTimer < 0)
    //{
    //    Destroy();
    //}



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
                direction.x -= 0.0065f;
            }
            if (x1_flag)
            {
                direction.x -= 0.0035f;
            }
            if (x2_flag)
            {
            }
            if (x3_flag)
            {
                direction.x += 0.0035f;
            }
            if (x4_flag)
            {
                direction.x += 0.0065f;
            }
            direction.y += 0.0055f;
        }
        if (position.y> 25)
        {
            ue = true;
        }
        if (ue)
        {
            if (x0_flag)
            {
                direction.x += 0.0085f;
            }
            if (x1_flag)
            {
                direction.x += 0.0050f;
            }
            if (x2_flag)
            {  
            }
            if (x3_flag)
            {
                direction.x -= 0.0050f;
            }
            if (x4_flag)
            {
                direction.x -= 0.009f;
            }
            direction.y -= 0.0055f;
        }
    }

    //����
    {


        //float turnSpeed = this->turnSpeed * elapsedTime;
        ////�^�[�Q�b�g�܂ł̃x�N�g�����Z�o
        //DirectX::XMVECTOR Position = DirectX::XMLoadFloat3(&position);
        //DirectX::XMVECTOR Target = DirectX::XMLoadFloat3(&target);
        //DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Target,Position);

        ////�[���x�N�g���łȂ��Ȃ��]����
        //DirectX::XMVECTOR LengthSq = DirectX::XMVector3LengthSq(Vec);
        //float lengthSq;
        //DirectX::XMStoreFloat(&lengthSq, LengthSq);
        //if (lengthSq > 0.00001f)
        //{
        //    //�^�[�Q�b�g�܂ł̃x�N�g����P�ʃx�N�g����(���K���H�j
        //    Vec = DirectX::XMVector3Normalize(Vec);

        //    //�����Ă�������x�N�g�����Z�o
        //    DirectX::XMVECTOR Direction = DirectX::XMLoadFloat3(&direction);

        //   // �O�������x�N�g���ƃ^�[�Q�b�g�܂ł̃x�N�g���̓��ρi�p�x�j���Z�o
        //    DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(Direction, Vec);

        //    float dot;
        //    DirectX::XMStoreFloat(&dot, Dot);//VECTOR����FLOAT3�ɕϊ�

        //    //�Q�̒P�ʃx�N�g���̊p�x���������ق�
        //    //1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐�����
        //    float rot = 1.0 - dot;
        //    if (rot > turnSpeed)//turnSpeed//��]���x�H
        //    {
        //        rot = turnSpeed;
        //    }



        //    //��]�p�x������Ȃ��]����������
        //    //  //�C�ӎ���]
        //    if (fabsf(rot)>0.0001f)//fabsf��float�^�̐�Βl���v�Z���邽�߂̊֐�
        //    {
        //        //��]�����Z�o
        //        DirectX::XMVECTOR Axis = DirectX::XMVector3Cross(Direction,Vec);

        //        //��]���Ɖ�]�ʂ����]�s����Z�o
        //        DirectX::XMMATRIX Rotation = DirectX::XMMatrixRotationAxis(Axis, rot);

        //        //���݂̍s�����]������
        //        DirectX::XMMATRIX Transform = DirectX::XMLoadFloat4x4(&transform);
        //        Transform = DirectX::XMMatrixMultiply(Transform, Rotation);

        //            //��]��̑O�����������o���A�P�ʃx�N�g��������
        //        Direction = DirectX::XMVector3Normalize(Transform.r[2]);
        //            DirectX::XMStoreFloat3(&direction, Direction);
        //    }
        //}
    }

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