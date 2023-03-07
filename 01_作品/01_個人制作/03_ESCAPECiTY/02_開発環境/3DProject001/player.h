//==========================================
//
//�v���C���[�v���O�����̃w�b�_[player.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "model.h"

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	float fLength;
	float fAngle;
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	Model aModel[EXITHUMAN_MODEL_NUM];		//���f��
	int nNumModel;			//�p�[�c����
	D3DXMATRIX mtxWorld;	//���[���h�}�g��
	bool bIntoSafeArea;		//�Z�[�t�G���A�ɓ����Ă��邩
	bool bInfection;		//�������Ă��邩�i��o���͓G�ɓ����������̔���̂݁j
	Motion mMotion;			//���[�V����
} Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

#endif // !_PLAYER_H_
