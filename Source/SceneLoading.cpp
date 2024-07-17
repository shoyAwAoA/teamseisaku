#include"Graphics/Graphics.h"
#include"Input/Input.h"
#include"SceneLoading.h"
#include"SceneManager.h"


//������
void SceneLoading::Initialize()
{
    //�X�v���C�g������
    sprite = new Sprite("Data/Sprite/setumee.png");

    //�X���b�h�J�n
    thread = new std::thread(LoadingThread, this);
}

//�I����
void SceneLoading::Finalize()
{
    //�X���b�h�I����
    if (thread != nullptr)
    {
        thread->join();
        delete thread;
        thread = nullptr;
    }
    //�X�v���C�g�I����
    if (sprite != nullptr)
    {
        delete sprite;
        sprite = nullptr;
    }
}

//�X�V����
void SceneLoading::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
   /* constexpr float speed = 180;
    angle += speed * elapsedTime;*/
    const GamePadButton GetGameStart =
        GamePad::GamePad::BTN_B;;
    
    //���̃V�[���̏���������������V�[����؂�ւ���
    /*if (nextScene->IsReady())
    {
        SceneManager::Instance().ChangeScene(nextScene);
        nextScene = nullptr;
    }*/
    if (gamePad.GetButton() & GetGameStart&& nextScene->IsReady())
    {

        {
            SceneManager::Instance().ChangeScene(nextScene);
        }
    }
}
//�`�揈��
void SceneLoading::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    //��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f,0.0f,0.5f,1.0f };
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);
    //2D�X�v���C�g�`��
    {
        //��ʉE���Ƀ��[�f�B���O�A�C�R����`��
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());
        float positionX = screenWidth - textureWidth;
        float positionY = screenHeight - textureHeight;

        sprite->Render(
            dc,
            positionX, positionY,
            textureWidth, textureHeight,
            0, 0,
            textureWidth, textureHeight,
            angle,
            1, 1, 1, 1
        );
    }
}
//���[�f�B���O�X���b�h
void SceneLoading::LoadingThread(SceneLoading* scene)
{
    //COM�֘A�̏������ŃX���b�h���ɌĂԕK�v������
    CoInitialize(nullptr);

    //���̃V�[���̏��������s��
    scene->nextScene->Initialize();

    //�X���b�h���I���O��COM�֘A�̏I����
    CoUninitialize();

    //���̃V�[���̏��������ݒ�
    scene->nextScene->SetReady();
}



