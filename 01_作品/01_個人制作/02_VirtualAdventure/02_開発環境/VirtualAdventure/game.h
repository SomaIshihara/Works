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

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state, int nCounter);
GAMESTATE GetGameState(void);
void SetEnablePause(bool bPause);

#endif // !_GAME_H_
