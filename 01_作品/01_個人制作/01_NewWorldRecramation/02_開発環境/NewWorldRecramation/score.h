//==========================================
//
//�X�R�A�\���v���O�����̃w�b�_[score.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//�v���g�^�C�v�錾
void InitScore(D3DXVECTOR3 pos, float fMag);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int GetScore(void);

#endif // !_SCORE_H_
