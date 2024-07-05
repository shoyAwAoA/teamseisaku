#pragma once

//#include"Graphics/Shader.h"
#include"Graphics/Model.h"
//#include"Collision.h"
#include"Stage.h"


//ステージ

//メインステージ
//class Stage
class StageMain:public Stage 
{
public:
    //Stage();
    StageMain();
    //~Stage();
    ~StageMain();

    //更新処理
    //void Update(float elapsedTime);
    void Update(float elapsedTime)override;

    //描画処理
    //void Render(ID3D11DeviceContext* dc, Shader* shader);
    void Render(ID3D11DeviceContext* dc, Shader* shader)override;
    //レイキャスト
    //bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);
    bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override;

    void DrawDebugGUI();

    void UpdateTransform();
    //インスタンス取得
  //  static Stage& Instance();
private:
    Model* model = nullptr;
    DirectX::XMFLOAT3 position = { 0,0,0 };
    DirectX::XMFLOAT3 angle = { 0,0,0 };
    DirectX::XMFLOAT3 scale = { 1,1,1 };
    DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
};