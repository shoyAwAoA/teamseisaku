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
    //インスタンス取得
  //  static Stage& Instance();
private:
    Model* model = nullptr;
};