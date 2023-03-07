//==========================================
//
//���̓v���O����[input.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX	(256)	//�L�[�̍ő吔
#define REPEATE_TIME	(150)	//���s�[�g�̊Ԋu

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];				//�v���X���
BYTE g_akeyStateTrigger[NUM_KEY_MAX];		//�g���K�[���
BYTE g_akeyStateRelease[NUM_KEY_MAX];		//�����[�X���
BYTE g_akeyStateRepeate[NUM_KEY_MAX];		//���s�[�g���
DWORD g_aCurrentTime[NUM_KEY_MAX];			//���݂̎��ԁi���s�[�g�g�p�j
DWORD g_aExecLastTime[NUM_KEY_MAX];			//�Ō��true��Ԃ������ԁi���s�[�g�g�p)

//========================
//���͏���������
//========================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	int nCntKey;		//�J�E���^

	//DireceInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�擾
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	//���ԏ�����
	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aCurrentTime[nCntKey] = 0;
		g_aExecLastTime[nCntKey] = timeGetTime() - REPEATE_TIME;
	}

	return S_OK;
}

//========================
//���͏I������
//========================
void UninitKeyboard(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//========================
//���͍X�V����
//========================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//���̓f�o�C�X����f�o�C�X���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++) 
		{
			//�g���K�[�ƃ����[�X
			g_akeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
 			g_akeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];

			//���s�[�g
			g_aCurrentTime[nCntKey] = timeGetTime();
			if (aKeyState[nCntKey] && (g_aCurrentTime[nCntKey] - g_aExecLastTime[nCntKey]) > REPEATE_TIME)
			{
				g_aExecLastTime[nCntKey] = g_aCurrentTime[nCntKey];
				g_akeyStateRepeate[nCntKey] = aKeyState[nCntKey];
			}
			else
			{
				g_akeyStateRepeate[nCntKey] = 0;
			}
			//�v���X
			g_aKeyState[nCntKey] = aKeyState[nCntKey];	//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}

//========================
//�v���X����Ԃ�����
//========================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;	//?����������邱�ƂɂȂ��Ă�݂�����
}

//========================
//�g���K�[����Ԃ�����
//========================
bool GetKeyboardTrigger(int nKey)
{
	return (g_akeyStateTrigger[nKey] & 0x80) ? true : false;
}

//========================
//�����[�X����Ԃ�����
//========================
bool GetKeyboardRelease(int nKey)
{
	return (g_akeyStateRelease[nKey] & 0x80) ? true : false;
}

//========================
//���s�[�g����Ԃ�����
//========================
bool GetKeyboardRepeate(int nKey)
{
 	return (g_akeyStateRepeate[nKey] & 0x80) ? true : false;
}