//==========================================
//
//���ԕ\���v���O�����̃w�b�_[timer.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

//�}�N��
#define MAX_TIME				(100 * 60 - 1)	//�ő厞��
#define TIMER_CHAR_SIZE_WIDTH	((CHAR_TEX_WIDTH / CHAR_PATT_WIDTH) * 1.0f)		//�����T�C�Y�i�{���̂ݐݒ�j
#define TIMER_CHAR_SIZE_HEIGHT	((CHAR_TEX_HEIGHT / CHAR_PATT_HEIGHT) * 1.0f)	//�����T�C�Y�i�{���̂ݐݒ�j

//�v���g�^�C�v�錾
void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
void SetTimer(int nTimer);
void AddTimer(int nValue);
int GetTimer(void);

#endif // !_TIMER_H_
