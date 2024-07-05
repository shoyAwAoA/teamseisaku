#include"StageMain.h"




//�C���X�^���X�擾
//static Stage* instance = nullptr;
//Stage& Stage::Instance()
//{
//    return *instance;
//    // TODO: return �X�e�[�g�����g�������ɑ}�����܂�
//}

//�R���X�g���N�^
//Stage::Stage()
StageMain::StageMain()
{
//    instance = this;
    //�X�e�[�W���f����ǂݍ���
    model = new Model("Data/Model/ExampleStage/ExampleStage.mdl");
}

//�f�X�g���N�^
//Stage::~Stage()
StageMain::~StageMain()
{
    //�X�e�[�W���f����j��
    delete model;
}

//�X�V����
//void Stage::Update(float elapsedTime)
void StageMain::Update(float elapsedTime)
{
    //
}
//�`�揈��
//void Stage::Render(ID3D11DeviceContext* dc, Shader* shader)
void StageMain::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    //�V�F�[�_�[�Ƀ��f����`�悵�Ă��炤
    model->UpdateTransform(transform);
    shader->Draw(dc, model);
}

//���C�L���X�g
//bool Stage::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
bool StageMain::RayCast(const DirectX::XMFLOAT3& start,const DirectX::XMFLOAT3& end,HitResult& hit)
{
    return Collision::IntersectRayVsModel(start,end,model,hit);
}

void StageMain::UpdateTransform()
{
    //�X�P�[���s����쐬
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

    ////��]�s����쐬
    //DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.z,angle.y,angle.x);

    //��]�s����쐬
    DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);

    DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);

    DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);

    DirectX::XMMATRIX R = Y * X * Z;

    //�ʒu�s����쐬
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

    //3�̍s���g�ݍ��킹�A���[���h�s����쐬
    DirectX::XMMATRIX W = S * R * T;

    //�v�Z�������[���h�s������o��
    DirectX::XMStoreFloat4x4(&transform, W);

}


void StageMain::DrawDebugGUI()
{
    //ImGui::SetNextWindowPos(ImVec2(10, 500), ImGuiCond_FirstUseEver);
    //ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    //if (ImGui::Begin("StageMain", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
    //{
    //    //�g�����X�t�H�[��

    //    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    //    {

    //        //�ʒu
    //        ImGui::InputFloat3("Position", &position.x);
    //        //��]
    //        DirectX::XMFLOAT3 a;
    //        a.x = DirectX::XMConvertToDegrees(angle.x);
    //        a.y = DirectX::XMConvertToDegrees(angle.y);
    //        a.z = DirectX::XMConvertToDegrees(angle.z);

    //        ImGui::InputFloat3("Angle", &a.x);

    //        angle.x = DirectX::XMConvertToRadians(a.x);
    //        angle.y = DirectX::XMConvertToRadians(a.y);
    //        angle.z = DirectX::XMConvertToRadians(a.z);

    //        //�X�P�[��
    //        ImGui::InputFloat3("Scale", &scale.x);

    //        ImGui::InputInt("Health", &health);


    //    }
    //}
    //ImGui::End();


}
void StageMain::UpdateTransform()
{
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
    DirectX::XMMATRIX W = S * R * T;
    DirectX::XMStoreFloat4x4(&transform, W);
}