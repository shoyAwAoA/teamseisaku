#pragma once

#include"Graphics/Shader.h"


//�O���錾�@�@���݃C���N���[�h���Ȃ��悤�ɑO���錾����
class ProjectileManager;

//�e��
class Projectile
{
public:
  //  Projectile() {}
    Projectile(ProjectileManager* manager);//�o�^�����}�l�[�W���[��ێ�����悤�ɂ���
    virtual ~Projectile() {}

    //�X�V����
    virtual void Update(float elapsedTime) = 0;

    //�`�揈��
    virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

    //�f�o�b�O�v���~�e�B�u�`��
    virtual void DrawDebugPrimitive();

    //�ʒu�擾
    const DirectX::XMFLOAT3& GetPosition() const { return position; }

    //�����擾
    const DirectX::XMFLOAT3& GetDirection()const { return direction; }

    //�X�P�[���擾
    const DirectX::XMFLOAT3& GetScale() const { return scale; }

    //�j��
    void Destroy();

    //���a�擾
    float GetRadius() const { return radius; }

protected:
    //�s��X�V
    void UpdateTransform();
protected:
    DirectX::XMFLOAT3       position = { 0,0,0 };
    DirectX::XMFLOAT3       direction = { 0,2.5f,1 };
    DirectX::XMFLOAT3       scale = { 1,1,1 };
    DirectX::XMFLOAT4X4     transform = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1 };

    ProjectileManager* manager = nullptr;

    float radius = 0.5f;
};