//==========================================
//
//�`���[�g���A���֌W�v���O�����̃w�b�_[tutorial.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//�`���[�g���A���y�[�W��
typedef enum
{
	TUTORIAL_CONFIG1 = 0,
	TUTORIAL_CONFIG2,
	TUTORIAL_SCORE,
	TUTORIAL_MAX
} TUTORIAL;

//�v���g�^�C�v�錾
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorial(int move);
TUTORIAL GetTutorial(void);

#endif // !_TUTORIAL_H_
