#include"EnemyManager.h"    
#include"Collision.h"
//�X�V����
void EnemyManager::Update(float elapsedTime)
{
    //�͈�for���ŊǗ����Ă���G�l�~�[�̍X�V�������ꊇ���s
    for (Enemy* enemy : enemies)
    {
        enemy->Update(elapsedTime);
    }

    for (notEnemy* notenemy : notenemies)
    {
        notenemy->Update(elapsedTime);
    }
    for (boss* boss1 : bosss)
    {
        boss1->Update(elapsedTime);
    }

    //�j������
    for (Enemy* enemy : removes)
    {
        std::vector<Enemy*>::iterator it = std::find(enemies.begin(), enemies.end(),enemy);

        if (it != enemies.end())
        {
            enemies.erase(it);
        }
        delete enemy;

    }


        removes.clear();

    //�G���m�̏Փ˔���
    CollisionEnemyVsEnemies();
}

//�`�揈��
void EnemyManager::Render(ID3D11DeviceContext* context, Shader* shader)
{
    for (Enemy* enemy : enemies)
    {
        enemy->Render(context, shader);
    }

    for (notEnemy* notenemy : notenemies)
    {
        notenemy->Render(context, shader);
    }
    for (boss* boss1 : bosss)
    {
        boss1->Render(context, shader);
    }
}

//�f�o�b�O�v���~�e�B�u�`��
void EnemyManager::DrawDebugPrimitive()
{
    for (Enemy* enemy : enemies)
    {
        enemy->DrawDebugPrimitive();
    }
}

void EnemyManager::Remove(Enemy* enemy)
{
    //�j�����X�g�ɒǉ�
    removes.insert(enemy);
}

void EnemyManager::Remove(notEnemy* notenemy)
{
    notremoves.insert(notenemy);
}

void EnemyManager::Remove(boss* boss)
{
    bossremoves.insert(boss);
}

//�G�l�~�[�o�^
void EnemyManager::Register(Enemy* enemy)
{
    
    enemies.emplace_back(enemy);
}
void EnemyManager::Register(notEnemy* notenemy)
{
    notenemies.emplace_back(notenemy);
}
void EnemyManager::Register(boss* boss)
{
    bosss.emplace_back(boss);
}
//�G�l�~�[�S�폜
void EnemyManager::Clear()
{
    for (Enemy* enemy : enemies)
    {
        delete enemy;
    }
    for (notEnemy* notenemy : notenemies)
    {
        delete notenemy;
    }
    for (boss* boss : bosss)
    {
        delete boss;
    }
  
        enemies.clear();
        notenemies.clear();
        bosss.clear();
}

void EnemyManager::CollisionEnemyVsEnemies()
{
    EnemyManager& enemyManager = EnemyManager::Instance();
    int enemyCount = enemyManager.GetEnemyCount();  
    for (int i = 0; i < enemyCount; ++i)
    {
        Enemy* enemy1 = EnemyManager::GetEnemy(i);
        for (int n = 1; n < enemyCount; ++n)
        {
            Enemy* enemy2 = EnemyManager::GetEnemy(n);
            //�Փˏ���
            DirectX::XMFLOAT3 outPosition;
           /* if (Collision::IntersectSphereVeSphere(
                enemy1->GetPosition(),
                enemy1->GetRadius(),
                enemy2->GetPosition(),
                enemy2->GetRadius(),
                outPosition
            ));
            {
                enemy2->SetPosition(outPosition);
            }*/
            if (Collision::IntersectCylinderVsCylinder(
                enemy1->GetPosition(),
                enemy1->GetRadius(),
                enemy1->GetHeight(),
                enemy2->GetPosition(),
                enemy2->GetRadius(),
                enemy2->GetHeight(),
                outPosition
            ))
            {
                enemy2->SetPosition(outPosition);
            }
        }
       
    }
}