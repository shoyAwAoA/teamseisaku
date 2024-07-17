#pragma once

#include"Graphics//Sprite.h"
#include"Scene.h"
#include"Audio/AudioSource.h"

//�^�C�g���V�[��
class SceneTitle :public Scene
{
public:
    SceneTitle() {}
    ~SceneTitle()override {};

    //������
    void Initialize()override;

    //�I����
    void Finalize()override;

    //�X�V����
    void Update(float elapseTime)override;

    //�`�揈��
    void Render()override;

private:
    Sprite* sprite = nullptr;
    Sprite* sprite2 = nullptr;
    std::unique_ptr<AudioSource> title_bgm;
    std::unique_ptr<AudioSource> sentaku_bgm;
    
   
};