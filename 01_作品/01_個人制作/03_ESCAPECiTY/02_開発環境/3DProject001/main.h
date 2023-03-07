//==========================================
//
//�Q�[���S�ʂ��Ǘ�����v���O�����̃w�b�_[main.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <XInput.h>
#include <string.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	//�r���h���̌x���Ώ�
#include "dinput.h"
#include "xaudio2.h"

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//��ʃ��[�h
typedef enum
{
	MODE_TITLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
} MODE;

//�}�N����`
#define CLASS_NAME			"WindowClass"
#define SCREEN_WIDTH		(1280)		//�N���C�A���g�̈�̕�
#define SCREEN_HEIGHT		(720)		//�N���C�A���g�̈�̍���
#define MAX_FPS				(60)		//�ő�t���[�����[�g
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//2D
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//3D
#define FIX_ROT(x)			((float)fmod(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//�p�x��-PI~PI�ɏC��
#define TASUKIGAKE(ax,az,bx,bz)	((az * bx) - (ax * bz))
#define PLAYER_POS			D3DXVECTOR3(0.0f, 0.0f, -960.0f)
#define OBJ_RED_ALPHA		(0.5f)	//�Ԃ���̕s�����x
#define CHAR_TEX_WIDTH		(256)	//�����e�N�X�`���̕�
#define CHAR_TEX_HEIGHT		(320)	//�����e�N�X�`���̍���
#define CHAR_PATT_WIDTH		(8)		//�����e�N�X�`���̃p�^�[����
#define CHAR_PATT_HEIGHT	(5)		//�����e�N�X�`���̃p�^�[������
#define NUMDATA(x)			(x)		//�����\���Ɏg�p�B�P�ɐ�������ꂽ����
#define CHARDATA(x)			(x - 0x37)	//�����\���Ɏg�p�B��������̂���l�����������ɕϊ�����
#define CHAR_SPACE			(36)	//�X�y�[�X
#define CHAR_COLON			(37)	//�R����

//���_���[2D]
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ϊ��W���i1.0f�ŌŒ�j
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;

//���_���[3D]
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`��
} VERTEX_3D;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void SetShowCursor(bool bDisp);
void SetMode(MODE mode);
MODE GetMode(void);

#endif // !_MAIN_H_
