#include"EnemySlime.h"
#include"Graphics/Graphics.h"
#include"Audio/Audio.h"
#include"SceneGame.h"



extern Effect* hitEffect;

Effect* kurogiri = nullptr;
extern  bool player_yarare_flag;
extern bool Bosss;
extern  int  owari_timer;
bool Effect0_flag;
bool Effect1_flag;
bool Effect2_flag;
bool Effect3_flag;
bool Effect4_flag;
bool effect_flag ;

int count = 0;

//�R���X�g���N�^
EnemySlime::EnemySlime()
{
    Audio& audioManager = Audio::Instance();
    model = new Model("Data/Model/Slime/teki3.mdl");
    zako = 0;
    zako_flag = false;
    idle_timer = 0;
    idle_flag = true;
    effect_flag = true;
    
    //���f�����傫���̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 0.17f;
    angle.y = DirectX::XMConvertToRadians(180);
   
    TransitionWanderState();

    zakosi_bgm = audioManager.LoadAudioSource("Data/Audio/zakosi.wav");
    warp_bgm = audioManager.LoadAudioSource("Data/Audio/warp.wav");
   
    //�G�t�F�N�g�̓ǂݍ���
    kurogiri = new Effect("Data/Effect/wa-pu.efk");
   
    //���A�����ݒ�
    radius = 5.0f;
    height = 5.0f;
    health = 1.0f;
}

//�f�X�g���N�^
EnemySlime::~EnemySlime()
{
    if (model != nullptr)
    {
        model = nullptr;
        delete model;
    }

}

//�X�V����
void EnemySlime::Update(float elapsedTime)
{
    if (!Bosss)
    {
        //�X�e�[�g���̍X�V����
        switch (state)
        {
        case State::Wander:
            UpdateWanderState(elapsedTime);
            break;
        case State::Idle:
            UpdateIdleState(elapsedTime);
            break;
        case State::Move:
            UpdateMoveState(elapsedTime);
            break;
        }

        if (health > 0)
        {
            radius = 5.0f;
        }
        else if (health <= 0)
        {
            radius = 0;
        }

        if (position.z < -140 || Bosss)
        {
            Destroy();
        }
        Effect_flag(idle_timer, idle_flag, count);
        //���͏����X�V
        UpdateVelocity(elapsedTime);

        //���G���ԍX�V
        UpdateInvincibleTimer(elapsedTime);

        //�I�u�W�F�N�g�s����X�V

        UpdateTransform();
        model->UpdateAnimation(elapsedTime);
        model->UpdateTransform(transform);

        //���f���s��X�V

        idle_timer++;
   }
    if (Bosss)
    {
        Effect_death();
    }
}


//�`�揈��
void EnemySlime::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    if (!Bosss)
    {
        if (health > 0 && state != State::Wander)
        {
            shader->Draw(dc, model);
        }
    }

    if (ImGui::Begin("Idle_flag", nullptr, ImGuiWindowFlags_None))
    {

        if (idle_flag)
        {
            ImGui::Checkbox(u8"Idle_flag", &idle_flag);
        }
        else
        {
            ImGui::Checkbox(u8"Idle_flag", &idle_flag);
        }
        ImGui::InputInt("Idle_Timer", &idle_timer);
        ImGui::InputInt("count", &count);
    }
    ImGui::End();
}

void EnemySlime::MoveSpeed(float elapsedTime)
{
    if (health > 0)
    {
        velocity.z = 1.6f;
       // velocity.z = 1.7f;
        position.z -= velocity.z;
    }
}

//�G�t�F�N�g�X�e�[�g�֑J��
void EnemySlime::TransitionWanderState()
{
    state = State::Wander;
}
//�G�t�F�N�g�X�e�[�g�X�V����
void EnemySlime::UpdateWanderState(float elapsedTime)
{
    if (effect_timer <= 90)
    {
        if (effect_flag)
        {
            Effect_create();
        }
    }
    if (effect_timer > 90)
    {
        TransitionIdleState();
    }
    effect_timer++;
}

//�ҋ@�X�e�[�g�֑J��
void EnemySlime::TransitionIdleState()
{
    state = State::Idle;

    //�ҋ@�A�j���[�V�����Đ�
    model->PlayAnimation(Anim_IdleNormal, true);
}

