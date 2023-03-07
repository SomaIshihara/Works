//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �Ό��D�n
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,	// �^�C�g��BGM
	SOUND_LABEL_BGM_GAME,		// �Q�[��BGM
	SOUND_LABEL_BGM_RESULT,		// ����
	SOUND_LABEL_SE_START,		// �X�^�[�g
	SOUND_LABEL_SE_SHOT,		// �e����
	SOUND_LABEL_SE_CLEAR,		// �N���A
	SOUND_LABEL_SE_OVER,		// ���s
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
void PauseSound(SOUND_LABEL label);
void RestartSound(SOUND_LABEL label);

#endif
