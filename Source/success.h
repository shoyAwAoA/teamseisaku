#pragma once

#include"Graphics/Sprite.h"
#include"Scene.h"
#include"SceneManager.h"
#include"SceneTitle.h"
#include"Audio/AudioSource.h"

class SceneSuccess : public Scene
{
public:
    SceneSuccess() {};
    ~SceneSuccess()override {};

    //������
    void Initialize()override;

    //�I����
    void Finalize()override;

    //�X�V����
    void Update(float elapsedTime)override;

    //�`�揈��
    void Render()override;

private:
    Sprite* sprite = nullptr;
    std::unique_ptr<AudioSource> kati_bgm;
};