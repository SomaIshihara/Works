//==========================================
//
//�Q�[���v���O�����̃w�b�_[game.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//�}�N��
#define SAFEAREA_MIN_X		(-80.0f)
#define SAFEAREA_MIN_Z		(798.0f)
#define SAFEAREA_MAX_X		(80.0f)
#define SAFEAREA_MAX_Z		(1120.0f)

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

#endif // !_GAME_H_
