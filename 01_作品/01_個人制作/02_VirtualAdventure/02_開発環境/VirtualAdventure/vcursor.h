//==========================================
//
//���z�J�[�\���v���O�����̃w�b�_[vcursor.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _VCURSOR_H_
#define _VCURSOR_H_

#include "main.h"

//�}�N��
#define VCURSOR_WIDTH		(21)		//��
#define VCURSOR_HEIGHT		(28)		//����

//�v���g�^�C�v�錾
void InitVCursor(void);
void UninitVCursor(void);
void UpdateVCursor(void);
void DrawVCursor(void);
void SetDispVCursor(bool bDisp);
bool GetDispVCursor(void);
D3DXVECTOR3 *GetpCursorPos(void);

#endif // !_VCURSOR_H_
