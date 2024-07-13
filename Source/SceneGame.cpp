#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include"Camera.h"
#include"EnemyManager.h"
#include"EnemySlime.h"
#include"EffectManager.h"
#include"Input/Input.h"
#include"StageManager.h"
#include"StageMain.h"
#include"StageMoveFloor.h"
#include"kowasenai.h"
#include"boss.h"
#include"SceneResult.h"
#include"SceneManager.h"
#include"success.h"
#include"Audio/Audio.h"


bool player_yarare_flag;

bool boss_yarare_flag;
bool ran_flag0;
bool ran_flag1;
bool ran_flag2;
bool ran_flag3;
bool ran_flag4;


extern int count;
// 初期化
void SceneGame::Initialize()
{
	srand((unsigned int)time(NULL));
	count = 0;
	timer0 = 0;
	timer1 = 0;
	timer2 = 0;
	timer3 = 0;
	timer4 = 0;
	enemyType = 0;

	ran_flag0 = false;
	ran_flag1 = false;
	ran_flag2 = false;
	ran_flag3 = false;
	ran_flag4 = false;


	//Effect0_flag=false;
 //   Effect1_flag=false;
	//Effect2_flag=false;
	//Effect3_flag=false;
	//Effect4_flag=false;

	Audio& audioManager = Audio::Instance();
	game_bgm=audioManager.LoadAudioSource("Data/Audio/bgm_game.wav");
	
	kurogiri2 = new Effect("Data/Effect/kurogiri2.efk");
	//ステージの初期化
	//stage = new Stage();
	StageManager& stageManager = StageManager::Instance();
	StageMain* stageMain = new StageMain();
	stageManager.Register(stageMain);
	player = new Player();
	player_yarare_flag = false;
	boss_yarare_flag = false;



	//
	//StageMoveFloor* stageMoveFloor = new StageMoveFloor();
	//stageMoveFloor->SetStartPoint(DirectX::XMFLOAT3(0, 1, 3));
	//stageMoveFloor->SetGoalPoint(DirectX::XMFLOAT3(10, 2, 3));
	//stageMoveFloor->SetTorque(DirectX::XMFLOAT3(0, 1.0f, 0));
	//stageManager.Register(stageMoveFloor);

	//エネミー初期化	
 //    EnemyManager& enemyManager = EnemyManager::Instance();
	///*enemyslime = new EnemySlime();
	//enemyslime->SetPosition(DirectX::XMFLOAT3(0, 0, 5));
	//enemyManager.Register(enemyslime);*/
	

	//カメラ初期設定
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();

	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 20, -10),
		DirectX::XMFLOAT3(0, 10, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);
	//カメラコントローラー初期化
	cameraController = new CameraController();

	EnemyManager& enemyManager = EnemyManager::Instance();
	//for (int i = 0; i < 5; ++i)
	//{
	//	
	//		EnemySlime* slime = new EnemySlime();
	//		slime->SetPosition(DirectX::XMFLOAT3(i * 12.0f, 0, 90));
	//		enemyManager.Register(slime);

	//		kowasenai* wasenai = new kowasenai();
	//		wasenai->SetPosition(DirectX::XMFLOAT3(12.0f, 0, 150));
	//		enemyManager.Register(wasenai);

	//}z

	Boss* boss = new Boss;
	boss->SetPosition(DirectX::XMFLOAT3(24, 0, 90));
	enemyManager.Register(boss);

	//ゲージスプライト
	gauge = new Sprite();
}

