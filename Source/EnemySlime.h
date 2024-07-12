#pragma once

#include"Graphics/Model.h"
#include"Enemy.h"
#include"Audio/AudioSource.h"

//スライム
class EnemySlime :public Enemy
{
public:
    EnemySlime();
    ~EnemySlime()override;

    //更新処理
    void Update(float elapsedTime)override;

    //描画処理
    void Render(ID3D11DeviceContext* dc, Shader* shader)override;

    void MoveSpeed(float elapsedTime);

    //デバッグ用GUI描画
   // void DrawDebugGUI();

private:

    //徘徊ステーとへ遷移
    void TransitionWanderState();

    //徘徊ステート更新処理
    void UpdateWanderState(float elapsedTime);
    
    //待機ステートへ遷移
    void TransitionIdleState();

    //待機ステート更新処理
    void UpdateIdleState(float elapsedTime);

private:
    //ステート
    enum class State
    {
        Wander,
        Idle,
        Die,
    };

    //アニメーション
    enum Animation
    {
        Anim_IdleNormal,
        Anim_IdleBattle,
        Anim_Attack1,
        Anim_Attack2,
        Anim_WalkFWD,
        Anim_WalkBWD,
        Anim_WalkLeft,
        Anim_WalkRight,
        Anim_RunFWD,
        Anim_SenseSomthingST,
        Anim_SenseSomthingPRT,
        Anim_Taunt,
        Anim_Victory,
        Anim_GetHit,
        Anim_Dizzy,
        Anim_Die
    };
private:
    Model* model=nullptr;
    State  state = State::Wander;
    DirectX::XMFLOAT3 targetPosition = { 0,0,0 };
    DirectX::XMFLOAT3 territoryOrigin = { 0,0,0 };
    float             territoryRange = 10.0f;
    float             moveSpeed = 3.0f;
    float             turnSpeed = DirectX::XMConvertToRadians(360);
    float             stateTimer = 0.0f;
protected:
    //死亡したときに呼ばれる
    void OnDead()override;
  //  void OnDamaged()override;
    std::unique_ptr<AudioSource> zakosi_bgm;

};