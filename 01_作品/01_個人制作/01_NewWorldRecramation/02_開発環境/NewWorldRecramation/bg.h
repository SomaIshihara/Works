//==========================================
//
//�e�\���v���O�����̃w�b�_[bullet.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _BG_H_
#define _BG_H_

//�}�N��
#define BG_TEX_SPEED	(0.0025f)	//�e�N�X�`���̈ړ����x
#define BG_TEX_HEIGHT	(360)		//�e�N�X�`���̕�

//�v���g�^�C�v�錾
void InitBg(void);
void UninitBg(void);
void UpdateBg(void);
void DrawBg(void);
void DrawTexU(void);
void SetBGSpeed(int nSpeed);
int GetBGSpeed(void);

#endif // !_BG_H_
