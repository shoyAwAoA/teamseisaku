#pragma once
#include"Enemy.h"


class Boss :public boss
{
public:
    Boss();
    ~Boss()override;

    //XVˆ—
    void Update(float elapsedTime)override;

    //•`‰æˆ—
    void Render(ID3D11DeviceContext* dc, Shader* shader)override;

    void MoveSpeed(float elapsedTime);


private:
    Model* model = nullptr;
protected:
    //€–S‚µ‚½‚Æ‚«‚ÉŒÄ‚Î‚ê‚é
    void OnDead()override;
    //  void OnDamaged()override;
};
