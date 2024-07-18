#include<imgui.h>
#include"Player.h"
#include"Input/Input.h"
#include"Camera.h"
#include"Graphics/Graphics.h"
#include"EnemyManager.h"
#include"Collision.h"
#include"ProjectileStraight.h"
#include"ProjectileHoming.h"
#include"EnemySlime.h"
#include"SceneManager.h"
#include"SceneResult.h"
#include"Audio/Audio.h"

static Player* instance = nullptr;
extern bool player_yarare_flag;
extern int damage_timer;
extern bool Bosss;

bool damage_flag;

bool x0_flag;
bool x1_flag;
bool x2_flag;
bool x3_flag;
bool x4_flag;

Effect* hitEffect = nullptr;
Effect* hitZako = nullptr;
//�C���X�^���X�擾
Player& Player::Instance()
{
    // TODO: return �X�e�[�g�����g�������ɑ}�����܂�
    return *instance;
}


//�R���X�g���N�^
Player::Player()
{
    //�C���X�^���X�|�C���^�ݒ�
    Audio& audioManager = Audio::Instance();

    move_Bgm = audioManager.LoadAudioSource("Data/Audio/idou.wav");
    attack_Bgm = audioManager.LoadAudioSource("Data/Audio/kougeki.wav");
    betyo_bgm = audioManager.LoadAudioSource("Data/Audio/betyo.wav");
    zakosi = audioManager.LoadAudioSource("Data/Audio/zakosi.wav");
    instance = this;
    damage_flag = false;
    deathFlag = false;
    effecFlag = false;

    x0_flag = false;
    x1_flag = false;
    x2_flag = false;
    x3_flag = false;
    x4_flag = false;

    interval_flag = true;
   
    model = new Model("Data/Model/pkpk/jiki.mdl");
 
    //���f�����傫���ŃX�P�[�����O
    scale.x = scale.y = scale.z = 4.0f;

    position.x = 24.0f;
    position.y = 0;
    position.z = -105;
    health = 1;
    height = 20.0f;
    player_pos = 0;

    effectTimer = 0;
    //�q�b�g�G�t�F�N�g�ǂݍ���
    hitEffect = new Effect("Data/Effect/kougeki.efk");
    hitZako = new Effect("Data/Effect/zakoHit.efk");
    radius = 5.0f;
    //�ҋ@�X�e�[�g�֑J��
    TransitionIdleState();
}

//�f�X�g���N�^
Player::~Player()
{
    delete hitEffect;

    delete hitZako;

    delete model;
}

//�X�V����
void Player::Update(float elapsedTime)
{
    position.y = 0;

    //�X�e�[�g���̏���
    switch (state)
    {
    case State::Idle:
        UpdateIdleState(elapsedTime);
        break;
    case State::Move:
        UpdateMoveState(elapsedTime);
        break;
    case State::Jump:
        UpdateJumpState(elapsedTime);
        break;
    case State::Land:
        UpdateLandState(elapsedTime);
        break;
    case State::Attack:
        UpdateAttackState(elapsedTime);
        break;
    case State::Damage:
        UpdateDamageState(elapsedTime);
        break;
    case State::Death:
        UpdateDeathState(elapsedTime);
        break;
    case State::Revive:
        UpdateReviceState(elapsedTime);
        break;
    }
    //���͏����X�V
    UpdateVelocity(elapsedTime);

    //�e�ۍX�V����
    projectileManager.Update(elapsedTime);

    //�v���C���[�ƓG�Ƃ̏Փˏ���
    if (!Bosss)
    {
    CollisionPlayerVsEnemies();

    //�e�ۂƓG�̏Փ˔���
    CollisionProjectilesVsEnemies();
    }

    //�I�u�W�F�N�g�s����X�V
    UpdateTransform();

    //���G���ԍX�V
    UpdateInvincibleTimer(elapsedTime);

    model->UpdateAnimation(elapsedTime);

    //���f���s��X�V
    model->UpdateTransform(transform);

    if (deathFlag)
    {
        angle.y += 0.035f;
    }
   
    ////�W�����v���͏���
  
    ////�e�ۓ��͏���
   
}
//���n�������ɌĂ΂��
void Player::OnLanding()
{
    jumpCount=0;

    //�������̑��͂����ȏ�Ȃ璅�n�X�e�[�g��
    if (velocity.y < gravity*5.0f)
    {
        state = State::Land;
    }
    //�_���[�W�A���S�X�e�[�g���͒��n�������ɃX�e�[�g�J�ڂ��Ȃ��悤�ɂ���
    if (state != State::Damage && state != State::Death)
    {
        //���n�X�e�[�g�֑J��
        TransitionLandState();
    }
}

