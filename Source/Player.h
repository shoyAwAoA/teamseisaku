#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"
#include"Character.h"
#include"ProjectileManager.h"
#include"Effect.h"
#include"Audio/AudioSource.h"

//プレイヤー
class Player :public Character
{
public:
    Player();
    ~Player()override;

    //更新処理
    void Update(float elapsedTime);

    //描画処理
    void Render(ID3D11DeviceContext* dc, Shader* shader);

    //デバッグ用GUI描画
    void DrawDebugGUI();

    //デバッグプリミティブ描画
    void DrawDebugPrimitive();

    ////ジャンプ入力処理
    //void InputJump();

    //弾丸と敵の衝突判定処理
    void CollisionProjectilesVsEnemies();

    //インスタンス取得
    static Player& Instance();

protected:
    //着地した時に呼ばれる
    void OnLanding() override;

    ////移動入力処理
    //void InputMove(float elapsedTime);

    //弾丸入力処理
    bool InputProjectile();

    //プレイヤーとエネミーとの衝突判定
    void CollisionPlayerVsEnemies();

    void UpdateInvincibleTimer(float elapsedTime);

    //ダメージを受けた時に呼ばれる
    void OnDamaged() override;

    //死亡した時に呼ばれる
    void OnDead()override;

private:
    //スティック入力値からベクトルを取得
    DirectX::XMFLOAT3 GetMoveVec() const;

    //移動入力処理
    bool InputMove(float elapsedTime);

    //ジャンプ入力処理
    bool InputJump();

    //攻撃入力処理
    bool InputAttack();

    //待機ステートへ遷移
    void TransitionIdleState();

    //待機ステート更新処理
    void UpdateIdleState(float elapsedTime);

    //移動ステートへ遷移
    void TranstionMoveState();

    //移動ステート更新処理
    void UpdateMoveState(float elapsedTime);

    //ジャンプステートへ遷移
    void TransitionJumpState();

    //ジャンプステート更新処理
    void UpdateJumpState(float elapsedTime);

    //着地ステートへ遷移
    void TransitionLandState();

    //着地ステート更新処理
    void UpdateLandState(float elapsedTime);

    //攻撃ステートへ遷移
    void TransitionAttackState();

    //攻撃ステート更新処理
    void UpdateAttackState(float elapsedTime);

    //ダメージステートへ遷移
    void TransitionDamageState();

    //ダメージステートへ更新処理
    void UpdateDamageState(float elapsedTime);

    //死亡ステートへ遷移
    void TransitionDeathState();

    //死亡ステート更新処理
    void UpdateDeathState(float elapsedTime);

    //ノードとエネミーの衝突処理
    void CollisionNodeVsEnemies(const char* nodeName, float nodeRadius);

    //復活ステートへ遷移
    void TransitionReviveState();

    //復活ステート更新処理
    void UpdateReviceState(float elapsedTime);

private:
    //ステート
    enum class State
    {
        Idle,
        Move,
        Jump,
        Land,
        Attack,
        Damage,
        Death,
        Revive,
    };

private:

    //アニメーション
    enum Animation
    {
        Anim_Idle,
        Anim_Hidari,
        Anim_Migi,
        Anim_Attack,
        Anim_Death,
        Anim_GetHit1,
        Anim_GetHit2,
        Anim_Falling,
        Anim_Jump,
        Anim_Jump_Flip,
        Anim_Landing,
        Anim_Revive,
        Anim_Running,
        Anim_Walking
    };

    Model* model = nullptr;

    float moveSpeed = 15.0f;

    float        jumpSpeed = 1.0f;
   
    float       turnSpeed = DirectX::XMConvertToRadians(720);

    float       leftHandRadius = 3.0f;

    int          jumpCount = 0;

    int          jumpLimit = 2;

    //アニメーションの再生時間取得し、衝突判定を発生させる時間を制限
    bool         attackCollisitonFlag = false;

    bool         moveMigiFlag = false;

    bool         moveHidariFlag = false;

    bool         bossFlag = false;

    bool         deathFlag = false;

   // int          interval = 15;

    bool         interval_flag = true;

    ProjectileManager   projectileManager;

    Effect* hitEffect = nullptr;

    int          player_pos = 0;

    State       state = State::Idle;

    std::unique_ptr<AudioSource> move_Bgm;
    std::unique_ptr<AudioSource> attack_Bgm;


};

