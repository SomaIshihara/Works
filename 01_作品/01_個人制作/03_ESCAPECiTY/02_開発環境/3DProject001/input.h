//==========================================
//
//���̓v���O�����̃w�b�_[input.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//�}�N��
#define STICK_MAX	(32767)		//�X�e�B�b�N�ő�l
#define MOUSE_CLICK_LEFT	(0)	//�}�E�X���N���b�N
#define MOUSE_CLICK_RIGHT	(1)	//�}�E�X�E�N���b�N

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);

//�L�[�{�[�h
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
bool GetKeyboardRepeate(int nKey);

//�Q�[���p�b�h
bool GetGamepadPress(int nButton);
bool GetGamepadTrigger(int nButton);
bool GetGamepadRelease(int nButton);
bool GetGamepadRepeate(int nButton);
SHORT GetLStickX(void);
SHORT GetLStickY(void);
SHORT GetRStickX(void);
SHORT GetRStickY(void);
bool GetUseGamepad(void);

//�}�E�X
bool GetMouseClickPress(int nButton);
bool GetMouseClickTrigger(int nButton);
bool GetMouseClickRepeate(int nButton);
D3DXVECTOR3 GetMousePos(void);
D3DXVECTOR3 GetMouseMove(void);

#endif // !_INPUT_H_
