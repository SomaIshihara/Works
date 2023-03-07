//==========================================
//
//���U���g�֌W�v���O�����̃w�b�_[result.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//�Q�[������
typedef enum
{
	RESULT_CLEAR = 0,
	RESULT_OVER,
	RESULT_MAX
} RESULT;

//�v���g�^�C�v�錾
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(RESULT res);
RESULT GetResult(void);

#endif // !_RESULT_H_
