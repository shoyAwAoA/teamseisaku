#pragma once

#include"Graphics/Sprite.h"
#include"Scene.h"
#include"SceneManager.h"
#include"SceneTitle.h"
#include"Audio/AudioSource.h"
#include<string>



class SceneSuccess : public Scene
{
public:
    SceneSuccess() {};
    ~SceneSuccess()override {};

    //初期化
    void Initialize()override;

    //終了化
    void Finalize()override;

    //更新処理
    void Update(float elapsedTime)override;

    //描画処理
    void Render()override;

private:
    Sprite* sprite = nullptr;
    Sprite* Score;
    std::unique_ptr<AudioSource> kati_bgm;
};