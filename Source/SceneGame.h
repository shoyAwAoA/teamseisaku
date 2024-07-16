#pragma once

//#include"Stage.h"
#include"Effect.h"
#include"Player.h"
#include"CameraController.h"
#include"EnemySlime.h"
#include"Scene.h"
#include"Graphics/Sprite.h"
#include"kowasenai.h"
#include"Audio/AudioSource.h"
#include<string>

// �Q�[���V�[��
class SceneGame :public Scene
{
public:
	SceneGame(){}
	//~SceneGame() {}

	// ������
	//void Initialize();
	void Initialize()override;

	// �I����
//	void Finalize();
	void Finalize()override;

	// �X�V����
//	void Update(float elapsedTime);
	void  Update(float elapsedTime)override;

	// �`�揈��
	//void Render();
	void Render()override;


	
private:
	//�G�l�~�[HP�Q�[�W�`��
	void RenderEnemyGauge(
		ID3D11DeviceContext* dc,
		const DirectX::XMFLOAT4X4& view,
		const DirectX::XMFLOAT4X4 projection
	);

private:
	//Stage* stage = nullptr;
	Player* player = nullptr;
	CameraController* cameraController = nullptr;
	EnemySlime* enemyslime = nullptr;
	Sprite* gauge = nullptr;
	std::unique_ptr<AudioSource> game_bgm;

	
	int timer0;
	int timer1;
	int timer2;
	int timer3;
	int timer4;
	int  ramdam0=0;
	int  enemyType = 0;
	
private:
	Effect* kurogiri2 = nullptr;

	Sprite* score;
};




