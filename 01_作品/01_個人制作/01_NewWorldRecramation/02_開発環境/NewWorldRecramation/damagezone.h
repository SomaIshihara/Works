//==========================================
//
//�_���[�W�]�[���v���O�����̃w�b�_[damagezone.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _DZ_H_
#define _DZ_H_

#include "main.h"
#include "file.h"

//�}�N��
#define DZ_COL_DEFAULT_LIGHT		D3DXCOLOR(1.0f,0.945f,0.0f,1.0f)		//�_���[�W�]�[���̐F�i���F�j
#define DZ_COL_DEFAULT_DARK			D3DXCOLOR(0.447f,0.094f,0.631f,1.0f)	//�_���[�W�]�[���̐F�i���j
#define DZ_COL_DEFAULT_RED			D3DXCOLOR(1.0f,0.0f,0.0f,0.42f)			//�_���[�W�]�[���̐F�i�ԁj

//�v���g�^�C�v�錾
void InitDamageZone(void);
void UninitDamageZone(void);
void UpdateDamageZone(void);
void DrawDamageZone(void);
void SetDamageZone(MapData setDZData, D3DXCOLOR col);

#endif // !_BG_H_
