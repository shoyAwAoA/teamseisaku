#include"StageMain.h"




//インスタンス取得
//static Stage* instance = nullptr;
//Stage& Stage::Instance()
//{
//    return *instance;
//    // TODO: return ステートメントをここに挿入します
//}

//コンストラクタ
//Stage::Stage()
StageMain::StageMain()
{
//    instance = this;
    //ステージモデルを読み込み
    scale.x = scale.y = scale.z = 3.0f;
     
    angle.y = DirectX::XMConvertToRadians(180);

    model = new Model("Data/Model/Stage/stage.mdl");
}

//デストラクタ
//Stage::~Stage()
StageMain::~StageMain()
{
    //ステージモデルを破棄
    delete model;
}

//更新処理
//void Stage::Update(float elapsedTime)
void StageMain::Update(float elapsedTime)
{
    UpdateTransform();
}
//描画処理
//void Stage::Render(ID3D11DeviceContext* dc, Shader* shader)
void StageMain::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    //シェーダーにモデルを描画してもらう
    model->UpdateTransform(transform);
    shader->Draw(dc, model);
}

//レイキャスト
//bool Stage::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
bool StageMain::RayCast(const DirectX::XMFLOAT3& start,const DirectX::XMFLOAT3& end,HitResult& hit)
{
    return Collision::IntersectRayVsModel(start,end,model,hit);
}


void StageMain::DrawDebugGUI()
{
    //ImGui::SetNextWindowPos(ImVec2(10, 500), ImGuiCond_FirstUseEver);
    //ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    //if (ImGui::Begin("StageMain", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
    //{
    //    //トランスフォーム

    //    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    //    {

    //        //位置
    //        ImGui::InputFloat3("Position", &position.x);
    //        //回転
    //        DirectX::XMFLOAT3 a;
    //        a.x = DirectX::XMConvertToDegrees(angle.x);
    //        a.y = DirectX::XMConvertToDegrees(angle.y);
    //        a.z = DirectX::XMConvertToDegrees(angle.z);

    //        ImGui::InputFloat3("Angle", &a.x);

    //        angle.x = DirectX::XMConvertToRadians(a.x);
    //        angle.y = DirectX::XMConvertToRadians(a.y);
    //        angle.z = DirectX::XMConvertToRadians(a.z);

    //        //スケール
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