//�f�o�b�O�v���~�e�B�u�`��
void Player::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

    //�Փ˔���p�̃f�o�b�O���`��

    //�Փ˔���p�̃f�o�b�O�~����`��
    debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));

    //�e�ۃf�o�b�O�v���~�e�B�u�`��
    projectileManager.DrawDebugPrimitive();

    //�U���Փ˗p�̍���m�[�h�̃f�o�b�O����`��

    if (attackCollisitonFlag)
    {
        Model::Node* leftHandBone = model->FindNode("joint6");
        debugRenderer->DrawSphere(DirectX::XMFLOAT3(
            leftHandBone->worldTransform._41,
            leftHandBone->worldTransform._42,
            leftHandBone->worldTransform._43),
            leftHandRadius,
            DirectX::XMFLOAT4(1, 0, 0, 1)
        );
    }
}

void Player::CollisionPlayerVsEnemies()
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    //�S�Ă̓G�Ƒ�������ŏՓˏ���
    int enemyCount = enemyManager.GetEnemyCount();
    for (int i = 0; i < enemyCount; ++i)
    {
        Enemy* enemy = enemyManager.GetEnemy(i);
        //�Փˏ���
        DirectX::XMFLOAT3 outPosition;

        if (Collision::IntersectCylinderVsCylinder(
            GetPosition(),
            GetRadius(),
            GetHeight(),
            enemy->GetPosition(),
            enemy->GetRadius(),
            enemy->GetHeight(),
            outPosition
        ))
        {
            //�_���[�W��^����
            if (ApplyDamage(1, 0.5f))
            {
                //������΂�
                const float power = 15.0f;
                const DirectX::XMFLOAT3 p = GetPosition();
                const DirectX::XMFLOAT3 e = enemy->GetPosition();

                float vx = p.x - e.x;
                float vz = p.z - e.z;

                float lengthXZ = sqrtf((vx * vx) + (vz * vz));

                vx /= lengthXZ;
                vz /= lengthXZ;

                DirectX::XMFLOAT3 impulse;

                impulse.x = 0;// vx * power;
                impulse.y = power * 20.0f;
                impulse.z = (vz * power) * 0.75f;

                AddImpulse(impulse);
            };
        }
    }

    EnemyManager& notenemyManager = EnemyManager::Instance();

    int notenemycount = notenemyManager.GetnotEnemyCount();
    

    for (int i = 0; i < notenemycount; ++i)
    {
        notEnemy* notenemy = enemyManager.GetnotEnemy(i);
        //�Փˏ���
        DirectX::XMFLOAT3 outPosition;
       
        if (Collision::IntersectCylinderVsCylinder(
            GetPosition(),
            GetRadius(),
            GetHeight(),
            notenemy->GetPosition(),
            notenemy->GetRadius(),
            notenemy->GetHeight(),
            outPosition
        ))
        {
            //�_���[�W��^����
            if (ApplyDamage(1, 0.5f))
            {
            };
        }
    }
}

void Player::UpdateInvincibleTimer(float elapsedTime)
{
    if (invincibleTimer > 0.0f)
    {
        invincibleTimer -= elapsedTime;
    }
}

void Player::OnDamaged()
{
    //�_���[�W�X�e�[�g�֑J
}

//�`�揈��
void Player::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);

    //�e�ە`�揈��
    projectileManager.Render(dc, shader);

    if (ImGui::Begin("parameter", nullptr, ImGuiWindowFlags_None))
    {
        if (moveMigiFlag)
        {
            ImGui::Checkbox(u8"MIGI", &moveMigiFlag);
        }
        else
        {
            ImGui::Checkbox(u8"MIGI", &moveMigiFlag);
        }
        if (moveHidariFlag)
        {
            ImGui::Checkbox(u8"HIGI", &moveHidariFlag);
        }
        else
        {
            ImGui::Checkbox(u8"HIGI", &moveHidariFlag);
        }
        if (interval_flag)
        {
            ImGui::Checkbox(u8"Interval_flag", &interval_flag);
        }
        else
        {
            ImGui::Checkbox(u8"Interval_flag", &interval_flag);
        }
    }
    ImGui::End();
}

