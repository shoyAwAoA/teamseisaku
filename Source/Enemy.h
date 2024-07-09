#pragma once

#include"Graphics/Shader.h"
#include"Character.h"

//�G�l�~�[
class Enemy :public Character
{
public:
    Enemy() {};
    ~Enemy() override {}


    //�X�V����
    virtual void Update(float elapsedTime) = 0;//�p����ŕK������������悤�ɏ������z�֐��ɂ���

    //�`�揈��
    virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

    //�f�o�b�O�v���~�e�B�u�`��
    virtual void DrawDebugPrimitive();

    virtual void DebugPrimitive();

    //�j��
    void Destroy();
};

class notEnemy :public Character
{
public:
    notEnemy() {};
    ~notEnemy() override {}

    //�X�V����
    virtual void Update(float elapsedTime) = 0;//�p����ŕK������������悤�ɏ������z�֐��ɂ���

    //�`�揈��
    virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

    //�f�o�b�O�v���~�e�B�u�`��
    virtual void DrawDebugPrimitive();

    //�j��
    void Destoroy();

};

class boss :public Character
{
public:
    boss() {};
    ~boss() override {}

    //�X�V����
    virtual void Update(float elapsedTime) = 0;//�p����ŕK������������悤�ɏ������z�֐��ɂ���

    //�`�揈��
    virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

    //�f�o�b�O�v���~�e�B�u�`��
    virtual void DrawDebugPrimitive();

    //�j��
    void Destoroy();
};


