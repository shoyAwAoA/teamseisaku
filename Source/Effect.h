#pragma once

#include<DirectXMath.h>
#include<Effekseer.h>

//�G�t�F�N�g
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

    //�Đ�
    Effekseer::Handle Play(const DirectX::XMFLOAT3& position, float scale = 1.0f);

    //��~
    void Stop(Effekseer::Handle handle);

    //�O��
    void Stopp();

    //���W�ݒ�

    void SetPosition(Effekseer::Handle handle, const DirectX::XMFLOAT3& posdition);

    //�X�P�[���ݒ�
    void SetScale(Effekseer::Handle handle, const DirectX::XMFLOAT3& scale);

    int GetEffectCount() const { return static_cast<int>(effecties.size()); }

private:
    std::vector<Effect*>        effecties;
    Effekseer::EffectRef    effekseerEffect;
};