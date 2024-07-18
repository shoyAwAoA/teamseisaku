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

    //‰Šú‰»
    void Initialize()override;

    //I—¹‰»
    void Finalize()override;

    //XVˆ—
    void Update(float elapsedTime)override;

    //•`‰æˆ—
    void Render()override;

private:
    int pos0 = 0;
    int pos1 = 0;
    int pos2 = 0;
    int pos3 = 0;
    int pos4 = 0;
    int pos5 = 0;
    int pos6 = 0;
    int pos7 = 0;
    Sprite* sprite = nullptr;
    Sprite* Score;
    std::unique_ptr<AudioSource> kati_bgm;
};