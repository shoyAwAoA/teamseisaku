#pragma once

#include"Graphics/Sprite.h"
#include"Scene.h"
#include"SceneManager.h"
#include"SceneTitle.h"

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
    Sprite* sprite = nullptr;
};