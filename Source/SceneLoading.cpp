#include"Graphics/Graphics.h"
#include"Input/Input.h"
#include"SceneLoading.h"
#include"SceneManager.h"


//初期化
void SceneLoading::Initialize()
{
    //スプライト初期化
    sprite = new Sprite("Data/Sprite/setumeeee.png"); 

    //スレッド開始
    thread = new std::thread(LoadingThread, this);

    idle_timer = 0;
}

//終了化
void SceneLoading::Finalize()
{
    //スレッド終了化
    if (thread != nullptr)
    {
        thread->join();
        delete thread;
        thread = nullptr;
    }
    //スプライト終了化
    if (sprite != nullptr)
    {
        delete sprite;
        sprite = nullptr;
    }
}

//更新処理
void SceneLoading::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
   
    const GamePadButton GetGameStart =
        GamePad::GamePad::BTN_B;;
    
    //次のシーンの準備が完了したらシーンを切り替える
  
    if (gamePad.GetButton() & GetGameStart&&idle_timer>29)
    {
        {
            idle_timer = 0;
            SceneManager::Instance().ChangeScene(nextScene);
        }
    }
    idle_timer++;
}
//描画処理
void SceneLoading::Render()
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
        //画面右下にローディングアイコンを描画
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
//ローディングスレッド
void SceneLoading::LoadingThread(SceneLoading* scene)
{
    //COM関連の初期化でスレッド毎に呼ぶ必要がある
    CoInitialize(nullptr);

    //次のシーンの初期化を行う
    scene->nextScene->Initialize();

    //スレッドが終わる前にCOM関連の終了化
    CoUninitialize();

    //次のシーンの準備完了設定
    scene->nextScene->SetReady();
}