// 終了化
void SceneGame::Finalize()
{

	//ゲージスプライト終了化
	if (gauge != nullptr)
	{
		delete gauge;
		gauge = nullptr;
	}

	//エネミー終了化
	EnemyManager::Instance().Clear();
	/*if (enemyslime != nullptr)
	{
		delete enemyslime;
		enemyslime = nullptr;*/
//	}
	//ステージ終了化
	/*if (stage != nullptr)
	{
		delete stage;
		stage = nullptr;
	}*/
	//プレイヤー終了化
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	//カメラコントローラー終了化
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}
	StageManager::Instance().Clear();


}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	if (game_bgm)
	{
		game_bgm->Play(true,0.5f);
	}

	//kurogiri



	//DirectX::XMFLOAT3 e = enemy->GetPosition();
	//e.y += enemy->GetHeight() * 0.5f;
	//hitEffect->Play(e);


	EnemyManager& enemyManager = EnemyManager::Instance();
	//0レーンの敵処理
	{
		if (timer0 >= 350 && rand() % 150 == 0)
		{
			if (ran_flag0 == false)
			{
				for (int i = 1; i < 2; ++i)
				{
					enemyType = rand() % 3+i;
					ran_flag0 = true;
				}
			}
			if (enemyType == 1 && ran_flag0)
			{
				
				EnemySlime* slime = new EnemySlime;
				slime->SetType(0);
				slime->SetPosition(DirectX::XMFLOAT3(0, 0, 90));
				enemyManager.Register(slime);
				
			}
			else if(enemyType==2 && ran_flag0)/* if (enemyType == 2 && ran_flag0)*/
			{
				EnemySlime* slime = new EnemySlime;
				slime->SetType(0);
				slime->SetPosition(DirectX::XMFLOAT3(0, 0, 90));
				enemyManager.Register(slime);


				//kowasenai* wasenai = new kowasenai;
				////wasenai->SetType(0);
				//wasenai->SetPosition(DirectX::XMFLOAT3(0, 0, 90));
				//enemyManager.Register(wasenai);
			}
			else if (enemyType == 3 && ran_flag0)
			{

				EnemySlime* slime = new EnemySlime;
				slime->SetType(0);
				slime->SetPosition(DirectX::XMFLOAT3(0, 0, 90));
				enemyManager.Register(slime);

			//	kowasenai* wasenai = new kowasenai;
			////	wasenai->SetType(0);
			//	wasenai->SetPosition(DirectX::XMFLOAT3(0, 0, 90));
			//	enemyManager.Register(wasenai);
			}
			ran_flag0 = false;
			timer0 = 0;

		}
	}
	//1レーンの敵処理
	{
		if (timer1 >= 250 && rand() % 150 == 0)
		{
			if (ran_flag1 == false)
			{
				enemyType = rand() % 3 + 1;
				ran_flag1 = true;
			}
			if (enemyType == 1 && ran_flag1)
			{
				EnemySlime* slime = new EnemySlime;
				slime->SetType(1);
				slime->SetPosition(DirectX::XMFLOAT3(12, 0, 90));
				enemyManager.Register(slime);
			}
			else if (enemyType == 2 && ran_flag1)/* if (enemyType == 2 && ran_flag0)*/
			{
				kowasenai* wasenai = new kowasenai;
				wasenai->SetPosition(DirectX::XMFLOAT3(12, 0, 90));
				enemyManager.Register(wasenai);
			}
			else if (enemyType == 3 && ran_flag1)
			{
				kowasenai* wasenai = new kowasenai;
				wasenai->SetPosition(DirectX::XMFLOAT3(12, 0, 90));
				enemyManager.Register(wasenai);
			}
			ran_flag1 = false;
			timer1 = 0;

		}
	}
	//2レーンの敵処理
	{
		if (timer2 >= 200 && rand() % 150 == 0)
		{
			if (ran_flag2 == false)
			{
				enemyType = rand() % 3 + 1;
				ran_flag2 = true;
			}
			if (enemyType == 1 && ran_flag2)
			{
				EnemySlime* slime = new EnemySlime;
				slime->SetType(2);
				slime->SetPosition(DirectX::XMFLOAT3(24, 0, 90));
				enemyManager.Register(slime);
			}
			else if (enemyType == 2 && ran_flag2)/* if (enemyType == 2 && ran_flag0)*/
			{
				kowasenai* wasenai = new kowasenai;
				wasenai->SetPosition(DirectX::XMFLOAT3(24, 0, 90));
				enemyManager.Register(wasenai);
			}
			else if (enemyType == 3 && ran_flag2)
			{
				kowasenai* wasenai = new kowasenai;
				wasenai->SetPosition(DirectX::XMFLOAT3(24, 0, 90));
				enemyManager.Register(wasenai);
			}
			ran_flag2 = false;
			timer2 = 0;

		}

	}
	//3レーンの敵処理
	{
		if (timer3 >= 250 && rand() % 150 == 0)
		{
			if (ran_flag3 == false)
			{
				enemyType = rand() % 3 + 1;
				ran_flag3 = true;
			}
			if (enemyType == 1 && ran_flag3)
			{
				EnemySlime* slime = new EnemySlime;
				slime->SetType(3);
				slime->SetPosition(DirectX::XMFLOAT3(36, 0, 90));

				enemyManager.Register(slime);
			}
			else if (enemyType == 2 && ran_flag3)/* if (enemyType == 2 && ran_flag0)*/
			{
				kowasenai* wasenai = new kowasenai;
				wasenai->SetPosition(DirectX::XMFLOAT3(36, 0, 90));
				enemyManager.Register(wasenai);
			}
			else if (enemyType == 3 && ran_flag3)
			{
				kowasenai* wasenai = new kowasenai;
				wasenai->SetPosition(DirectX::XMFLOAT3(36, 0, 90));
				enemyManager.Register(wasenai);
			}
			ran_flag3 = false;
			timer3 = 0;

		}

	}
	//4レーンの敵処理
	{
		if (timer4 >= 150 && rand() % 150 == 0)
		{
			if (ran_flag4 == false)
			{
				enemyType = rand() % 3 + 1;
				ran_flag4 = true;
			}
			if (enemyType == 1 && ran_flag4)
			{
				EnemySlime* slime = new EnemySlime;
				slime->SetType(4);
				slime->SetPosition(DirectX::XMFLOAT3(48, 0, 90));
				enemyManager.Register(slime);
			}
			else if (enemyType == 2 && ran_flag4)/* if (enemyType == 2 && ran_flag0)*/
			{
				kowasenai* wasenai = new kowasenai;
				wasenai->SetPosition(DirectX::XMFLOAT3(48, 0, 90));
				
				
				enemyManager.Register(wasenai);
			}
			else if (enemyType == 3 && ran_flag4)
			{
				kowasenai* wasenai = new kowasenai;
				wasenai->SetPosition(DirectX::XMFLOAT3(48, 0, 90));
			
			
				enemyManager.Register(wasenai);
			}
			ran_flag4 = false;
			timer4 = 0;

		}



	}
	timer0++;
	timer1++;
	timer2++;
	timer3++;
	timer4++;
	//{
	//	ramdam0 = rand() % 4;
	//	
	//	if (timer0 >= 500 && rand() % 240 == 0)
	//	{

	//		EnemyManager& enemyManager = EnemyManager::Instance();

	//		switch (ramdam0)
	//		{
	//		case 0:
	//			for (int i = 0; i < 2; ++i)
	//			{
	//				EnemySlime* slime = new EnemySlime;
	//				slime->SetPosition(DirectX::XMFLOAT3(i * 24.0f, 0, 90));
	//				enemyManager.Register(slime);
	//			}
	//			for (int j = 1; j < 4; ++j)
	//			{
	//				kowasenai* wasenai = new kowasenai();
	//				wasenai->SetPosition(DirectX::XMFLOAT3(j * 12, 0.0f, 90.0f));

	//				//if(wasenai->SetPosition().)
	//				enemyManager.Register(wasenai);
	//				if (wasenai->GetPosition().x == 24 || wasenai->GetPosition().x == 48)
	//				{

	//					if (wasenai->ApplyDamage(1, 0.5f))
	//					{
	//						wasenai->Destoroy();
	//					}
	//				}
	//			}


	//			break;
	//		case 1:
	//			for (int i = 1; i < 2; ++i)
	//			{
	//				EnemySlime* slime = new EnemySlime;
	//				slime->SetPosition(DirectX::XMFLOAT3(i * 36.0f, 0, 90));
	//				enemyManager.Register(slime);
	//			}
	//			for (int j = 1; j < 4; ++j)
	//			{
	//				kowasenai* wasenai = new kowasenai();
	//				wasenai->SetPosition(DirectX::XMFLOAT3(j * 12, 0.0f, 90.0f));

	//				enemyManager.Register(wasenai);
	//				if (wasenai->GetPosition().x == 36)
	//				{

	//					if (wasenai->ApplyDamage(1, 0.5f))
	//					{
	//						wasenai->Destoroy();

	//					}
	//				}
	//			}


	//			break;
	//		case 2:
	//			for (int i = 1; i < 3; ++i)
	//			{
	//				EnemySlime* slime = new EnemySlime;
	//				slime->SetPosition(DirectX::XMFLOAT3(i * 24.0f, 0, 90));
	//				enemyManager.Register(slime);
	//			}
	//			for (int j = 1; j < 4; ++j)
	//			{
	//				kowasenai* wasenai = new kowasenai();
	//				wasenai->SetPosition(DirectX::XMFLOAT3(j * 12, 0.0f, 90.0f));


	//				enemyManager.Register(wasenai);
	//				if (wasenai->GetPosition().x == 24 || wasenai->GetPosition().x == 48)
	//				{

	//					if (wasenai->ApplyDamage(1, 0.5f))
	//					{
	//						wasenai->Destoroy();

	//					}
	//				}
	//			}


	//			break;
	//		case 3:
	//			for (int i = 0; i < 2; ++i)
	//			{
	//				EnemySlime* slime = new EnemySlime;
	//				slime->SetPosition(DirectX::XMFLOAT3(i * 24.0f, 0, 90));
	//				enemyManager.Register(slime);
	//				if (slime->GetPosition().x == 24)
	//				{
	//					if (slime->ApplyDamage(1, 0.5f))
	//					{
	//						enemyManager.Remove(slime);

	//					}

	//				}
	//			}
	//			for (int j = 1; j < 4; ++j)
	//			{
	//				kowasenai* wasenai = new kowasenai();
	//				wasenai->SetPosition(DirectX::XMFLOAT3(j * 12.0f + 12.0f, 0.0f, 90.0f));


	//				enemyManager.Register(wasenai);


	//			}

	//			break;
	//		}
	//		/*enemyManager.Register(slime);
	//		enemyManager.Register(wasenai);*/
	//		timer0 = 0;

	//	}
	//	//if (timer==500)
	//	//{
	//	//	EnemyManager& enemyManager = EnemyManager::Instance();
	//	//	for (int i = 0; i < 5; i++)
	//	//	{
	//	//		EnemySlime* slime = new EnemySlime;
	//	//		slime->SetPosition(DirectX::XMFLOAT3(i * 12.0f, 0, 90));
	//	//		enemyManager.Register(slime);
	//	//	}
	//	//	timer = 0;
	//	//}
	//	timer0++;

	//}

	//カメラコントローラ更新処理
	DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);


	//ステージ更新処理
