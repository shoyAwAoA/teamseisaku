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


// ������
void SceneGame::Initialize()
{
	//�X�e�[�W�̏�����
	//stage = new Stage();
	StageManager& stageManager = StageManager::Instance();
	StageMain* stageMain = new StageMain();
	stageManager.Register(stageMain);
	player = new Player();

	//
	//StageMoveFloor* stageMoveFloor = new StageMoveFloor();
	//stageMoveFloor->SetStartPoint(DirectX::XMFLOAT3(0, 1, 3));
	//stageMoveFloor->SetGoalPoint(DirectX::XMFLOAT3(10, 2, 3));
	//stageMoveFloor->SetTorque(DirectX::XMFLOAT3(0, 1.0f, 0));
	//stageManager.Register(stageMoveFloor);

	//�G�l�~�[������	
 //    EnemyManager& enemyManager = EnemyManager::Instance();
	///*enemyslime = new EnemySlime();
	//enemyslime->SetPosition(DirectX::XMFLOAT3(0, 0, 5));
	//enemyManager.Register(enemyslime);*/
	

	//�J���������ݒ�
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
	//�J�����R���g���[���[������
	cameraController = new CameraController();

	EnemyManager& enemyManager = EnemyManager::Instance();
	for (int i = 0; i < 5; ++i)
	{
		
			EnemySlime* slime = new EnemySlime();
			slime->SetPosition(DirectX::XMFLOAT3(i * 12.0f, 0, 90));
			enemyManager.Register(slime);

			kowasenai* wasenai = new kowasenai();
			wasenai->SetPosition(DirectX::XMFLOAT3(i * 12.0f, 0, 120));
			enemyManager.Register(wasenai);


		
	}


	//�Q�[�W�X�v���C�g
	gauge = new Sprite();
}

// �I����
void SceneGame::Finalize()
{

	//�Q�[�W�X�v���C�g�I����
	if (gauge != nullptr)
	{
		delete gauge;
		gauge = nullptr;
	}

	//�G�l�~�[�I����
	EnemyManager::Instance().Clear();
	/*if (enemyslime != nullptr)
	{
		delete enemyslime;
		enemyslime = nullptr;*/
//	}
	//�X�e�[�W�I����
	/*if (stage != nullptr)
	{
		delete stage;
		stage = nullptr;
	}*/
	//�v���C���[�I����
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	//�J�����R���g���[���[�I����
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}
	StageManager::Instance().Clear();
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{
	//�J�����R���g���[���X�V����
	DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);

	//�X�e�[�W�X�V����
//	stage->Update(elapsedTime);
	StageManager::Instance().Update(elapsedTime);
	//�v���C���[�X�V����
	player->Update(elapsedTime);
	//�G�l�~�[�̍X�V����
	EnemyManager::Instance().Update(elapsedTime);
	//�G�t�F�N�g�X�V����
	EffectManager::Instance().Update(elapsedTime);



	//if (timer==500)
	//{
	//	EnemyManager& enemyManager = EnemyManager::Instance();
	//	for (int i = 0; i < 5; i++)
	//	{
	//		EnemySlime* slime = new EnemySlime;
	//		slime->SetPosition(DirectX::XMFLOAT3(i * 12.0f, 0, 90));
	//		enemyManager.Register(slime);
	//	}
	//	timer = 0;
	//}
}

// �`�揈��
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0�`1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// �`�揈��
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ���C�g�����i�������j

	////�J�����p�����[�^�ݒ�
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	//// �r���[�s��
	//{
	//	DirectX::XMFLOAT3 eye = { 0, 10, -10 };	// �J�����̎��_�i�ʒu�j
	//	DirectX::XMFLOAT3 focus = { 0, 0, 0 };	// �J�����̒����_�i�^�[�Q�b�g�j
	//	DirectX::XMFLOAT3 up = { 0, 1, 0 };		// �J�����̏����

	//	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
	//	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	//	DirectX::XMbVECTOR Up = DirectX::XMLoadFloat3(&up);
	//	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	//	DirectX::XMStoreFloat4x4(&rc.view, View);
	//}
	//// �v���W�F�N�V�����s��
	//{
	//	float fovY = DirectX::XMConvertToRadians(45);	// ����p
	//	float aspectRatio = graphics.GetScreenWidth() / graphics.GetScreenHeight();	// ��ʏc���䗦
	//	float nearZ = 0.1f;	// �J�������f���o���̍ŋߋ���
	//	float farZ = 1000.0f;	// �J�������f���o���̍ŉ�����
	//	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspectRatio, nearZ, farZ);
	//	DirectX::XMStoreFloat4x4(&rc.projection, Projection);
	//}

	// 3D���f���`��
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);
		//�X�e�[�W�`��
	//	stage->Render(dc, shader);
		StageManager::Instance().Render(dc, shader);
		//�G�l�~�[�`��
		EnemyManager::Instance().Render(dc, shader);

		//�v���C���[�`��
		player->Render(dc, shader);

		shader->End(dc);
	}

	// 3D�f�o�b�O�`��
	{
		//�v���C���[�f�o�b�O�v���~�e�B�u�`��
		player->DrawDebugPrimitive();
		//�G�l�~�[�f�o�b�O�v���~�e�B�u�`��
		EnemyManager::Instance().DrawDebugPrimitive();
		// ���C�������_���`����s
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);

		// �f�o�b�O�����_���`����s
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);
	}

	//3D�G�t�F�N�g�`��
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}

	// 2D�X�v���C�g�`��
	{
		RenderEnemyGauge(dc, rc. view, rc. projection);
	}

	// 2D�f�o�b�OGUI�`��
	{
		//�v���C���[�f�o�b�O�`��
		player->DrawDebugGUI();
		
	}
}

