#pragma once

#include<DirectXMath.h>
#include<Effekseer.h>

//エフェクト
class Effect
{
public:

    //static Effect& Instance()
    //{
    //    static Effect& instance;
    //    return instance;
    //}

    Effect(const char* filename);
    ~Effect() {};

    //再生
    Effekseer::Handle Play(const DirectX::XMFLOAT3& position, float scale = 1.0f);

    //停止
    void Stop(Effekseer::Handle handle);

    //前提し
    void Stopp();

    //座標設定

    void SetPosition(Effekseer::Handle handle, const DirectX::XMFLOAT3& posdition);

    //スケール設定
    void SetScale(Effekseer::Handle handle, const DirectX::XMFLOAT3& scale);

    int GetEffectCount() const { return static_cast<int>(effecties.size()); }

private:
    std::vector<Effect*>        effecties;
    Effekseer::EffectRef    effekseerEffect;
};