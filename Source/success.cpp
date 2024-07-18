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
    pos0 = 73;
    pos1 = 235;
    pos2 =75;
    pos3 = 439;
    pos4 = 1422;
    pos5 = 425;
    pos6 = 1393;
    pos7 = 875;
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

       
    }
    //スコア表示
    {
        static int time;

        time = Scoree;

        char timer[36];

        sprintf_s(timer, "%d", time);



        Score->textout(dc, "TIME", pos0, pos1, 170, 170, 1, 0, 1, 1);

        Score->textout(dc, "SCORE", pos6, pos7, 100, 100, 1, 0, 1, 1);

        Score->textout(dc, timer, pos2, pos3, 130, 130, 1, 0, 1, 1);

        if (time < 5001)
        {
            Score->textout(dc, "S", pos4, pos5, 450, 450, 1, 0, 1, 1);
        }
        else if (time > 5000 && time < 7001)
        {
            Score->textout(dc, "A", pos4, pos5, 450, 450, 1, 0, 1, 1);
        }
        else if (time > 7000 && time < 9001)
        {
            Score->textout(dc, "B", pos4, pos5, 450, 450, 1, 0, 1, 1);
        }
        else if (time > 7000 && time < 11001)
        {
            Score->textout(dc, "C", pos4, pos5, 450, 450, 1, 0, 1, 1);
        }
        else if (time > 11000 )
        {
            Score->textout(dc, "^^", pos4, pos5, 450, 450, 1, 0, 1, 1);
        }
    }
    if (ImGui::Begin("Boss", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
    {
        //トランスフォーム
        ImGui::InputInt("x0", &pos0);
        ImGui::InputInt("y0", &pos1);
        ImGui::InputInt("x1", &pos2);
        ImGui::InputInt("y1", &pos3);
        ImGui::InputInt("Score.x", &pos4);
        ImGui::InputInt("Score.y", &pos5);
        ImGui::InputInt("Scor", &pos6);
        ImGui::InputInt("Scor2", &pos7);




        ImGui::End();
    }
}




