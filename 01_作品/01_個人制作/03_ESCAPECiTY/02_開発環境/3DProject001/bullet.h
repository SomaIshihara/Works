//==========================================
//
//�e�\���v���O�����̃w�b�_[bullet.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, float fSpeed, float fRot, D3DXCOLOR col);

#endif // !_BG_H_
