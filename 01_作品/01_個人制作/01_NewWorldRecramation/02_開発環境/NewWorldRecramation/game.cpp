//==========================================
//
//�Q�[���v���C�֌W�v���O����[Game.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "game.h"
#include "player.h"
#include "bg.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "timer.h"
#include "sound.h"
#include "file.h"
#include "frame.h"
#include "gauge.h"
#include "fade.h"
#include "effect.h"
#include "item.h"
#include "pause.h"
#include "particle.h"
#include "damagezone.h"
#include "map.h"
#include "ranking.h"
#include "progressbar.h"
#include "hpenestat.h"
#include "selectstage.h"

//�}�N��
#define GAME_SCORE_MAG			(0.375f)

//�O���[�o��
GAMESTATE g_gameState = GAMESTATE_NONE;	//�Q�[���̏��
GAMERESULT g_gameResult = GAMERESULT_MAX;	//�Q�[������
int g_nCounterGameState = 0;				//��ԊǗ��J�E���^
bool g_bPause = false;					//�|�[�Y���
bool g_bScreenShot = false;				//�X�N�V���B�e���[�h
bool g_bDispdebug = false;				//�f�o�b�O���
int g_nCounterTimer = 0;				//����
int g_nreadEnemyNum;					//�ǂݎ�����G�̐�
STAGE g_stage;							//�ݒ�X�e�[�W

//========================
//�Q�[����ʏ���������
//========================
void InitGame(void)
{
	//�w�i�̏���������
	InitBg();

	//�g�̏�����
	InitFrame();

	//�v���O���X�o�[������
	InitProgressBar();

	//�v���C���[�̏���������
	InitPlayer();

	//HP�E�G�l���M�[�Q�[�W�̏�����
	InitGauge();

	//HP�E�G�l���M�[�e�L�X�g�̏�����
	InitHpEneStat();

	//�e�̏���������
	InitBullet();

	//�����̏���������
	InitExplosion();

	//�G�t�F�N�g
	InitEffect();

	//�p�[�e�B�N��
	InitParticle();

	//�t�@�C���ǂݎ��i�X�e�[�W�ɂ���ĈقȂ�
	LoadMapEnemyFile();

	//�}�b�v�i�X�e�[�W�ɂ���ĈقȂ�
	InitMap();

	//�G�̏���������
	InitEnemy();

	//�_���[�W�]�[���̏�����
	InitDamageZone();

	//�A�C�e���̏�����
	InitItem();

	//�X�R�A����������
	InitScore(D3DXVECTOR3(936.0f, 120.0f, 0.0f), GAME_SCORE_MAG);

	//�X�R�A�\��
	SetScore(0);

	if (g_stage == STAGE_TIMEATTACK)
	{
		//���ԏ�����
		InitTimer();
	}

	//�|�[�Y������
	InitPause();

	g_gameState = GAMESTATE_NORMAL;	//�Q�[���̏��
	g_nCounterGameState = 0;		//��ԊǗ��J�E���^
	g_bPause = false;				//�|�[�Y���
	g_bDispdebug = false;			//�f�o�b�O���
	g_bScreenShot = false;			//�X�N�V���B�e���[�h
	g_nCounterTimer = 0;			//����
}

//========================
//�Q�[����ʏI������
//========================
void UninitGame(void)
{
	g_gameState = GAMESTATE_NONE;
	StopSound();

	//�|�[�Y���
	UninitPause();

	if (g_stage == STAGE_TIMEATTACK)
	{
		//����
		UninitTimer();
	}

	//�X�R�A
	UninitScore();

	//�A�C�e��
	UninitItem();

	//�_���[�W�]�[��
	UninitDamageZone();

	//�G�̏I������
	UninitEnemy();

	//�}�b�v
	UninitMap();

	//�p�[�e�B�N��
	UninitParticle();

	//�G�t�F�N�g
	UninitEffect();

	//�����̏I������
	UninitExplosion();

	//�e�̏I������
	UninitBullet();

	//HP�E�G�l���M�[�e�L�X�g�̏I��
	UninitHpEneStat();

	//HP�E�G�l���M�[�Q�[�W�̏I��
	UninitGauge();

	//�v���C���[�̏I������
	UninitPlayer();

	//�v���O���X�o�[
	UninitProgressBar();

	//�g�̏I��
	UninitFrame();

	//�w�i�̏I������
	UninitBg();
}

//========================
//�Q�[����ʍX�V����
//========================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true && GetGameState() != GAMESTATE_END && GetFade() == FADE_NONE)
	{//P�L�[�����ꂽ
		if (g_bPause)
		{
			g_bPause = false;
			g_bScreenShot = false;
			RestartSound(GetPlayBGM());
		}
		else
		{
			g_bPause = true;
			PauseSound(GetPlayBGM());
		}
	}

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1) == true)
	{
		g_bDispdebug = g_bDispdebug ? false : true;
	}
