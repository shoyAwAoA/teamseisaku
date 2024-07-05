#include"Character.h"
//#include"Stage.h"
#include"Mathf.h"
#include"StageManager.h"
//�s��X�V����
void Character::UpdateTransform()
{
    //�X�P�[���s����쐬
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x,scale.y,scale.z);

    ////��]�s����쐬
    //DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.z,angle.y,angle.x);

    //��]�s����쐬
    DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);

    DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);

    DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);

    DirectX::XMMATRIX R = Y*X*Z;

    //�ʒu�s����쐬
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x,position.y,position.z);

    //3�̍s���g�ݍ��킹�A���[���h�s����쐬
    DirectX::XMMATRIX W = S * R * T;

    //�v�Z�������[���h�s������o��
    DirectX::XMStoreFloat4x4(&transform, W);

}
//�W�����v����
void Character::Jump(float speed)
{
    //������̗͂�ݒ�
    velocity.y = speed;
}

//���͏����X�V
void Character::UpdateVelocity(float elapsedTime)
{
    //�o�߃t���[��
    float elapsedFrame = 60.0f * elapsedTime;

    //�������͍X�V����
    UpdateVerticalVelocity(elapsedFrame);

    //�������͍X�V����
    UpdateHorizontalVelocity(elapsedFrame);

    //�����ړ��X�V����
    UpdateVerticalMove(elapsedTime);

    //�����ړ��X�V����
    UpdateHorizontalMove(elapsedTime);
}


void Character::UpdateVerticalVelocity(float elapsedFrame)
{
   //�d�͏���
    velocity.y += gravity * elapsedFrame;// position.y += gravity;

}
void Character::UpdateVerticalMove(float elapsedTime)
{
    ////�ړ�����
    //position.y += velocity.y * elapsedTime;

    ////�n�ʔ���
    //if (position.y < 0.0f)
    //{

    //    position.y = 0.0f;
    //    velocity.y = 0.0f;

    //    //���n����
    //    if (!isGround)
    //    {
    //        OnLanding();
    //    }
    //    else
    //    {
    //        isGround = true;
    //    }
    //}
    //else
    //{
    //    isGround = false;
    //}

    //���������̈ړ���
    float my = velocity.y * elapsedTime;

    //�L�����N�^�[��Y�������ƂȂ�@���x�N�g��
    DirectX::XMFLOAT3 normal = { 0,1,0 };

    //������
    if (my < 0.0f)
    {
        //���C�̊J�n�ʒu�͑�����菭����
        DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
        //���C�̏I�_�ʒu�͈ړ���̈ʒu
        DirectX::XMFLOAT3 end = { position.x,position.y + my,position.z };

        //���C�L���X�g�ɂ��n�ʔ���
        HitResult hit;
       // if (Stage::Instance().RayCast(start, end, hit))
        if(StageManager::Instance().RayCast(start,end,hit))
        {
            //�@���x�N�g���擾
            normal = hit.normal;

            //�n�ʐڒn���Ă���
           // position.y = hit.position.y;
            position = hit.position;

            angle.y += hit.rotation.y;
           //�X�Η��̌v�Z
            float normalLengthXZ=sqrtf(hit.normal.x*hit.normal.x+hit.normal.z*hit.normal.z);
            slopeRate=1.0f-(hit.normal.y / (normalLengthXZ + hit.normal.y));

            //���n����
            if (!isGround)
            {
                OnLanding();
            }
            isGround = true;
            velocity.y = 0.0f;
        }
        else
        {
            //�󒆂ɕ����Ă���
            position.y += my;
            isGround = false;
        }
    }
    //�㏸��
    else if (my > 0.0f)
    {   
        position.y += my;
        isGround = false;
    }
    //�n�ʂ̌����ɉ����悤��XZ����]
    {
        //Y�����@���x�N�g�������Ɍ����I�C���[�p��]���Z�o����
        float ax = atan2(normal.z,normal.y);
        float az = -atan2(normal.x, normal.y);

        //���`�⊮�Ŋ��炩�ɉ�]����
        angle.x=Mathf::Lerp(angle.x,ax,0.2f);
        angle.z=Mathf::Lerp(angle.z,az,0.2f);
    }

}

