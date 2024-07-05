#pragma once

#include"Graphics/Shader.h"
#include"Character.h"

//エネミー
class Enemy :public Character
{
public:
    Enemy() {};
    ~Enemy() override {}


    //更新処理
    virtual void Update(float elapsedTime) = 0;//継承先で必ず実装させるように純粋仮想関数にする

    //描画処理
    virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

    //デバッグプリミティブ描画
    virtual void DrawDebugPrimitive();

    virtual void DebugPrimitive();

    //破棄
    void Destroy();
};