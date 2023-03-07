//==========================================
//
//�f�o�b�O�\���v���O����[debugproc.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "debugproc.h"
#include "input.h"
#include <stdio.h>
#include <stdarg.h>

//�}�N��
#define DEBPRO_MAX_STR	(2048)			//�m�ۂ��镶����

//�O���[�o���ϐ�
LPD3DXFONT g_pFont = NULL;				//�t�H���g�ւ̃|�C���^
char g_aStrPrint[DEBPRO_MAX_STR];		//�\�������o�b�t�@

//========================
//����������
//========================
void InitDebugProc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�f�o�b�O�\���p�t�H���g����
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//�o�b�t�@�N���A
	memset(&g_aStrPrint, 0, sizeof g_aStrPrint);
}

//========================
//�I������
//========================
void UninitDebugProc(void)
{
	//�t�H���g�j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateDebugProc(void)
{
	//��
}

//========================
//�`�揈��
//========================
void DrawDebugProc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	
	//�e�L�X�g�`��
	g_pFont->DrawText(NULL, &g_aStrPrint[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));

	//�o�b�t�@�N���A
	memset(&g_aStrPrint, 0, sizeof g_aStrPrint);
}

//========================
//���͎�荞�ݏ���
//========================
void PrintDebugProc(const char *fmt, ...)
{
	int nCount;		//�J�E���^
	va_list args;	//�ψ����̒��g

	//�o�͊J�n
	va_start(args, fmt);

	for (nCount = 0; *fmt != '\0'; fmt++)
	{
		if (*fmt == '%')
		{
			char aStr[10] = {};
			switch (*(fmt + 1))
			{
			case 'd':
				sprintf(&aStr[0], "%d", va_arg(args, int));
				snprintf(&g_aStrPrint[0], sizeof g_aStrPrint, "%s%s", &g_aStrPrint[0], &aStr[0]);
				fmt++;
				break;
			case 'f':
				sprintf(&aStr[0], "%.2f", va_arg(args, double));
				snprintf(&g_aStrPrint[0], sizeof g_aStrPrint, "%s%s", &g_aStrPrint[0], &aStr[0]);
				fmt++;
				break;
			case 'c':
				strcat(&g_aStrPrint[0], &va_arg(args, char));
				fmt++;
				break;
			case 's':
				strcat(&g_aStrPrint[0], va_arg(args, const char*));
				fmt++;
				break;
			default:
				strcat(&g_aStrPrint[0], "< ERROR >");
				break;
			}
		}
		else
		{
			char cData = *fmt;
			snprintf(&g_aStrPrint[0], sizeof g_aStrPrint, "%s%c", &g_aStrPrint[0], cData);
		}
	}

	va_end(args);
}