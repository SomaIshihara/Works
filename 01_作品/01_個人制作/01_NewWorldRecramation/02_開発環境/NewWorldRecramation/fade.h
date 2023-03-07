//==========================================
//
//�t�F�[�h�\���v���O�����̃w�b�_[fade.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE = 0,	//�������Ȃ�
	FADE_IN,		//�C��
	FADE_OUT,		//�A�E�g
	FADE_MAX
} FADE;

//�v���g�^�C�v�錾
void InitFade(MODE nodenext, GAMERESULT result);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modenext, GAMERESULT result);
FADE GetFade(void);

#endif // !_FADE_H_
