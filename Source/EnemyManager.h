#pragma once
#include<vector>
#include"Enemy.h"
#include<set>

//�G�l�~�[�}�l�[�W���[
class EnemyManager
{
private:
    EnemyManager() {};
    ~EnemyManager() {};
    void CollisionEnemyVsEnemies();
public:
    //�B��̃C���X�^���X�擾
    static EnemyManager& Instance()//�G�l�~�[�}�l�[�W���[�̓Q�[���ŗB��̂��̂Ƃ��Ĉ��������̂ŃV���O���g���ɂ���
    {
        static EnemyManager instance;
        return instance;
    }

    //�X�V����
    void Update(float elapsedTime);

    //�`�揈��
    void Render(ID3D11DeviceContext* dc, Shader* shader);

    //�G�l�~�[�o�^
    void Register(Enemy* enemy);

    //�G�l�~�[�S�폜
    void Clear();

    //�f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive();

    //�G�l�~�[�폜
    void Remove(Enemy* enemy);

    //�����̃G�l�~�[���Ǘ����邽�߁A�G�l�~�[�̃|�C���^��std::vector�ŊǗ�����

    int GetEnemyCount() const { return static_cast<int>(enemies.size()); }

    Enemy* GetEnemy(int index) { return enemies.at(index); }

   
private:
    std::vector<Enemy*>     enemies;
    std::set<Enemy*>        removes;

};
