#pragma once

#include"Graphics/Model.h"
#include"Enemy.h"
#include"Audio/AudioSource.h"

//�X���C��
class EnemySlime :public Enemy
{
public:
    EnemySlime();
    ~EnemySlime()override;

    //�X�V����
    void Update(float elapsedTime)override;

    //�`�揈��
    void Render(ID3D11DeviceContext* dc, Shader* shader)override;

    void MoveSpeed(float elapsedTime);

    //�f�o�b�O�pGUI�`��
   // void DrawDebugGUI();

private:

    //�p�j�X�e�[�Ƃ֑J��
    void TransitionWanderState();

    //�p�j�X�e�[�g�X�V����
    void UpdateWanderState(float elapsedTime);
    
    //�ҋ@�X�e�[�g�֑J��
    void TransitionIdleState();

    //�ҋ@�X�e�[�g�X�V����
    void UpdateIdleState(float elapsedTime);

private:
    //�X�e�[�g
    enum class State
    {
        Wander,
        Idle,
        Die,
    };

    //�A�j���[�V����
    enum Animation
    {
        Anim_IdleNormal,
        Anim_IdleBattle,
        Anim_Attack1,
        Anim_Attack2,
        Anim_WalkFWD,
        Anim_WalkBWD,
        Anim_WalkLeft,
        Anim_WalkRight,
        Anim_RunFWD,
        Anim_SenseSomthingST,
        Anim_SenseSomthingPRT,
        Anim_Taunt,
        Anim_Victory,
        Anim_GetHit,
        Anim_Dizzy,
        Anim_Die
    };
private:
    Model* model=nullptr;
    State  state = State::Wander;
    DirectX::XMFLOAT3 targetPosition = { 0,0,0 };
    DirectX::XMFLOAT3 territoryOrigin = { 0,0,0 };
    float             territoryRange = 10.0f;
    float             moveSpeed = 3.0f;
    float             turnSpeed = DirectX::XMConvertToRadians(360);
    float             stateTimer = 0.0f;
protected:
    //���S�����Ƃ��ɌĂ΂��
    void OnDead()override;
  //  void OnDamaged()override;
    std::unique_ptr<AudioSource> zakosi_bgm;

};