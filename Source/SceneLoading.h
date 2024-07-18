#pragma once

#include<thread>
#include"Graphics/Sprite.h"
#include"Scene.h"

//���[�f�B���O�V�[��
class SceneLoading : public Scene
{
public:
    SceneLoading(Scene* nextScene) :nextScene(nextScene) {}
    //SceneLoading() {}
    ~SceneLoading() {}

    //������
    void Initialize() override;

    //�I����
    void Finalize() override;

    //�X�V����
    void Update(float elapsedTime)override;

    //�`�揈��
    void Render() override;

private:
    //���[�f�B���O�X���b�h
    static void LoadingThread(SceneLoading* scene);

private:
    Sprite* sprite = nullptr;
    float   angle = 0.0f;
    Scene* nextScene = nullptr;
    std::thread* thread = nullptr;
    int idle_timer = 0;
};