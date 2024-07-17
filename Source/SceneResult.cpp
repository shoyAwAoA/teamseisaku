#include"Graphics/Graphics.h"
#include"SceneResult.h"
#include"SceneTitle.h"

#include"SceneManager.h"
#include"Input/Input.h"
#include"Audio/Audio.h"


void SceneResult::Initialize()
{
    //スプライト初期化
    sprite = new Sprite("Data/Sprite/make.png");
    Audio& audioManager = Audio::Instance();
    result_bgm = audioManager.LoadAudioSource("Data/Audio/result.wav");
}

void SceneResult::Finalize()
{
    //スプライト終了化
    if (sprite != nullptr)
    {
        delete sprite;
        sprite = nullptr;
    }
}

void SceneResult::Update(float elapsedTime)
{
    //BGM
    {
        if (result_bgm)
        {
            result_bgm->Play(true, 5);
        }
    }

    GamePad& gamePad = Input::Instance().GetGamePad();

    //何かボタンを押したらゲームシーンへ切り替え
    const GamePadButton anyButton =
        GamePad::BTN_A
        | GamePad::BTN_B
        | GamePad::BTN_X
        | GamePad::BTN_Y;
    /*if (gamePad.GetButton() & anyButton)
    {
        SceneManager::Instance().ChangeScene(new SceneGame);
    }*/

    if (gamePad.GetButton() & anyButton)
    {
        result_bgm->Stop();
        SceneManager::Instance().ChangeScene(new SceneTitle);
    }

}

void SceneResult::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    //画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f,0.0f,0.5f,1.0f };
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);
    //2Dスプライト描画
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());
        //タイトルスプライト描画
        sprite->Render(
            dc,
            0, 0,
            screenWidth,
            screenHeight,
            0, 0,
            textureWidth,
            textureHeight,
            0,
            1, 1, 1, 1
        );

    }
}
