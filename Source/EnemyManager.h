#pragma once
#include<vector>
#include"Enemy.h"
#include<set>

//エネミーマネージャー
class EnemyManager
{
private:
    EnemyManager() {};
    ~EnemyManager() {};
    void CollisionEnemyVsEnemies();
public:
    //唯一のインスタンス取得
    static EnemyManager& Instance()//エネミーマネージャーはゲームで唯一のものとして扱いたいのでシングルトンにする
    {
        static EnemyManager instance;
        return instance;
    }

    //更新処理
    void Update(float elapsedTime);

    //描画処理
    void Render(ID3D11DeviceContext* dc, Shader* shader);

    //エネミー登録
    void Register(Enemy* enemy);

    //エネミー全削除
    void Clear();

    //デバッグプリミティブ描画
    void DrawDebugPrimitive();

    //エネミー削除
    void Remove(Enemy* enemy);

    //複数のエネミーを管理するため、エネミーのポインタをstd::vectorで管理する

    int GetEnemyCount() const { return static_cast<int>(enemies.size()); }

    Enemy* GetEnemy(int index) { return enemies.at(index); }

   
private:
    std::vector<Enemy*>     enemies;
    std::set<Enemy*>        removes;

};
