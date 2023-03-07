//==========================================
//
//�Q�[���v���C�֌W�v���O����[Game.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "map.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "score.h"
#include "input.h"
#include "file.h"
#include "pause.h"
#include "timer.h"
#include "sound.h"

//�O���[�o��
GAMESTATE g_gameState = GAMESTATE_NONE;	//�Q�[���̏��
int g_nCounterGameState = 0;			//��ԊǗ��J�E���^
bool g_bPause = false;					//�|�[�Y���
bool g_bScreenShot = false;				//�X�N�V���B�e���[�h
bool g_bDispdebug = false;				//�f�o�b�O���
int g_nCounterTimer = 0;				//����

//========================
//�Q�[����ʏ���������
//========================
void InitGame(void)
{
	//�K�v�Ȃ��́Fcamera,player,score,timer

	//�v���C���[�̏���������
	InitPlayer();

	//�J����
	InitCamera();

	//�X�R�A
	InitScore();

	//�|�[�Y
	InitPause();

	//����
	InitTimer();

	g_gameState = GAMESTATE_NORMAL;	//�Q�[���̏��
	g_nCounterGameState = 0;		//��ԊǗ��J�E���^
	g_bPause = false;				//�|�[�Y���
	g_bDispdebug = false;			//�f�o�b�O���
	g_bScreenShot = false;			//�X�N�V���B�e���[�h
	g_nCounterTimer = 0;			//����

	//���y�Đ�
	PlaySound(SOUND_LABEL_BGM_GAME);
}

//========================
//�Q�[����ʏI������
//========================
void UninitGame(void)
{
	//���y��~
	StopSound(SOUND_LABEL_BGM_GAME);

	//�Q�[����ԏ�����
	g_gameState = GAMESTATE_NONE;

	//����
	UninitTimer();

	//�|�[�Y
	UninitPause();

	//�X�R�A
	UninitScore();

	//�J����
	UninitCamera();

	//�v���C���[�̏I������
	UninitPlayer();
}

//========================
//�Q�[����ʍX�V����
//========================
void UpdateGame(void)
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1) == true)
	{
		g_bDispdebug = g_bDispdebug ? false : true;
	}
#endif // _DEBUG

	//�|�[�Y�؂�ւ�
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}
	else if (GetUseGamepad() == true && GetGamepadTrigger(XINPUT_GAMEPAD_START) == true)
	{
		g_bPause = g_bPause ? false : true;
	}

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
		//�}�b�v�̗�
		UpdateMap();

		//�v���C���[
		UpdatePlayer();

		//�J����
		UpdateCamera();

		//�X�R�A
		UpdateScore();

		//����
		//�ő厞�ԂłȂ���΃J�E���^�[���Z
		if (g_nCounterTimer < MAX_TIME)
		{
			g_nCounterTimer++;
		}

		//�J�E���^�[��1�b���o��������s
		if (g_nCounterTimer >= 60)
		{
			g_nCounterTimer = 0;
			AddTimer(1);
		}
		UpdateTimer();
	}

	//�Q�[���I���Ȃ��ʑJ��
	if (g_gameState == GAMESTATE_END)
	{
		DecisionScore();
		SetMode(MODE_RESULT);
	}
}

//========================
//�Q�[����ʕ`�揈��
//========================
void DrawGame(void)
{
	//�����������`�揈��
	//�v���C���[
	DrawPlayer();

	//�J�����͕`��Ȃ�

	//�X�R�A
	DrawScore();

	//����
	DrawTimer();

	//�|�[�Y
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

		//�ʒu
		DrawPos();

		//�ړ���
		DrawSpeed();
	}
#endif // _DEBUG
#endif // 0
}

//========================
//�Q�[����Ԑݒ菈��
//========================
void SetGameState(GAMESTATE state, int nCounter)
{
	g_gameState = state;
	g_nCounterGameState = nCounter;
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