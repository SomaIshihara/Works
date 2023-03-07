//==========================================
//
//�Q�[���v���O����[game.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "game.h"
#include "result.h"
#include "wall.h"
#include "player.h"
#include "enemy.h"
#include "shadow.h"
#include "bullet.h"
#include "meshfield.h"
#include "sky.h"
#include "object.h"
#include "model.h"
#include "timer.h"
#include "file.h"
#include "input.h"
#include "camera.h"

//�}�N��
#define GAME_CLEAR_TIME	(0 * 60)	//�Q�[���N���A�ɂ���܂ł�����؍ݎ���

//�O���[�o��
int g_nCnterSafeAreaTime;
int g_nCnterTimer;

//========================
//����������
//========================
void InitGame(void)
{
	//�ϐ�������
	g_nCnterSafeAreaTime = 0;
	g_nCnterTimer = 0;

	//�I�u�W�F�N�g������
	InitSky();
	InitMeshfield();
	InitWall();
	InitBullet();
	InitShadow();
	InitModel();
	LoadMotionFile();
	InitPlayer();
	InitEnemy();
	InitObject();
	InitTimer();

	//�ǐ����i�f�W���u�j
	//���ʂ̕�
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 1120.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 2720.0f, 80.0f, false);		//�O
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -1120.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 2720.0f, 80.0f, false);		//��
	SetWall(D3DXVECTOR3(-1360.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 2240.0f, 50.0f, false);	//��
	SetWall(D3DXVECTOR3(1360.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 2240.0f, 50.0f, false);		//�E

	//��l�̕�
	SetWall(D3DXVECTOR3(-960.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-480.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(480.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(960.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-1040.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-400.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-80.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(80.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(400.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(1040.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-1040.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-880.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-560.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-400.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-80.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(560.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(880.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(1040.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(0.0f, 0.0f, 160.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -160.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(480.0f, 0.0f, 160.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(480.0f, 0.0f, -160.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-1040.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-880.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-560.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(560.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(880.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(1040.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(0.0f, 0.0f, -320.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-480.0f, 0.0f, -320.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-480.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-1040.0f, 0.0f, -720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(80.0f, 0.0f, -720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(400.0f, 0.0f, -720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(1040.0f, 0.0f, -720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-960.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(480.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(960.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	//�t�@�C���ǂݍ��݁E�I�u�W�F�N�g����
	LoadMapFile();
}

//========================
//�I������
//========================
void UninitGame(void)
{
	//�I������
	UninitTimer();
	UninitObject();
	UninitEnemy();
	UninitPlayer();
	UninitModel();
	UninitShadow();
	UninitBullet();
	UninitWall();
	UninitMeshfield();
	UninitSky();
}

//========================
//�X�V����
//========================
void UpdateGame(void)
{
	Player *pPlayer = GetPlayer();
	//�e
	UpdateShadow();

	//��
	UpdateSky();

	//���b�V���t�B�[���h
	UpdateMeshfield();

	//��
	UpdateWall();

	//�e
	UpdateBullet();

	//���f��
	UpdateModel();

	//�v���C���[
	UpdatePlayer();

	//�G
	UpdateEnemy();

	//�I�u�W�F�N�g
	UpdateObject();

	//�^�C�}�[
	g_nCnterTimer++;
	if (GetTimer() < MAX_TIME && g_nCnterTimer >= MAX_FPS)
	{
		g_nCnterTimer = 0;
		AddTimer(1);
	}
	UpdateTimer();

	//�Z�[�t�G���A�ɓ����Ă��邩�m�F
	if (pPlayer->bIntoSafeArea == true)
	{
		g_nCnterSafeAreaTime++;
		if (g_nCnterSafeAreaTime >= GAME_CLEAR_TIME)
		{
			SetResult(RESULT_CLEAR);
			SetMode(MODE_RESULT);
			ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
		}
	}
	else
	{
		g_nCnterSafeAreaTime = 0;
	}

	//[��o�p]�G�ɓ���������
	if (pPlayer->bInfection == true)
	{
		SetResult(RESULT_OVER);
		SetMode(MODE_RESULT);
		ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
	}
}

//========================
//�`�揈��
//========================
void DrawGame(void)
{
	//��
	DrawSky();

	//���b�V���t�B�[���h
	DrawMeshfield();

	//�e
	DrawShadow();

	//�e
	DrawBullet();

	//��
	DrawWall();

	//�v���C���[
	DrawPlayer();

	//�G
	DrawEnemy();

	//�I�u�W�F�N�g
	DrawObject();

	//�^�C�}�[
	DrawTimer();
}