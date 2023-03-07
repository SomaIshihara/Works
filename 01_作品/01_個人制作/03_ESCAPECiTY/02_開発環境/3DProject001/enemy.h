//==========================================
//
//�G�v���O�����̃w�b�_[enemy.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "model.h"
#include "object.h"

//�}�N��
#define MAX_ENEMY	(64)	//�G����

//�G�\����
typedef struct
{
	//�z�u�֌W
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOld;
	float fLength;
	float fAngle;
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	Model aModel[EXITHUMAN_MODEL_NUM];			//�g�p���f��
	int nNumModel;			//�p�[�c����
	D3DXMATRIX mtxWorld;	//���[���h�}�g��
	int nIdxShadow;			//�e�ԍ�

	//�p�����[�^�֌W
	int nLife;				//�̗�
	OBJSTATE state;			//���
	int nCounterState;		//��ԕω��܂ł̎���

	bool bUse;				//�g�p���邩
} Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELNAME name, int nLife);
Enemy *GetEnemy(void);
void HitEnemy(int nNumObj);
void DestroyEnemy(int nNumObj);

#endif // !_ENEMY_H_