void Player::DrawDebugGUI()
{
    ImGui::SetNextWindowPos(ImVec2(10, 100), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Player", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
    {
        //�g�����X�t�H�[��
     
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        {

            //�ʒu
            ImGui::InputFloat3("Position", &position.x);
            //��]
            DirectX::XMFLOAT3 a;
            a.x = DirectX::XMConvertToDegrees(angle.x);
            a.y = DirectX::XMConvertToDegrees(angle.y);
            a.z = DirectX::XMConvertToDegrees(angle.z);

            ImGui::InputFloat3("Angle", &a.x);
            angle.x = DirectX::XMConvertToRadians(a.x);
            angle.y = DirectX::XMConvertToRadians(a.y);
            angle.z = DirectX::XMConvertToRadians(a.z);

            //�X�P�[��
            ImGui::InputFloat3("Scale", &scale.x);

            ImGui::InputInt("Health", &health);
        }
    }
    ImGui::End();
}
void Player::OnDead()
{
    //���S�X�e�[�g�֑J��
    TransitionDeathState();
}
//�X�e�B�b�N���͒l����ړ��x�N�g�����擾
DirectX::XMFLOAT3 Player::GetMoveVec() const
{
    //���͏����擾
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();
    float ay = gamePad.GetAxisLY();

    //�J���������ƃX�e�B�b�N�̓��͒l�ɂ���Đi�s�������v�Z����
    Camera& camera = Camera::Instance();
    const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
    const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

    //�ړ��x�N�g����XZ���ʂɐ����ȃx�N�g���ɂȂ�悤�ɂ���

    //�J�����E�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
    float cameraRightX = cameraRight.x;
    float cameraRightZ = cameraRight.z;
    float cameraRightLength = sqrtf((cameraRightX*cameraRightX)+
        (cameraRightZ*cameraRightZ));

    if (cameraRightLength > 0.0f)
    {
        //�P�ʃx�N�g����
        cameraRightX /= cameraRightLength;
        cameraRightZ /= cameraRightLength;
    }
    //�J�����O�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
    float cameraFrontX = cameraFront.x;
    float cameraFrontZ = cameraFront.z;

    float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX +
        cameraFrontZ * cameraFrontZ);

    if (cameraFrontLength > 0.0f)
    {
        //�P�ʃx�N�g����
        cameraFrontX /= cameraFrontLength;
        cameraFrontZ/= cameraFrontLength;
    }

    //�X�e�B�b�N�̐������͒l���J�����E�����ɔ��f���A
    //�X�e�B�b�N�̐������͒l���J�����O�����ɔ��f���A
    //�i�s�x�N�g�����v�Z����
    DirectX::XMFLOAT3 vec;
    vec.x = (ax*cameraRightX)+(ay*cameraFrontX);
    vec.z = (0);
    //Y�������ɂ͈ړ����Ȃ�
    vec.y = 0.0f;

    return vec;
}

bool Player::InputMove(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    {
        if (gamePad.GetButtonDown() & GamePad::BTN_Y && gamePad.GetButtonDown() != GamePad::BTN_B)
        {

            if (state == State::Idle)
            {
                if (interval_flag)
                {
                    if (position.x < 40 && player_pos < 3)
                    {
                        if (move_Bgm)
                        {
                            move_Bgm->Play(false, 1.5f);
                        }
                        moveMigiFlag = true;
                        interval_flag = false;
                        return true;
                    }
                }
            }
        }
    }

    {

    
        if (gamePad.GetButtonDown() & GamePad::BTN_A&& gamePad.GetButtonDown() != GamePad::BTN_B)
        {
            if (state == State::Idle)
            {
                if (interval_flag)
                {
                    if (position.x >= 10 && player_pos > -3)
                    {
                        if (move_Bgm)
                        {
                            move_Bgm->Play(false, 1.5f);
                        }
                        moveHidariFlag = true;
                        //interval = 0;
                        interval_flag = false;
                        return true;
                    }
                }
            }
        }}
    return false;
}
    

 //   //�i�s�x�N�g������

