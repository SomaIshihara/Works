//==========================================
//
//�X�R�A�\���v���O�����̃w�b�_[timer.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

//�}�N��
#define MAX_TIME				(100 * 60 - 1)	//�ő厞��

//�v���g�^�C�v�錾
void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
void SetTimer(int nTimer);
void AddTimer(int nValue);
int GetTimer(void);

#endif // !_TIMER_H_
