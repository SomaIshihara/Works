//==========================================
//
//�G�֌W�v���O�����̃w�b�_[spot.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _SPOT_H_
#define _SPOT_H_

#include "main.h"
#include "file.h"

//�n�_��
typedef enum
{
	SPOTTYPE_START = 0,
	SPOTTYPE_HALFWAY,
	SPOTTYPE_GOAL,
	SPOTTYPE_MAX
} SPOTTYPE;

//�G�\���̒�`
typedef struct
{
	SPOTTYPE spotType;		//���
	D3DXVECTOR3 pos;	//�ʒu
	float fWidth;		//��
	float fHeight;		//����
	bool bDisp;			//�g�����ǂ����i���Ԓn�_�̂ݎg�p�B�X�^�[�g�E�S�[����true�j
} Spot;

//�v���g�^�C�v�錾
void InitSpot(void);
void UninitSpot(void);
void UpdateSpot(void);
void DrawSpot(void);
void SetSpot(Spot setSpotData);
void ResetSpot(void);
Spot *RefSpot(SPOTTYPE type, int nNumber);

#endif // !_SPOT_H_