#endif // _DEBUG

	Player *pPlayer = GetPlayer();
	if (g_bPause)
	{//�|�[�Y���
		if (GetKeyboardTrigger(DIK_F2) == true)
		{//F1�����ꂽ
			g_bScreenShot = g_bScreenShot ? false : true;
		}

		if (!g_bScreenShot)
		{//�X�N�V���B�e���[�h�ł͂Ȃ�
			UpdatePause();
		}
	}
	else
	{//�|�[�Y���ĂȂ�
	 //�e��I�u�W�F�N�g�̍X�V����
		//�w�i
		UpdateBg();

		//�g
		UpdateFrame();

		//�v���C���[
		UpdatePlayer();

		//HP�E�G�l���M�[�Q�[�W
		UpdateGauge();

		//HP�E�G�l���M�[�e�L�X�g
		UpdateHpEneStat();

		//�e
		UpdateBullet();

		//����
		UpdateExplosion();

		//�p�[�e�B�N��
		UpdateParticle();

		//�G�t�F�N�g
		UpdateEffect();

		//�}�b�v
		UpdateMap();

		//�G
		UpdateEnemy();

		//�_���[�W�]�[��
		UpdateDamageZone();

		//�A�C�e��
		UpdateItem();

		//�X�R�A
		UpdateScore();

		if (g_stage == STAGE_TIMEATTACK)
		{//�^�C���A�^�b�N�͎��Ԏg��
		 //����
			if (g_gameState != GAMESTATE_END)
			{
				if (GetTimer() == 0)
				{
					SetGameState(GAMESTATE_END, 60, GAMERESULT_CLEAR);
				}
				else
				{
					g_nCounterTimer++;
					if (g_nCounterTimer >= 60)
					{
						AddTimer(-1);
						UpdateTimer();
						g_nCounterTimer = 0;
					}
				}
			}
		}
		else
		{//�X�g�[�����[�h�̂Ƃ��̓v���O���X�o�[��������
			if (g_gameState != GAMESTATE_END)
			{
				UpdateProgressBar();
			}
		}
	}

	if (g_bDispdebug)
	{
		pPlayer->nLife = pPlayer->nMaxLife;
	}


	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_END:
		g_nCounterGameState--;	//�J�E���g���炷
		if (g_nCounterGameState <= 0 && GetFade() == FADE_NONE)
		{
			if (g_stage == STAGE_TIMEATTACK)
			{
				SetRanking(GetScore());	//�����L���O���f�i2���Ԃ̂݁j
			}
			else if (g_stage >= STAGE_1 && g_stage <= STAGE_LAST && g_gameResult == GAMERESULT_CLEAR)
			{
				SetStoryScore(GetScore(), g_stage);

				//���X�g�X�e�[�W�̓G���h���[���ɑJ��
				if (g_stage == STAGE_LAST)
				{
					SetFade(MODE_ENDING, g_gameResult);
					break;
				}
			}
			SetFade(MODE_RESULT, g_gameResult);
			break;
		}
	}
}

//========================
//�Q�[����ʕ`�揈��
//========================
void DrawGame(void)
{
	//�����������`�揈��
	//�w�i
	DrawBg();

	//�p�[�e�B�N��
	DrawParticle();

	//�G�t�F�N�g
	DrawEffect();

	//�e
	DrawBullet();

	//�A�C�e��
	DrawItem();

	//����
	DrawExplosion();

	//�}�b�v
	DrawMap();

	//�G
	DrawEnemy();

	//�v���C���[
	DrawPlayer();

	//�_���[�W�]�[��
	DrawDamageZone();

	//�g
	DrawFrame();

	//HP�E�G�l���M�[�Q�[�W
	DrawGauge();

	//HP�E�G�l���M�[�e�L�X�g
	DrawHpEneStat();

	//�X�R�A
	DrawScore();
	
	if (g_stage == STAGE_TIMEATTACK)
	{
		//����
		DrawTimer();
	}
	else
	{
		//�v���O���X�o�[
		DrawProgressBar();
	}

	if (g_bPause && !g_bScreenShot)
	{
		DrawPause();
	}

#if 1
#ifdef _DEBUG
	if (g_bDispdebug)
	{
		//�f�o�b�O�iFPS�\��
		DrawFPS();

		//�f�o�b�O�i���W�\��
		DrawMove();

		//�f�o�b�O�iU���W�\��
		DrawTexU();
	}
#endif // _DEBUG
#endif // 0
}

//========================
//�Q�[����Ԑݒ菈��
//========================
void SetGameState(GAMESTATE state, int nCounter, GAMERESULT result)
{
	g_gameState = state;
	g_nCounterGameState = nCounter;
	g_gameResult = result;
}

//========================
//�Q�[����Ԏ擾����
//========================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//========================
//�|�[�Y�؂�ւ�����
//========================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

//========================
//�X�e�[�W�ݒ菈��
//========================
void SetStage(STAGE stage)
{
	g_stage = stage;
}

//========================
//�X�e�[�W�擾����
//========================
STAGE GetStage(void)
{
	return g_stage;
}