//	stage->Update(elapsedTime);
	StageManager::Instance().Update(elapsedTime);
	//プレイヤー更新処理
	player->Update(elapsedTime);
	//エネミーの更新処理
	EnemyManager::Instance().Update(elapsedTime);
	//エフェクト更新処理
	EffectManager::Instance().Update(elapsedTime);
	
}


	



// 描画処理
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// 画面クリア＆レンダーターゲット設定
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0～1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// 描画処理
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ライト方向（下方向）

	////カメラパラメータ設定
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	//// ビュー行列
	//{
	//	DirectX::XMFLOAT3 eye = { 0, 10, -10 };	// カメラの視点（位置）
	//	DirectX::XMFLOAT3 focus = { 0, 0, 0 };	// カメラの注視点（ターゲット）
	//	DirectX::XMFLOAT3 up = { 0, 1, 0 };		// カメラの上方向

	//	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
	//	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	//	DirectX::XMbVECTOR Up = DirectX::XMLoadFloat3(&up);
	//	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	//	DirectX::XMStoreFloat4x4(&rc.view, View);
	//}
	//// プロジェクション行列
	//{
	//	float fovY = DirectX::XMConvertToRadians(45);	// 視野角
	//	float aspectRatio = graphics.GetScreenWidth() / graphics.GetScreenHeight();	// 画面縦横比率
	//	float nearZ = 0.1f;	// カメラが映し出すの最近距離
	//	float farZ = 1000.0f;	// カメラが映し出すの最遠距離
	//	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspectRatio, nearZ, farZ);
	//	DirectX::XMStoreFloat4x4(&rc.projection, Projection);
	//}

	// 3Dモデル描画
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);
		//ステージ描画
	//	stage->Render(dc, shader);
		StageManager::Instance().Render(dc, shader);
		//エネミー描画
		EnemyManager::Instance().Render(dc, shader);

		//プレイヤー描画
		player->Render(dc, shader);

		shader->End(dc);
	}

	// 3Dデバッグ描画
	{
		//プレイヤーデバッグプリミティブ描画
		player->DrawDebugPrimitive();
		//エネミーデバッグプリミティブ描画
		EnemyManager::Instance().DrawDebugPrimitive();
		// ラインレンダラ描画実行
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);

		// デバッグレンダラ描画実行
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);
	}

	//3Dエフェクト描画
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}

	// 2Dスプライト描画
	{
		RenderEnemyGauge(dc, rc. view, rc. projection);
	}

	// 2DデバッグGUI描画
	{
		//プレイヤーデバッグ描画
		player->DrawDebugGUI();

		
	}
	
	//プレイヤーが死んだときにリザルト画面に遷移
	if (player_yarare_flag)
	{
		SceneManager::Instance().ChangeScene(new SceneResult);
	}
	//ボスが死んだときにクリア画面に遷移
	if (boss_yarare_flag)
	{
		SceneManager::Instance().ChangeScene(new SceneSuccess);
	}


}

