#include"EnemySlime.h"
#include"Graphics/Graphics.h"
#include"Audio/Audio.h"


//�R���X�g���N�^
EnemySlime::EnemySlime()
{
    model = new Model("Data/Model/Slime/Slime.mdl");

    //���f�����傫���̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 0.1f;
    angle.y = 180.0f;
   /* position.y = 0;*/
    TransitionIdleState();

    Audio& audioManager = Audio::Instance();

    zakosi_bgm = audioManager.LoadAudioSource("Data/Audio/zakosi.wav");

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
    //�X�e�[�g���̍X�V����
    switch (state)
    {
    case State::Wander:
        UpdateWanderState(elapsedTime);
        break;
    case State::Idle:
        UpdateIdleState(elapsedTime);
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



    //���͏����X�V
    UpdateVelocity(elapsedTime);

    //���G���ԍX�V
    UpdateInvincibleTimer(elapsedTime);

    //�I�u�W�F�N�g�s����X�V
    UpdateTransform();

    MoveSpeed(elapsedTime);


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
    if (zakosi_bgm)
    {
        zakosi_bgm->Play(false, 12.0f);
    }
   Destroy();
}

//void EnemySlime::OnDamaged()
//{
//}
