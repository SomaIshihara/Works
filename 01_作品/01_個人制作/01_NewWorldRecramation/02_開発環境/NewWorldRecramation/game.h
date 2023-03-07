//==========================================
//
//�Q�[���v���C�֌W�v���O�����̃w�b�_[game.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//�}�N��
#define STAGE_NUM	(5)	//�X�e�[�W��

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE = 0,		//�������Ă��Ȃ�
	GAMESTATE_NORMAL,		//�ʏ�
	GAMESTATE_END,			//�I��
	GAMESTATE_MAX
} GAMESTATE;

typedef enum
{
	STAGE_TIMEATTACK = 0,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_LAST,
	STAGE_SECRET,
	STAGE_MAX
} STAGE;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state, int nCounter, GAMERESULT result);
GAMESTATE GetGameState(void);
void SetEnablePause(bool bPause);
void SetStage(STAGE stage);
STAGE GetStage(void);

#endif // !_GAME_H_
