#include"success.h"
#include <Input/GamePad.h>
#include<Input/Input.h>
#include <Graphics/Graphics.h>
#include"Audio/Audio.h"

extern int Scoree;

void SceneSuccess::Initialize()
{
    //スプライト初期化
    sprite = new Sprite("Data/Sprite/kati.png");
    Score = new Sprite("Data/Font/font1.png");
    Audio& audiomanager = Audio::Instance();
    kati_bgm = audiomanager.LoadAudioSource("Data/Audio/kati.wav");
}

void SceneSuccess::Finalize()
{
    //スプライト終了化
    if (sprite != nullptr)
    {
        delete sprite;
        sprite = nullptr;
    }
}

void SceneSuccess::Update(float elapsedTime)
{
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

    kati_bgm->Play(true, 1);

    if (gamePad.GetButton() & anyButton)
    {
        SceneManager::Instance().ChangeScene(new SceneTitle);
    }
}

void SceneSuccess::Render()
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

       Score->textout(dc,"score",400,400,80,80,1,0,1,1);
    }
    //スコア表示
    {
        static int time;

        time = Scoree;

        char timer[36];

        sprintf_s(timer, "%d", time);

       Score->textout(dc,"TIME",0,280,120,120,1,0,1,1);

       Score->textout(dc, timer, 750, 280, 60,60, 1, 0, 1, 1);
     
       if (time < 5001)
       {
           Score->textout(dc, "S", 900, 400, 300, 300, 1, 0, 1, 1);
       }
       else if (time>5000&&time < 7001)
       {
           Score->textout(dc, "A", 900, 400, 300, 300, 1, 0, 1, 1);
       }
       else if (time>7000&&time < 9001)
       {
           Score->textout(dc, "B", 900, 400, 300, 300, 1, 0, 1, 1);
       }
       else if (time>7000&&time < 11001)
       {
           Score->textout(dc, "C", 900, 400, 300, 300, 1, 0, 1, 1);
       }
       else if (time>11000&&time < 13001)
       {
           Score->textout(dc, "^^", 900, 400, 300, 300, 1, 0, 1, 1);
       }
    }
}




