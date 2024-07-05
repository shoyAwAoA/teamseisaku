#include"CameraController.h"
#include"Camera.h"
#include"Input/Input.h"

//更新処理
void CameraController::Update(float elpsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisRX();//右スティック
    float ay = gamePad.GetAxisRY();

    //カメラの回転速度
    float speed = rollSpeed * elpsedTime;

    //スティックの入力値に合わせてX軸とY軸を回転
    angle.y += ax * speed;
    angle.x += ay * speed;

    //X軸のカメラ回転を制限

    if (angle.x > maxAngleX)
    {
        angle.x = maxAngleX;
    }
    if (angle.x < minAngleX)
    {
        angle.x = minAngleX;
    }



    //Y軸の回転値を-3.14〜3.14に収まるようにする
    if (angle.y < -DirectX::XM_PI)
    {
        angle.y += DirectX::XM_2PI;
    }
    if (angle.y > DirectX::XM_PI)
    {
        angle.y -= DirectX::XM_2PI;
    }



    //カメラ回転値を回転行列に変換
    DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

    //回転行列から前方向ベクトルを取り出す//前方向はZjiku 
    DirectX::XMVECTOR Front = Transform.r[2];
    DirectX::XMFLOAT3 front;
    DirectX::XMStoreFloat3(&front, Front);

    //注視点から後ろのベクトル方向に一定距離離れたカメラ視点を求める
    DirectX::XMFLOAT3 eye;
    /*eye.x = target.x - front.x * range;
    eye.y = target.y - front.y * range;
    eye.z = target.z - front.z * range;*/
    eye.x = 24 - front.x * range;
    eye.y = 40 - front.y * range;
    eye.z = -180 - front.z * range;

    //カメラの視点と注視点を設定
    Camera::Instance().SetLookAt(eye,{ 24, 0, 0
}, DirectX::XMFLOAT3(0, 1, 0));

}