bool Player::InputJump()
{
    return false;
}

//�U�����͏���
bool Player::InputAttack()
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    if (gamePad.GetButtonDown() & GamePad::BTN_B&& interval_flag)
    {
        if (state == State::Idle)
        {       
            interval_flag = false;
            if (attack_Bgm)
            {
                attack_Bgm->Play(false,2.3f);
            }
            return true;
            
        }
    }

    return false;
}

//�ҋ@�X�e�[�g�֑J��
void Player::TransitionIdleState()
{
    state = State::Idle;

    //�ҋ@�A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Idle, true);
}


//�ҋ@�X�e�[�g�X�V����
void Player::UpdateIdleState(float elapsedTime)
{
    moveHidariFlag = false;
    moveMigiFlag = false;
    interval_flag = true;
    if (player_pos == 0)
    {
        position.x = 24.0f;
    }
    else if (player_pos == 1)
    {
        position.x = 36.0f;
    }
    else if (player_pos == 2)
    {
        position.x = 48.0f;
    }
    else if (player_pos == -1)
    {
        position.x = 12.0f;
    }
    else if (player_pos == -2)
    {
        position.x = 0.0f;
    }
    //�ړ����͏���
    if (InputMove(elapsedTime))
    {
        TranstionMoveState();
    };
    
    //�W�����v���͏���
    if (InputJump())
    {
        TransitionJumpState();
    }

    //�U�����͏���
    if (InputAttack())
    {
        TransitionAttackState();
    }
    //�W�����v���͏���
    //�e�ۓ��͏���
    InputProjectile();
}

//�ړ��X�e�[�g�֑J��
void Player::TranstionMoveState()
{
    state = State::Move;

    //����A�j���[�V�����Đ�
    if (moveMigiFlag&&!moveHidariFlag)
    {
        if (move_Bgm)
        {
            move_Bgm->Play(true,1.5f);
        }
        velocity.x = 7.9f;
        position.x += velocity.x;
        model->PlayAnimation(Anim_Migi, false);
        player_pos += 1;
    }
    if (moveHidariFlag && !moveMigiFlag)
    {
        velocity.x = -7.9f;
        position.x += velocity.x;
        player_pos -= 1;
        model->PlayAnimation(Anim_Hidari, false);
    }
}

//�ړ��X�e�[�g�X�V����
void Player::UpdateMoveState(float elapsedTime)
{
    //�ړ����͏���
    
    if (!model->IsPlayAimation())
    {
        if (move_Bgm)
        {
            move_Bgm->Stop();
        }
        moveMigiFlag = false;
        moveHidariFlag = false;
        interval_flag = true;
    }
    if (!moveMigiFlag&&!moveHidariFlag)
    {
        TransitionIdleState();
    }
    //�W�����v���͏���
    if (InputJump())
    {
        TransitionJumpState();
    }
    //�U�����͏���
    ////�W�����v���͏���
    //�e�ۓ��͏���
    InputProjectile();

}

void Player::TransitionJumpState()
{
    state = State::Jump;

    //�W�����v�A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Jump, false);

}

void Player::UpdateJumpState(float elapsedTime)
{
    //�ړ����͏���
    
    InputMove(elapsedTime);

    if (InputJump())
    {
        model->PlayAnimation(Anim_Jump_Flip, false);
    };
    //�A�j���[�V�����I��
    if (!model->IsPlayAimation())
    {
        model->PlayAnimation(Anim_Falling, false);
    }
    InputProjectile();
}

//���n�X�e�[�g�֑J��
void Player::TransitionLandState()
{
    state = State::Land;

    //���n�A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Landing, false);
}



//���n�X�e�[�g�X�V����
void Player::UpdateLandState(float elapsedTime)
{
    if (!model->IsPlayAimation())
    {
        TransitionIdleState();
    }
}

