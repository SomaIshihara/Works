//==========================================
//
//�e�v���O�����̃w�b�_[shadow.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//�\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	bool bUse;				//�g�p�̗L��
} Shadow;

//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(void);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void ReleaseIdxShadow(int nIdxShadow);

#endif // !_SHADOW_H_
