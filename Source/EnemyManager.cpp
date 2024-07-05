#include"EnemyManager.h"    
#include"Collision.h"
//更新処理
void EnemyManager::Update(float elapsedTime)
{
    //範囲for文で管理しているエネミーの更新処理を一括実行
    for (Enemy* enemy : enemies)
    {
        enemy->Update(elapsedTime);
    }

    //破棄処理
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

    //敵同士の衝突判定
    CollisionEnemyVsEnemies();
}

//描画処理
void EnemyManager::Render(ID3D11DeviceContext* context, Shader* shader)
{
    for (Enemy* enemy : enemies)
    {
        enemy->Render(context, shader);
    }
}

//デバッグプリミティブ描画
void EnemyManager::DrawDebugPrimitive()
{
    for (Enemy* enemy : enemies)
    {
        enemy->DrawDebugPrimitive();
    }
}

void EnemyManager::Remove(Enemy* enemy)
{
    //破棄リストに追加
    removes.insert(enemy);
}

//エネミー登録
void EnemyManager::Register(Enemy* enemy)
{
    
    enemies.emplace_back(enemy);
}
//エネミー全削除
void EnemyManager::Clear()
{
  /*  for (Enemy* enemy : enemies)
    {
        delete enemy;
    }*/
        enemies.clear();
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
            //衝突処理
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