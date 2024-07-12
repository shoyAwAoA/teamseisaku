#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"
#include"Character.h"
#include"ProjectileManager.h"
#include"Effect.h"

//�v���C���[
class Player :public Character
{
public:
    Player();
    ~Player()override;

    //�X�V����
    void Update(float elapsedTime);

    //�`�揈��
    void Render(ID3D11DeviceContext* dc, Shader* shader);

    //�f�o�b�O�pGUI�`��
    void DrawDebugGUI();

    //�f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive();

    ////�W�����v���͏���
    //void InputJump();

    //�e�ۂƓG�̏Փ˔��菈��
    void CollisionProjectilesVsEnemies();

    //�C���X�^���X�擾
    static Player& Instance();

protected:
    //���n�������ɌĂ΂��
    void OnLanding() override;

    ////�ړ����͏���
    //void InputMove(float elapsedTime);

    //�e�ۓ��͏���
    bool InputProjectile();

    //�v���C���[�ƃG�l�~�[�Ƃ̏Փ˔���
    void CollisionPlayerVsEnemies();

    void UpdateInvincibleTimer(float elapsedTime);

    //�_���[�W���󂯂����ɌĂ΂��
    void OnDamaged() override;

    //���S�������ɌĂ΂��
    void OnDead()override;

private:
    //�X�e�B�b�N���͒l����x�N�g�����擾
    DirectX::XMFLOAT3 GetMoveVec() const;

    //�ړ����͏���
    bool InputMove(float elapsedTime);

    //�W�����v���͏���
    bool InputJump();

    //�U�����͏���
    bool InputAttack();

    //�ҋ@�X�e�[�g�֑J��
    void TransitionIdleState();

    //�ҋ@�X�e�[�g�X�V����
    void UpdateIdleState(float elapsedTime);

    //�ړ��X�e�[�g�֑J��
    void TranstionMoveState();

    //�ړ��X�e�[�g�X�V����
    void UpdateMoveState(float elapsedTime);

    //�W�����v�X�e�[�g�֑J��
    void TransitionJumpState();

    //�W�����v�X�e�[�g�X�V����
    void UpdateJumpState(float elapsedTime);

    //���n�X�e�[�g�֑J��
    void TransitionLandState();

    //���n�X�e�[�g�X�V����
    void UpdateLandState(float elapsedTime);

    //�U���X�e�[�g�֑J��
    void TransitionAttackState();

    //�U���X�e�[�g�X�V����
    void UpdateAttackState(float elapsedTime);

    //�_���[�W�X�e�[�g�֑J��
    void TransitionDamageState();

    //�_���[�W�X�e�[�g�֍X�V����
    void UpdateDamageState(float elapsedTime);

    //���S�X�e�[�g�֑J��
    void TransitionDeathState();

    //���S�X�e�[�g�X�V����
    void UpdateDeathState(float elapsedTime);

    //�m�[�h�ƃG�l�~�[�̏Փˏ���
    void CollisionNodeVsEnemies(const char* nodeName, float nodeRadius);

    //�����X�e�[�g�֑J��
    void TransitionReviveState();

    //�����X�e�[�g�X�V����
    void UpdateReviceState(float elapsedTime);

private:
    //�X�e�[�g
    enum class State
    {
        Idle,
        Move,
        Jump,
        Land,
        Attack,
        Damage,
        Death,
        Revive,
    };

private:

    //�A�j���[�V����
    enum Animation
    {
        Anim_Idle,
        Anim_Hidari,
        Anim_Migi,
        Anim_Attack,
        Anim_Death,
        Anim_GetHit1,
        Anim_GetHit2,
        Anim_Falling,
        Anim_Jump,
        Anim_Jump_Flip,
        Anim_Landing,
        Anim_Revive,
        Anim_Running,
        Anim_Walking
    };

    Model* model = nullptr;

    float moveSpeed = 15.0f;

    float        jumpSpeed = 1.0f;
   
    float       turnSpeed = DirectX::XMConvertToRadians(720);

    float       leftHandRadius = 3.0f;

    int          jumpCount = 0;

    int          jumpLimit = 2;

    //�A�j���[�V�����̍Đ����Ԏ擾���A�Փ˔���𔭐������鎞�Ԃ𐧌�
    bool         attackCollisitonFlag = false;

    bool         moveMigiFlag = false;

    bool         moveHidariFlag = false;

    bool         bossFlag = false;

    bool         deathFlag = false;

   // int          interval = 15;

    bool         interval_flag = true;

    ProjectileManager   projectileManager;

    Effect* hitEffect = nullptr;

    int          player_pos = 0;

    State       state = State::Idle;
};

