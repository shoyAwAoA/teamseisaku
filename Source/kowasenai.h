#pragma once
#include"Graphics/Model.h"
#include"Enemy.h"
#include"EnemyManager.h"
class kowasenai :public notEnemy
{
public:
    kowasenai();
    virtual ~kowasenai()override;
    //�X�V����
    void Update(float elapsedTime)override;
    //�`�揈��
    void Render(ID3D11DeviceContext* dc, Shader* shader)override;
    void MoveSpeed(float elapsedTime);
    //�f�o�b�O�pGUI�`��
   // void DrawDebugGUI();
private:
    Model* model = nullptr;
protected:
    //���S�����Ƃ��ɌĂ΂��
 //   void OnDead() {};
    void OnDead()override;
    //  void OnDamaged()override;
};