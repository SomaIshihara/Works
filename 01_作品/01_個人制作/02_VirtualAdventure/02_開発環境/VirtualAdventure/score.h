//==========================================
//
//�X�R�A�\���v���O�����̃w�b�_[score.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//�}�N��
#define SCORE_DIGIT				(8)		//���������Ŏg�p����|���S����

//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetPoint(int nScore);
void AddPoint(int nValue);
int GetScore(void);
int GetHighScore(void);
void DecisionScore(void);

#endif // !_SCORE_H_
