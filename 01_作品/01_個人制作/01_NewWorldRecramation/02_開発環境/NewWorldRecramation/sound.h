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
	SOUND_LABEL_BGM_2ATK = 0,	// BGM�i2����TA: Be Happy - Ucchii0�j
	SOUND_LABEL_BGM_STG1,		// BGM�iSTG1: Tomorrow Land - �����j
	SOUND_LABEL_BGM_STG2,		// BGM�iSTG2: Flower - �����j
	SOUND_LABEL_BGM_STG3,		// BGM�iSTG3: �n�������E�l�b�g���[�N - �����j
	SOUND_LABEL_BGM_STG4,		// BGM�iSTG4: Trick style - �܂�ڂ��񓙕��j
	SOUND_LABEL_BGM_STGL,		// BGM�iSTGL: Empathy - Ucchii0 feat.Haruna�i�t�@�C�����͓ǂݍ��݃G���[�h�~�̂���Trick style�̏�ԁj�j
	SOUND_LABEL_SE_TOPSTART,	// �N�����̉�ʂ�Enter
	SOUND_LABEL_SE_ALART,		// �x��
	SOUND_LABEL_SE_MESSAGE,		// ���b�Z�[�W
	SOUND_LABEL_SE_HEALHP,		// HP��
	SOUND_LABEL_SE_HEALENE,		// �G�l���M�[��
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_HIT,			// �q�b�g��
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_PRSENTER,	// Enter�L�[��������
	SOUND_LABEL_SE_CLEAR,		// �~�b�V�����N���A
	SOUND_LABEL_SE_OVER,		// �~�b�V�������s
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
