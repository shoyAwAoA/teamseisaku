#pragma once
#include"Graphics//Sprite.h"
#include"Scene.h"

//���[�f�B���O�V�[��
class SceneResult : public Scene
{
public:
    SceneResult() {}
    ~SceneResult()override {};

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
   
  
};