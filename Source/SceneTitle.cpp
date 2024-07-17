#include"Graphics/Graphics.h"
#include"SceneTitle.h"
#include"SceneGame.h"
#include"SceneManager.h"
#include"Input/Input.h"
#include"SceneLoading.h"
#include"Audio/Audio.h"
bool sen_flag = false;
int sen = 0;
//初期化
void SceneTitle::Initialize()
{
    //スプライト初期化
    sprite = new Sprite("Data/Sprite/titole.png");
    Audio& audiomanager = Audio::Instance();
    title_bgm = audiomanager.LoadAudioSource("Data/Audio/title.wav");
    sentaku_bgm = audiomanager.LoadAudioSource("Data/Audio/senntaku.wav");
    sen = 0;
    sen_flag = false;
}

//終了化
void SceneTitle::Finalize()
{
    //スプライト終了化
    if (sprite != nullptr)
    {
        delete sprite;
        sprite = nullptr;
    }
}

//更新所l理
void SceneTitle::Update(float elapseTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    if (title_bgm)
    {
        title_bgm->Play(true,1.0f);
    }

    //何かボタンを押したらゲームシーンへ切り替え
    const GamePadButton anyButton =
        GamePad::BTN_A
        | GamePad::BTN_B
        | GamePad::BTN_X
        | GamePad::BTN_Y;
    //if (gamePad.GetButton() & anyButton)
    //{
    //    SceneManager::Instance().ChangeScene(new SceneGame);
    //}

    if (gamePad.GetButton() & anyButton&&sen>60)
    {
        sen_flag = true;
    }
    if (sen_flag)
    {

        if (sen <= 50)
        {
            if (sentaku_bgm)
            {
                sentaku_bgm->Play(true, 8.5f);
            }
        }
        if (sen > 50)
        {
            sen_flag = false;
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
            sen = 0;
        }
    }
   
        sen++;
    
}
//描画処理
void SceneTitle::Render()
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



