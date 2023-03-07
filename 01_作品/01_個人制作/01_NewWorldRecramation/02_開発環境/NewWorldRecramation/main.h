//==========================================
//
//�Q�[���S�ʂ��Ǘ�����v���O�����̃w�b�_[main.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
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

//�}�N����`
#define SCREEN_WIDTH		(1280)		//�N���C�A���g�̈�̕�
#define SCREEN_HEIGHT		(720)		//�N���C�A���g�̈�̍���
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//���_���
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ϊ��W���i1.0f�ŌŒ�j
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;

//�\���|���S��
typedef struct
{
	int nWidth;						//��
	int nHeight;					//����
	D3DXVECTOR3 pos;				//���S���W
	LPDIRECT3DTEXTURE9 tex = NULL;	//�e�N�X�`���|�C���^
	D3DXCOLOR col;					//�e�N�X�`���J���[
	bool bDisp;						//�\�����邩
} PolygonData;

//��ʃ��[�h�̎��
typedef enum
{
	MODE_TITLE = 0,		//�^�C�g��
	MODE_SELSTAGE,		//�X�e�[�W�I��
	MODE_GAME,			//�Q�[��
	MODE_RESULT,		//���U���g
	MODE_RANK,			//�����L���O
	MODE_ENDING,		//�G���h���[��
	MODE_LOGO,			//���S�\��
	MODE_MAX,
} MODE;

//�Q�[������
typedef enum
{
	GAMERESULT_CLEAR = 0,		//�N���A
	GAMERESULT_OVER,			//�I�[�o�[
	GAMERESULT_MAX
} GAMERESULT;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode, GAMERESULT result);
MODE GetMode(void);
void DrawFPS(void);

#endif // !_MAIN_H_
