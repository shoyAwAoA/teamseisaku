#include"SceneManager.h"

//�X�V����
void SceneManager::Update(float elapsedTime)
{
    if (nextScene != nullptr)
    {
        //�Â��V�[�����I������
      //  currentScene->Finalize();
        Clear();
        //�V�����V�[����ݒ�
        currentScene = nextScene;

        //�V�[��������
        currentScene->Initialize();
        nextScene = nullptr;
    }

    if (currentScene != nullptr)
    {
        currentScene->Update(elapsedTime);
    }

}
//�`�揈��
void SceneManager::Render()
{
    if (currentScene != nullptr)
    {
        currentScene->Render();
    }
}
//�V�[���N���A
void SceneManager::Clear()
{
    if (currentScene != nullptr)
    {
        currentScene->Finalize();
        delete currentScene;
        currentScene = nullptr;
    }
}
//�V�[���؂�ւ�
void SceneManager::ChangeScene(Scene* scene)
{
    nextScene = scene;
}

