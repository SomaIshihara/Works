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

//�����ԍ���
typedef enum
{
	ZERO = 0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
	EIGHT, NINE, A, B, C, D, E, F,
	G, H, I, J, K, L, M, N,
	O, P, Q, R, S, T, U, V,
	W, X, Y, Z, ENTER, ABUTTON, COLON, SPACE,
	STRINGNUM_MAX
} STRINGNUM;

//�����Z�b�g�ԍ�
typedef enum
{
	STRSET_POINT = 0,
	STRSET_RESULT,
	STRSET_YOU,
	STRSET_HSCORE,
	STRSET_START,
	STRSET_PRSBUTTON,
	STRSET_TIME,
	STRSET_MAX
} STRSET;

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
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define ACCELERATION_GRAVITY	(9.8f * 4.0f)		//�d�͉����x

//�����e�N�X�`���֌W
#define CHARSET_SIZE_WIDTH		(256)	//�e�N�X�`���T�C�Y��
#define CHARSET_SIZE_HEIGHT		(240)	//�e�N�X�`���T�C�Y����
#define CHARSET_PATT_WIDTH		(8)		//�e�N�X�`���p�^�[����
#define CHARSET_PATT_HEIGHT		(5)		//�e�N�X�`���p�^�[������

//���_���
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ϊ��W���i1.0f�ŌŒ�j
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void DrawFPS(void);
void SetMode(MODE mode);
MODE GetMode(void);

//������Z�b�g
const STRINGNUM c_aTextSet[STRSET_MAX][10] =
{
	{P,O,I,N,T,COLON},
	{R,E,S,U,L,T},
	{Y,O,U,SPACE,SPACE,SPACE,SPACE },
	{H,S,C,O,R,E,SPACE},
	{ENTER,S,T,A,R,T,ABUTTON},
	{P,R,S,ENTER,ABUTTON},
	{T,I,M,E,SPACE}
};

//������Z�b�g�̕�����
const int c_aTextSetNum[STRSET_MAX] = { 6,6,7,7,7,5,5 };

#endif // !_MAIN_H_
