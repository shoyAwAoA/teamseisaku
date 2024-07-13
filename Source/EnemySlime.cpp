#include"EnemySlime.h"
#include"Graphics/Graphics.h"
#include"Audio/Audio.h"
#include"SceneGame.h"



extern Effect* hitEffect;
extern  bool player_yarare_flag;
bool Effect0_flag;
bool Effect1_flag;
bool Effect2_flag;
bool Effect3_flag;
bool Effect4_flag;



int count = 0;
int count1=0;
int count2=0;
int count3=0;
int count4=0;
//�R���X�g���N�^
EnemySlime::EnemySlime()
{
    Audio& audioManager = Audio::Instance();
    model = new Model("Data/Model/Slime/Slime.mdl");
    zako = 0;
    zako_flag = false;
    idle_timer = 0;
    idle_flag = true;
    //���f�����傫���̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 0.1f;
    angle.y = 180.0f;
   /* position.y = 0;*/
    TransitionIdleState();
   
  

    zakosi_bgm = audioManager.LoadAudioSource("Data/Audio/zakosi.wav");
   
    kurogiri->Stopp();
    //�G�t�F�N�g�̓ǂݍ���
    kurogiri = new Effect("Data/Effect/kurogiri2.efk");


   
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
  
    if (kurogiri != nullptr)
    {
        kurogiri = nullptr;
        delete kurogiri;
    }
}

//�X�V����
void EnemySlime::Update(float elapsedTime)
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

    if (position.z<-120)
    {
        Destroy();
    }


    Effect_create();

    //���͏����X�V
    UpdateVelocity(elapsedTime);

    //���G���ԍX�V
    UpdateInvincibleTimer(elapsedTime);

    //�I�u�W�F�N�g�s����X�V
    UpdateTransform();

    //MoveSpeed(elapsedTime);



    model->UpdateAnimation(elapsedTime);

    //���f���s��X�V
    model->UpdateTransform(transform);
}

//�`�揈��
void EnemySlime::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    if (health > 0)
    {
        shader->Draw(dc, model);
    }

    if (ImGui::Begin("Idle_flag", nullptr, ImGuiWindowFlags_None))
    {

        if (idle_flag)
        {
            ImGui::Checkbox(u8"Idle", &idle_flag);
        }
        else
        {
            ImGui::Checkbox(u8"Idle", &idle_flag);
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
        velocity.z = 0.85f;
        position.z -= velocity.z;
    }
}

//�p�j�X�e�[�g�֑J��
void EnemySlime::TransitionWanderState()
{
    state = State::Wander;
    model->PlayAnimation(Anim_WalkFWD, true);
}
//�p�j�X�e�[�g�X�V����
void EnemySlime::UpdateWanderState(float elapsedTime)
{
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

    if (idle_timer <= 90)
    {
           
       // if (GetType() == 0)
        if(idle_flag)
        {
            if (GetType() == 0)
            {
                Effect_create();
                //idle_flag = false;
            }
        }
    }
   // else if(idle_timer>90)
    else if(!idle_flag)
    {
     
        Effect_death(GetType());
        count++;
        TransitionMoveState();
       
       //idle_timer = 0;
    }  
    
    ++idle_timer;
}

//�ړ��X�e�[�g�֑J��
void EnemySlime::TransitionMoveState()
{
    state = State::Move;
  
    idle_flag = false;
    //for (int i = 0; i < 200; ++i)
    //{
    //     hitEffect->Stop(i);
    //}
    //
    //�ړ��A�j���[�V�����Đ�
    model->PlayAnimation(Anim_WalkBWD, true);
}

void EnemySlime::Effect_create()
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    int EffectCount = kurogiri->GetEffectCount();
    int enemy_Count=enemyManager.GetEnemyCount();
    int enemyCount=enemyManager.Instance().GetEnemyCount();

    for (int i = 0; i < enemy_Count; ++i)
    {
        if (Effect_flag(idle_timer, idle_flag, count))
        {

            if (GetType() == 0)
            {
                DirectX::XMFLOAT3 p = { 0,0,90 };
                p.y += 2.5f;
                kurogiri->Play(p, 20);
             

                idle_flag = false;
            }
            if (GetType() == 1)
            {
                DirectX::XMFLOAT3 p = { 12,0,90 };
                p.y += 2.5f;
                kurogiri->Play(p, 20);
            

                idle_flag = false;
            }
            if (GetType() == 2)
            {
                DirectX::XMFLOAT3 p = { 24,0,90 };
                p.y += 2.5f;
                kurogiri->Play(p, 20);
               

                idle_flag = false;
            }
            if (GetType() == 3)
            {
                DirectX::XMFLOAT3 p = { 36,0,90 };
                p.y += 2.5f;
                kurogiri->Play(p, 20);
          

                idle_flag = false;
            }
            if (GetType() == 4)
            {
                DirectX::XMFLOAT3 p = { 48,0,90 };
                p.y += 2.5f;
                kurogiri->Play(p, 20);
             

                idle_flag = false;
            }
        };

    }
}

void EnemySlime::Effect_death(float GetType)
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    int EffectCount = kurogiri->GetEffectCount();
    int enemy_Count = enemyManager.GetEnemyCount();
    int enemyCount = enemyManager.Instance().GetEnemyCount();

    for (int i = 0; i < enemy_Count; ++i)
    {
        
            if (GetType == 0)
            {
                kurogiri->Stop(count);
               
            }
            if (GetType == 1)
            {
                kurogiri->Stop(count);
              
            }
            if (GetType == 2)
            {
                kurogiri->Stop(count);
               
            }
            if (GetType == 3)
            {
                kurogiri->Stop(count);
              
            }
            if (GetType == 4)
            {
                kurogiri->Stop(count);
               
            }
    }
}

bool EnemySlime::Effect_flag(int efc_timer, bool efc_flag,int count)
{
    if (efc_timer <= 90 && efc_flag)
    {
        return true;
    }
    else if (efc_timer > 90)
    {
        return false;
    }
}

//�ړ��A�j���[�V�����X�V����
void EnemySlime::UpdateMoveState(float elapsedTime)
{
   
    MoveSpeed(elapsedTime);

    
}

//void EnemySlime::DrawDebugGUI()
//{
//    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
//    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
//
////    if (ImGui::Begin("EnemySlime", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
////    {
////        //�g�����X�t�H�[��
////
////        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
////        {
////
////            //�ʒu
////            ImGui::InputFloat3("Position", &position.x);
////            //��]
////            DirectX::XMFLOAT3 a;
////            a.x = DirectX::XMConvertToDegrees(angle.x);
////            a.y = DirectX::XMConvertToDegrees(angle.y);
////            a.z = DirectX::XMConvertToDegrees(angle.z);
////
////            ImGui::InputFloat3("Angle", &a.x);
////
////            angle.x = DirectX::XMConvertToRadians(a.x);
////            angle.y = DirectX::XMConvertToRadians(a.y);
////            angle.z = DirectX::XMConvertToRadians(a.z);
////
////            //�X�P�[��
////            ImGui::InputFloat3("Scale", &scale.x);
////
////            //HP
////            //ImGui::InputFloat("health", &health);
////        }
////    }
////    ImGui::End();
////
////}

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
    /*if (zakosi_bgm)
    {
    }*/
   Destroy();
}

//void EnemySlime::OnDamaged()
//{
//}
