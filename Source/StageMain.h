#pragma once

//#include"Graphics/Shader.h"
#include"Graphics/Model.h"
//#include"Collision.h"
#include"Stage.h"

//�X�e�[�W

//���C���X�e�[�W
//class Stage
class StageMain:public Stage
{
public:
    //Stage();
    StageMain();
    //~Stage();
    ~StageMain();

    //�X�V����
    //void Update(float elapsedTime);
    void Update(float elapsedTime)override;

    //�`�揈��
    //void Render(ID3D11DeviceContext* dc, Shader* shader);
    void Render(ID3D11DeviceContext* dc, Shader* shader)override;
    //���C�L���X�g
    //bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);
    bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override;
    //�C���X�^���X�擾
  //  static Stage& Instance();
private:
    Model* model = nullptr;
};