//�U���X�e�[�g�֑J��
void Player::TransitionAttackState()
{
    state = State::Attack;

    model->PlayAnimation(Anim_Attack, false);
}
//�U���X�e�[�g�X�V����
void Player::UpdateAttackState(float elapsedTime)
{
  

    if (!model->IsPlayAimation())
    {
        TransitionIdleState();
        interval_flag = true;
    }
    ////����m�[�h�ƃG�l�~�[�̏Փˏ���
    //CollisionNodeVsEnemies("mixamorig:LeftHand", leftHandRadius);

    //�C�ӂ̃A�j���[�V�����Đ���Ԃł̂ݏՓ˔��菈��������
    float animationTime = model->GetCurrentAnimationSeconds();
    attackCollisitonFlag = animationTime >=0.2f&&animationTime<=0.7f;

    if (attackCollisitonFlag)
    {
            //����m�[�h�ƃG�l�~�[�̏Փˏ���
             CollisionNodeVsEnemies("joint6", leftHandRadius);
    }
}

void Player::TransitionDamageState()
{
    state = State::Damage;

    //�_���[�W�A�j���[�V�����Đ�
    model->PlayAnimation(Anim_GetHit1, false);
}

//�_���[�W�X�e�[�g�X�V����
void Player::UpdateDamageState(float elapsedTime)
{
    //�_���[�W�A�j���[�V�������I�������ҋ@�X�e�[�g�֑J��
    if (!model->IsPlayAimation())
    {
        
           // SceneManager::Instance().ChangeScene(new SceneResult);
        
        //TransitionIdleState();
    }
}

//���S�X�e�[�g�֑J��
void Player::TransitionDeathState()
{
    state = State::Death;

    //�_���[�W�A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Death, false);
    deathFlag = true;

}

//���S�X�e�[�g�X�V����
void Player::UpdateDeathState(float elapsedTime)
{
   
    if(!model->IsPlayAimation())
    {
        
        player_yarare_flag = true;
      
        ////�{�^�����������畜���X�e�[�g�֑J��
    }
}

void Player::CollisionNodeVsEnemies(const char* nodeName, float nodeRadius)
{
    if (!interval_flag)
    {
        //�m�[�h�擾
        Model::Node* node = model->FindNode(nodeName);
        DirectX::XMFLOAT3 positionn = { position.x,position.y,position.z + 5 };
        //�m�[�h�ʒu�擾
        DirectX::XMFLOAT3 nodePosition;
        nodePosition.x = node->worldTransform._41;
        nodePosition.y = node->worldTransform._42;
        nodePosition.z = node->worldTransform._43;

        //�w��̃m�[�h�ƑS�Ă̓G�𑍓�����ŏՓˏ���
        EnemyManager& enemyManager = EnemyManager::Instance();
        int enemyCount = enemyManager.GetEnemyCount();

        for (int i = 0; i < enemyCount; ++i)
        {
            Enemy* enemy = enemyManager.GetEnemy(i);

            //�Փˏ���
            DirectX::XMFLOAT3 outPosition;
            if (Collision::IntersectSphereVsCylinder(
                //position,
                positionn,
                nodeRadius,
                enemy->GetPosition(),
                enemy->GetRadius(),
                enemy->GetHeight(),
                outPosition))
            {
                if (zakosi)
                {
                    zakosi->Play(false, 15);
                }

                //�_���[�W��^����
                if (enemy->ApplyDamage(5, 0.5f))
                {
                    if (enemy->GetPosition().x >= -1 && enemy->GetPosition().x <= 1)
                    {
                        x0_flag = true;
                    }

                    if (enemy->GetPosition().x >= 11 && enemy->GetPosition().x <= 13)
                    {
                        x1_flag = true;
                    }

                    if (enemy->GetPosition().x >= 23 && enemy->GetPosition().x <= 25)
                    {
                        x2_flag = true;
                    }

                    if (enemy->GetPosition().x >= 35 && enemy->GetPosition().x <= 37)
                    {
                        x3_flag = true;
                    }

                    if (enemy->GetPosition().x >= 47 && enemy->GetPosition().x <= 49)
                    {
                        x4_flag = true;
                    }

                    bossFlag = true;

                    {
                        //�q�b�g�G�t�F�N�g�Đ�
                        {

                            DirectX::XMFLOAT3 e = enemy->GetPosition();
                            e.y += enemy->GetHeight() * 1.6f;
                            hitEffect->Play(e, 2);
                        }

                    }
                }
            }


        }
    }
}

void Player::TransitionReviveState()
{
    
}