//エネミーHPゲージ描画
//エネミーHPゲージ描画
void SceneGame::RenderEnemyGauge(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4 projection)
{
	//ビューポート
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	dc->RSGetViewports(&numViewports, &viewport);
	//変換行列
	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();
	//全ての敵の頭上にHPゲージを表示
	EnemyManager& enemyManager = EnemyManager::Instance();
	int bossCount = enemyManager.GetbossCount();
	for (int i = 0; i < bossCount; ++i)
	{
		boss* boss = enemyManager.Getboss(i);

		DirectX::XMFLOAT3 worldPosition = boss->GetPosition();
		worldPosition.y += boss->GetHeight();
		DirectX::XMVECTOR WorldPosition = DirectX::XMLoadFloat3(&worldPosition);
		//ワールド座標からスクリーン座標へ変換
		DirectX::XMVECTOR ScreenPosition = DirectX::XMVector3Project(
			WorldPosition,//ワールド座標
			viewport.TopLeftX,	  //ビューポート左上X位置
			viewport.TopLeftY,	  //ビューポート左上Y位置
			viewport.Width,//ビューポート幅
			viewport.Height,//ビューポート高さ
			viewport.MinDepth,//深度値の範囲を表す最小値(0.0でよい)
			viewport.MaxDepth,//深度値の範囲を表す最大値(1.0fでよい)
			Projection,//プロジェクション行列
			View,//ビュー行列
			World//ワールド行列(単位行列で良い)
		);
		//スクリーン座標
		DirectX::XMFLOAT2 screenPosition;
		DirectX::XMStoreFloat2(&screenPosition, ScreenPosition);
		//ゲージの長さ
		const float gaugeWidth = 50.0f;
		const float gaugeHeight = 40.0f;
		float healthRate = boss->GetHealth() / static_cast<float> (boss->GetMaxHealth());
		float maxHealthRate = static_cast<float>(boss->GetMaxHealth());
		//ゲージ描画
		gauge->Render(
			dc,
			screenPosition.x + gaugeWidth * 2.5f,
			screenPosition.y - gaugeHeight * 3.0f,
			gaugeWidth * 10,
			gaugeHeight,
			0, 0,
			static_cast<float>(gauge->GetTextureWidth()),
			static_cast<float>(gauge->GetTextureHeight()),
			0.0f,
			1.0f, 1.0f, 1.0f, 1.0f
		);
		gauge->Render(
			dc,
			screenPosition.x + gaugeWidth * 2.5f,
			screenPosition.y - gaugeHeight * 3.0f,
			gaugeWidth * healthRate,
			gaugeHeight,
			0, 0,
			static_cast<float>(gauge->GetTextureWidth()),
			static_cast<float>(gauge->GetTextureHeight()),
			0.0f,
			1.0f, 0.0f, 0.0f, 1.0f
		);

	}
	//
	//
	//
	//	////エネミーの配置処理
	//	//Mouse& mouse = Input::Instance().GetMouse();
	//	//if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
	//	//{
	//	//	//マウスカーソル座標を取得
	//	//	DirectX::XMFLOAT3 screenPosition;
	//	//	screenPosition.x = static_cast<float>(mouse.GetPositionX());
	//	//	screenPosition.y = static_cast<float>(mouse.GetPositionY());
	//	//	DirectX::XMVECTOR ScreenPosition, WorldPosition;
	//	//	//レイの始点を算出
	//	//	screenPosition.z = 0.0f;
	//	//	ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
	//	//	WorldPosition = DirectX::XMVector3Unproject(
	//	//		ScreenPosition,
	//	//		viewport.TopLeftX,
	//	//		viewport.TopLeftY,
	//	//		viewport.Width,
	//	//		viewport.Height,
	//	//		viewport.MinDepth,
	//	//		viewport.MaxDepth,
	//	//		Projection,
	//	//		View,
	//	//		World
	//	//	);
	//	//	DirectX::XMFLOAT3 rayStart;
	//	//	DirectX::XMStoreFloat3(&rayStart, WorldPosition);
	//	//	//レイの終点を算出
	//	//	screenPosition.z = 1.0f;
	//	//	ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
	//	//	WorldPosition = DirectX::XMVector3Unproject(
	//	//		ScreenPosition,
	//	//		viewport.TopLeftX,
	//	//		viewport.TopLeftY,
	//	//		viewport.Width,
	//	//		viewport.Height,
	//	//		viewport.MinDepth,
	//	//		viewport.MaxDepth,
	//	//		Projection,
	//	//		View,
	//	//		World
	//	//	);
	//	//	DirectX::XMFLOAT3 rayEnd;
	//	//	DirectX::XMStoreFloat3(&rayEnd, WorldPosition);
	//	//	//レイキャスト
	//	//	HitResult hit;
	//	//	if (StageManager::Instance().RayCast(rayStart, rayEnd, hit))
	//	//	{
	//	//		//敵を配置
	//	//		EnemySlime* slime = new EnemySlime();
	//	//		slime->SetPosition(hit.position);
	//	//		EnemyManager::Instance().Register(slime);
	//	//	}
	//	//}
	//}
}