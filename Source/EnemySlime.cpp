#include"EnemySlime.h"


//�R���X�g���N�^
EnemySlime::EnemySlime()
{
    model = new Model("Data/Model/Slime/Slime.mdl");

    //���f�����傫���̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 0.01f;

    position.y = 0;

    //���A�����ݒ�
    radius = 0.5f;
    height = 1.0f;
    health = 1.0f;
}

//�f�X�g���N�^
EnemySlime::~EnemySlime()
{
    delete model;
}

//�X�V����
void EnemySlime::Update(float elapsedTime)
{
    //���͏����X�V
    UpdateVelocity(elapsedTime);

    //���G���ԍX�V
    UpdateInvincibleTimer(elapsedTime);

    //�I�u�W�F�N�g�s����X�V
    UpdateTransform();

    MoveSpeed(elapsedTime);

    //���f���s��X�V
    model->UpdateTransform(transform);

}

//�`�揈��
void EnemySlime::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);
}

void EnemySlime::MoveSpeed(float elapsedTime)
{
    velocity.z = 0.05f;
    position.z -= velocity.z;
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
   Destroy();
}

//void EnemySlime::OnDamaged()
//{
//}