void Player::UpdateReviceState(float elapsedTime)
{
    //�����A�j���[�V�����I����ɑҋ@�X�e�[�g�֑J��
    if (!model->IsPlayAimation())
    {
        TransitionIdleState();
    }
}

//�e�ۂƓG�̏Փˏ���
void Player::CollisionProjectilesVsEnemies()
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    //�S�Ă̒e�ۂƑS�Ă̓G�𑍓�����ŏՓˏ���
    int projectileCount = projectileManager.GetProjectileCount();
    int bossCount = enemyManager.GetbossCount();
    int slimeCount = enemyManager.GetEnemyCount();
    for (int i = 0; i < projectileCount; ++i)
    {
        Projectile* projectile = projectileManager.GetProjectile(i);

        for (int j = 0; j < bossCount; ++j)
        {
            boss* boooss = enemyManager.Getboss(j);
           
                //�Փˏ���
                DirectX::XMFLOAT3 outPosition;

                if (Collision::IntersectSphereVsCylinder(
                    projectile->GetPosition(),
                    projectile->GetRadius(),
                    boooss->GetPosition(),
                    boooss->GetRadius(),
                    boooss->GetHeight(),
                    outPosition))
                {
                    //�_���[�W��^����
                    if (!damage_flag)
                    {
                        if (boooss->ApplyDamage(1, 0.5f))
                        {
                            damage_timer = 60;
                            damage_flag = true;
                            if (x0_flag)
                            {
                                x0_flag = false;
                            }
                            if (x1_flag)
                            {
                                x1_flag = false;
                            }
                            if (x2_flag)
                            {
                                x2_flag = false;
                            }
                            if (x3_flag)
                            {
                                x3_flag = false;
                            }
                            if (x4_flag)
                            {
                                x4_flag = false;
                            }
                        
                            {
                                DirectX::XMFLOAT3 pro = projectile->GetPosition();
                                pro.y += projectile->GetPosition().y * 0.5f;
                                hitZako->Play(pro, 1);
                            }

                            betyo_bgm->Play(false, 1);

                            //�e�۔j��
                            projectile->Destroy();

                        }
                    }
                }
        }
    }
}



//�e�ۓ��͏���
bool Player::InputProjectile()
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    //�ǔ��e�ۏ���
  //  if (gamePad.GetButtonDown() & GamePad::BTN_Y)
    if (bossFlag)
    {
        //�O����
        DirectX::XMFLOAT3 dir;
        dir.x = sin(angle.y);
        dir.y = 0.0f;
        dir.z = cos(angle.y);

            //���ˈʒu�i�v���C���[�̍�������j
            DirectX::XMFLOAT3 pos;
            pos.x = position.x;
            pos.y = position.y + (height * 0.6f);
            pos.z = position.z;
            //�^�[�Q�b�g�i�f�t�H���g�ł̓v���C���[�̑O��)
            DirectX::XMFLOAT3 target;
            target.x = pos.x + dir.x * 1000.0f;
            target.y = pos.y + dir.y * 1000.0f;
            target.z = pos.z + dir.z * 1000.0f;
            boss* Boss;
            //��ԋ߂��̓G���^�[�Q�b�g�ɂ���
            float dist = FLT_MAX;
            EnemyManager& enemyManager = EnemyManager::Instance();
            int enemyCount = enemyManager.GetbossCount();
            //DirectX::XMFLOAT3 BossPosition =Boss->GetPosition();
            for (int i = 0; i < enemyCount; ++i)
            {
                //�G�Ƃ̋�������
                boss* booss = EnemyManager::Instance().Getboss(i);
                DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&position);
                DirectX::XMVECTOR E = DirectX::XMLoadFloat3(&booss->GetPosition());
                DirectX::XMVECTOR V = DirectX::XMVectorSubtract(E, P);
                DirectX::XMVECTOR D = DirectX::XMVector3LengthSq(V);
                float d;
                DirectX::XMStoreFloat(&d, D);
                if (d < dist)
                {
                    dist = d;
                    target.x = booss->GetPosition().x;
                    target.y += booss->GetHealth();
                    target.z = booss->GetPosition().z;
                }
            }
            //����
            ProjectileHoming* projectile = new ProjectileHoming(&projectileManager);
            projectile->Launch(dir, pos, target);

            bossFlag = false;

            return true;
    }
    return false;
}