//�G�l�~�[HP�Q�[�W�`��
void SceneGame::RenderEnemyGauge(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4 projection)
{
	//�r���[�|�[�g
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	dc->RSGetViewports(&numViewports, &viewport);

	//�ϊ��s��
	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

	//�S�Ă̓G�̓����HP�Q�[�W��\��
	EnemyManager& enemyManager = EnemyManager::Instance();
	int enemyCount = enemyManager.GetEnemyCount();

	for (int i = 0; i < enemyCount; ++i)
	{
		//	Enemy* enemy = enemyManager.GetEnemy(i);
		//	
		//	DirectX::XMFLOAT3 worldPosition = enemy->GetPosition();
		//	worldPosition.y += enemy->GetHeight();
		//	DirectX::XMVECTOR WorldPosition = DirectX::XMLoadFloat3(&worldPosition);

		//	//���[���h���W����X�N���[�����W�֕ϊ�
		//	DirectX::XMVECTOR ScreenPosition = DirectX::XMVector3Project(
		//		WorldPosition,//���[���h���W
		//		viewport.TopLeftX,	  //�r���[�|�[�g����X�ʒu
		//		viewport.TopLeftY,	  //�r���[�|�[�g����Y�ʒu
		//		viewport.Width,//�r���[�|�[�g��
		//		viewport.Height,//�r���[�|�[�g����
		//		viewport.MinDepth,//�[�x�l�͈̔͂�\���ŏ��l(0.0�ł悢)
		//		viewport.MaxDepth,//�[�x�l�͈̔͂�\���ő�l(1.0f�ł悢)
		//		Projection,//�v���W�F�N�V�����s��
		//		View,//�r���[�s��
		//		World//���[���h�s��(�P�ʍs��ŗǂ�)
		//		);

		//	//�X�N���[�����W
		//	DirectX::XMFLOAT2 screenPosition;
		//	DirectX::XMStoreFloat2(&screenPosition, ScreenPosition);

		//	//�Q�[�W�̒���
		//	const float gaugeWidth = 30.0f;
		//	const float gaugeHeight = 5.0f;

		//	float healthRate = enemy->GetHealth() /static_cast<float> (enemy->GetMaxHealth());

		//	//�Q�[�W�`��
		//	gauge->Render(
		//		dc,
		//		screenPosition.x - gaugeWidth * 0.5f,
		//		screenPosition.y - gaugeHeight,
		//		gaugeWidth * healthRate,
		//		gaugeHeight,
		//		0, 0,
		//		static_cast<float>(gauge->GetTextureWidth()),
		//		static_cast<float>(gauge->GetTextureHeight()),
		//		0.0f,
		//		1.0f, 0.0f, 0.0f, 1.0f
		//	);
		//}
		////�G�l�~�[�̔z�u����
		//Mouse& mouse = Input::Instance().GetMouse();
		//if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
		//{
		//	//�}�E�X�J�[�\�����W���擾
		//	DirectX::XMFLOAT3 screenPosition;
		//	screenPosition.x = static_cast<float>(mouse.GetPositionX());
		//	screenPosition.y = static_cast<float>(mouse.GetPositionY());

		//	DirectX::XMVECTOR ScreenPosition, WorldPosition;

		//	//���C�̎n�_���Z�o
		//	screenPosition.z = 0.0f;
		//	ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		//	WorldPosition = DirectX::XMVector3Unproject(
		//		ScreenPosition,
		//		viewport.TopLeftX,
		//		viewport.TopLeftY,
		//		viewport.Width,
		//		viewport.Height,
		//		viewport.MinDepth,
		//		viewport.MaxDepth,
		//		Projection,
		//		View,
		//		World
		//	);
		//	DirectX::XMFLOAT3 rayStart;
		//	DirectX::XMStoreFloat3(&rayStart, WorldPosition);

		//	//���C�̏I�_���Z�o
		//	screenPosition.z = 1.0f;
		//	ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		//	WorldPosition = DirectX::XMVector3Unproject(
		//		ScreenPosition,
		//		viewport.TopLeftX,
		//		viewport.TopLeftY,
		//		viewport.Width,
		//		viewport.Height,
		//		viewport.MinDepth,
		//		viewport.MaxDepth,
		//		Projection,
		//		View,
		//		World
		//	);
		//	DirectX::XMFLOAT3 rayEnd;
		//	DirectX::XMStoreFloat3(&rayEnd, WorldPosition);

		//	//���C�L���X�g
		//	HitResult hit;
		//	if (StageManager::Instance().RayCast(rayStart, rayEnd, hit))
		//	{
		//		//�G��z�u
		//		EnemySlime* slime = new EnemySlime();
		//		slime->SetPosition(hit.position);
		//		EnemyManager::Instance().Register(slime);
		//	}
		//}
	}
}