//�ҋ@�A�j���[�V�����X�V����
void EnemySlime::UpdateIdleState(float elapsedTime)
{
        if (idle_timer > 120&&!idle_flag) { 
            TransitionMoveState();
            idle_timer = 0;
        }
    ++idle_timer;
}

//�ړ��X�e�[�g�֑J��
void EnemySlime::TransitionMoveState()
{
    state = State::Move;
 
    //�ړ��A�j���[�V�����Đ�
    model->PlayAnimation(Anim_IdleNormal, true);
}

void EnemySlime::Effect_create()
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    int EffectCount = kurogiri->GetEffectCount();
    int enemy_Count=enemyManager.GetEnemyCount();
 
    for (int i = 0; i <= enemy_Count; ++i)
    {
        if (Effect_flag(idle_timer, idle_flag, count))
        {
            if (owari_timer==0)
            {
                warp_bgm->Play(false, 4);
                if (GetType() == 0)
                {
                    DirectX::XMFLOAT3 p = { 0,5,90 };
                    p.y += 2.5f;
                    kurogiri->Play(p, 5);

                    idle_flag = false;
                    effect_flag = false;
                }
                if (GetType() == 1)
                {
                    DirectX::XMFLOAT3 p = { 12,5,90 };
                    p.y += 2.5f;
                    kurogiri->Play(p, 5);

                    idle_flag = false;
                    effect_flag = false;
                }
                if (GetType() == 2)
                {
                    DirectX::XMFLOAT3 p = { 24,5,90 };
                    p.y += 2.5f;
                    kurogiri->Play(p, 5);

                    idle_flag = false;
                    effect_flag = false;
                }
                if (GetType() == 3)
                {
                    DirectX::XMFLOAT3 p = { 36,5,90 };
                    p.y += 2.5f;
                    kurogiri->Play(p, 5);

                    idle_flag = false;
                    effect_flag = false;
                }
                if (GetType() == 4)
                {
                    DirectX::XMFLOAT3 p = { 48,5,90 };
                    p.y += 2.5f;
                    kurogiri->Play(p, 5);

                    idle_flag = false;
                    effect_flag = false;
                }
            }
          
        };

    }
}

void EnemySlime::reset()
{
 
}


void EnemySlime::Effect_death()
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    int EffectCount = kurogiri->GetEffectCount();
    int enemy_Count = enemyManager.GetEnemyCount();

    for (int i = 0; i < enemy_Count; ++i)
    {
        if (!Effect_flag(idle_timer, idle_flag, count))
        {
            if (GetType() == 0||Bosss)
            {
                kurogiri->Stop(count);
                effect_flag=true;
                idle_flag = true;
            }
            if (GetType() == 1 || Bosss)
            {
                kurogiri->Stop(count);
                effect_flag = true;
                idle_flag = true;
            }
            if (GetType() == 2 || Bosss)
            {
                kurogiri->Stop(count);
                effect_flag = true;
                idle_flag = true;
            }
            if (GetType() == 3 || Bosss)
            {
                kurogiri->Stop(count);
                effect_flag = true;
                idle_flag = true;
            }
            if (GetType() == 4 || Bosss)
            {
                kurogiri->Stop(count);
                effect_flag = true;
                idle_flag = true;
            }
            count++;

        }
    }
}

bool EnemySlime::Effect_flag(int efc_timer, bool efc_flag,int count)
{
    if (efc_timer <= 90 && efc_flag)
    {
        return true;
    }
    else if (efc_timer > 90&&!efc_flag)
    {
        return false;
    }
}

//�ړ��A�j���[�V�����X�V����
void EnemySlime::UpdateMoveState(float elapsedTime)
{
    if (idle_timer > 80 && !idle_flag) {
        Effect_death();
    }

    ++idle_timer;
    if (idle_timer > 120)
    {
        MoveSpeed(elapsedTime);
    }
}

//���S�������ɌĂ΂��
void EnemySlime::OnDead()
{
    if (!zako_flag)
    {
        zako_flag = true;
    }
    if (zako_flag)
    {
        if (zako <= 50)
        {
            zakosi_bgm->Play(false, 12.0f);
        }
        else if (zako > 50)
        {
            zako = 0;
            zako_flag = false;
        }
        zako++;
    }
   Destroy();
}
