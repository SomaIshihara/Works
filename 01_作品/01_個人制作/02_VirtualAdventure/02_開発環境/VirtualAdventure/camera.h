//==========================================
//
//�}�b�v�v���O�����̃w�b�_[camera.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "player.h"

//�}�N��
#define CAMERA_MOVEX		(320)	//�J�����ړ��̍Œ�l

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
D3DXVECTOR3 GetCameraPos(void);

#endif // !_CAMERA_H_
