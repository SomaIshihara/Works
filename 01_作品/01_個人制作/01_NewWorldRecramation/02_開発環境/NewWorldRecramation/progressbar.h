//==========================================
//
//�i�s�x�\���v���O�����̃w�b�_[progressbar.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _PROGRESSBAR_H_
#define _PROGRESSBAR_H_

#include "main.h"

//�}�N��
#define PROGLINE_APPEMIN_ROP	(0.5f)	//�{�X�Œ჉�C���̐i�s�x
#define PROGLINE_APPEMAX_ROP	(0.7f)	//�{�X�Œ჉�C���̐i�s�x

//�v���g�^�C�v�錾
void InitProgressBar(void);
void UninitProgressBar(void);
void UpdateProgressBar(void);
void DrawProgressBar(void);
void SetRateofProg(float fRoP);
float GetProgress(void);

#endif // !_PROGRESSBAR_H_
