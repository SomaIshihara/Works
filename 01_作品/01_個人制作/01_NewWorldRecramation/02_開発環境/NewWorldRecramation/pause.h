//==========================================
//
//�|�[�Y��ʕ\���v���O�����̃w�b�_[pause.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//�|�[�Y���j���[
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,
	PAUSE_MENU_RETRY,
	PAUSE_MENU_QUIT,
	PAUSE_MENU_MAX
} PAUSE_MENU;

//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#endif // !_PAUSE_H_
