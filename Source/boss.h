#pragma once
#include"Enemy.h"


class Boss :public boss
{
public:
    Boss();
    ~Boss()override;

    //更新処理
    void Update(float elapsedTime)override;

    //描画処理
    void Render(ID3D11DeviceContext* dc, Shader* shader)override;

    void MoveSpeed(float elapsedTime);


private:
    Model* model = nullptr;
    int damage_timer = 60;
protected:
    //死亡したときに呼ばれる
    void OnDead()override;
    //  void OnDamaged()override;
};