//�������͍X�V����
void Character::UpdateHorizontalVelocity(float elapsedFrame)
{
    //XZ���ʂ̑��͂���������
    float length = sqrtf(velocity.x*velocity.x+velocity.z*velocity.z);

    if (length > 0.0f)
    {
        //���C��
        float friction = this->friction * elapsedFrame;

        //�󒆂ɂ���Ƃ��͖��C�͂����炷
        if (!isGround)
        {
            friction*=airControl ;//0.3
        }

        //���C�ɂ�鉡�����̌�������
        if (length > friction)
        {
            //�P�ʃx�N�g��
            float vx = velocity.x / length;
            float vz = velocity.z / length;

            velocity.x -= vx * friction;
            velocity.z -= vz * friction;
        }
        else
        {
            velocity.x = 0.0f;
            velocity.z = 0.0f;
        }

    }
    //XZ���ʂ̑��͂���������
    if (length <= maxMoveSpeed)
    {
        //�ړ��x�N�g�����[���x�N�g���ł͂Ȃ��Ȃ��������
        float moveVecLength = sqrtf(moveVecX*moveVecX+moveVecZ*moveVecZ);
        if (moveVecLength > 0.0f)
        {
            //������
            float acceleration = this->acceleratio * elapsedFrame;
            //�ړ��x�N�g���ɂ���������
            velocity.x += moveVecX*acceleration;
            velocity.z += moveVecZ*acceleration;

            //�ő呬�x����
            float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
                if (length > maxMoveSpeed)
                {
                    float vx = velocity.x/length;
                    float vz = velocity.z/length;

                    velocity.x = vx*maxMoveSpeed;
                    velocity.z = vz*maxMoveSpeed;
                }
                //�����ŃK�^�K�^���Ȃ��悤�ɂ���
                if (isGround && slopeRate > 0.0f)
                {   
                    velocity.y -= length * slopeRate * elapsedFrame;
                }
        }
       
    }
    //�ړ��x�N�g�������Z�b�g
    moveVecX = 0.0f;
    moveVecZ = 0.0f;
}
//�����ړ��X�V����
void Character::UpdateHorizontalMove(float elapsedTime)
{
    //�ړ�����
    //position.x += velocity.x * elapsedTime;
    //position.z += velocity.z * elapsedTime;

    //�����ړ��ʌv�Z
    float velocityLengthXZ = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
    if (velocityLengthXZ > 0.0f)
    {
        // �����ړ��l
        float mx = velocity.x * elapsedTime;
        float mz = velocity.z * elapsedTime;

        //���C�̊J�n�ʒu�ƏI�_�ʒu
        DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
        DirectX::XMFLOAT3 end = { position.x+mx,position.y+stepOffset,position.z+mz };

        //���C�L���X�g�ɂ��ǔ���
        HitResult hit;
       // if (Stage::Instance().RayCast(start, end, hit))
        if(StageManager::Instance().RayCast(start,end,hit))
        {
            //�ǂ܂ł̃x�N�g��
            DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&start);
            DirectX::XMVECTOR End = DirectX::XMLoadFloat3(&end);
            DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(End, Start);

            //�ǂ̖@��
            DirectX::XMVECTOR Normal = DirectX::XMLoadFloat3(&hit.normal);

            //���˃x�N�g����@���Ɏˉe
            DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(DirectX::XMVectorNegate(Vec),Normal);//�x�N�g���Ɩ@���x�N�g�����g��

            //�␳�ʒu�̌v�Z
            DirectX::XMVECTOR CollectPosition = DirectX::XMVectorMultiplyAdd(Normal,Dot,End);
            DirectX::XMFLOAT3 collectPosition;
            DirectX::XMStoreFloat3(&collectPosition,CollectPosition);

            //�ǂ�������փ��C�L���X�g
            HitResult hit2;
         //   if (!Stage::Instance().RayCast(hit.position, collectPosition, hit2))
            if(!StageManager::Instance().RayCast(hit.position,collectPosition,hit2))
            {
                //�ǂ�������ŕǂɓ�����Ȃ�������␳�ʒu�Ɉړ�
                position.x = collectPosition.x;
                position.z = collectPosition.z;
            }
            else
            {
                position.x = hit2.position.x;
                position.z = hit2.position.z;
            }
        }
        else
        {
            //�ړ�
            position.x += mx;
            position.z += mz;
        }
    }
}
//���񏈗�
void Character::Turn(float elapsedTIme, float vx, float vz, float speed)
{
    speed *= elapsedTIme;

    //�i�s�x�N�g�����[���x�N�g���̏ꍇ�͏�������K�v�Ȃ�
    if (vx == 0 && vz == 0)return;

    //�i�s�x�N�g����P�ʃx�N�g����
    vx /= sqrtf(vx * vx + vz * vz);
    vz /= sqrtf(vx * vx + vz * vz);

    //���g�̉�]�l����O���������߂�
    float frontX = sinf(angle.y);
    float frontZ = cosf(angle.y);

    //��]�p�����߂邽�߁A�񂽂̒P�ʃx�N�g���̓��ς��v�Z����
    float dot = (vx * frontX) + (vz * frontZ);//����

    //���֍���-1.0�`�P�D�O�ŕ\������Ă���A��̒P�ʃx�N�g���̊p�x��
    //�������قǂP�D�O�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐߂���
    float rot = 1.0 - dot;// �␳�l

    //���E������s�����߂ɂQ�̒P�ʃx�N�g���̊O�ς��v�Z����
    float cross = (frontZ * vx) - (frontX * vz);
    //ctrl + h

    //�QD�̊O�ϒl�����̏ꍇ�����̏ꍇ�ɂ���č��E���肪�s����
    //���E������s�����Ƃɂ���č��E��]��I������
    if (cross < 0.0f)
    {
        //angle.y -= speed;
        angle.y -= rot * speed;
    }
    else
    {
        // angle.y += speed;
        angle.y += rot * speed;
    }
}
bool Character::ApplyDamage(int damage, float invincibleTime)
{
    //�_���[�W��0�̏ꍇ�͌��N��Ԃ�ύX����K�v���Ȃ�
    if (damage == 0)return false;
    
    //���S���Ă���ꍇ�͌��N��Ԃ�ύX���Ȃ�
    if (health <= 0)return false;


    if (invincibleTimer > 0.0f)return false;

    invincibleTimer = invincibleTime;

    //�_���[�W����

    health -= damage;

    //���S�ʒm
    if (health <= 0)
    {
        OnDead();//���S�����ꍇ�ɌĂ΂��
    }
    //�_���[�W�ʒm
    else
    {
        OnDamaged();//�_���[�W���󂯂����ɌĂ΂��
    }
    //���N��Ԃ��ύX�����ꍇ��true��Ԃ�
    return true;
}
void Character::UpdateInvincibleTimer(float elapsedTime)
{
    if (invincibleTimer > 0.0f)
    {
        invincibleTimer -= elapsedTime;
    }
}
//�Ռ���^����
void Character::AddImpulse(const DirectX::XMFLOAT3& impulse)
{
    //���͂ɗ͂�������
    velocity.x += impulse.x;
    velocity.y += impulse.y;
    velocity.z += impulse.z;
}
// �ړ�����
void Character::Move(float vx,float vz,float speed)
{
    /*speed *= elapsedTime;
    position.x += vx * speed;
    position.z += vz * speed;*/

    //�ړ������x�N�g����ݒ�
    moveVecX = vx;
    moveVecZ = vz;

    //�ő呬�x�ݒ�
    maxMoveSpeed = speed;
}