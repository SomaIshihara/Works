//==========================================
//
//���U���g�֌W�v���O����[result.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "result.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "game.h"

//�}�N��
#define RETURN_TIME		(5000)	//�^�C�g����ʂɖ߂�܂ł̎���
#define USE_RESULT_POLYGON	(4)	//���U���g��ʂŎg���|���S����

#define RESULT_BG0_PATH			"data\\TEXTURE\\Gametitle_BG.png"
#define RESULT_BG0_WIDTH		(1280)
#define RESULT_BG0_HEIGHT		(720)

#define RESULT_BG1_PATH			"data\\TEXTURE\\Result_BG_Failed_01.png"
#define RESULT_BG1_WIDTH		(1280)
#define RESULT_BG1_HEIGHT		(720)

#define RESULT_CLEAR_PATH		"data\\TEXTURE\\Game_Clear_01.png"
#define RESULT_CLEAR_WIDTH		(776)
#define RESULT_CLEAR_HEIGHT		(96)

#define RESULT_OVER_PATH		"data\\TEXTURE\\Game_Failed_01.png"
#define RESULT_OVER_WIDTH		(816)
#define RESULT_OVER_HEIGHT		(96)

//�O���[�o���ϐ�
PolygonData g_ResultPolygonData[USE_RESULT_POLYGON] = {};	//�|���S�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffResult = NULL;			//���_�o�b�t�@�|�C���^
DWORD g_dwCurrentTime, g_dwStartTime;						//���U���g��ʊJ�n����̎��Ԃƌ��݂̎���
GAMERESULT g_gameresult;									//�Q�[������

//========================
//����������
//========================
void InitResult(GAMERESULT result)
{
	int nCntResultPolyData;		//�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�N���A�w�i
	g_ResultPolygonData[0].nWidth = RESULT_BG0_WIDTH;
	g_ResultPolygonData[0].nHeight = RESULT_BG0_HEIGHT;
	g_ResultPolygonData[0].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		RESULT_BG0_PATH,
		&g_ResultPolygonData[0].tex);

	//�I�[�o�[�w�i
	g_ResultPolygonData[1].nWidth = RESULT_BG1_WIDTH;
	g_ResultPolygonData[1].nHeight = RESULT_BG1_HEIGHT;
	g_ResultPolygonData[1].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		RESULT_BG1_PATH,
		&g_ResultPolygonData[1].tex);

	//�N���A����
	g_ResultPolygonData[2].nWidth = RESULT_CLEAR_WIDTH;
	g_ResultPolygonData[2].nHeight = RESULT_CLEAR_HEIGHT;
	g_ResultPolygonData[2].pos = D3DXVECTOR3(640.0f, 150.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		RESULT_CLEAR_PATH,
		&g_ResultPolygonData[2].tex);

	//�I�[�o�[����
	g_ResultPolygonData[3].nWidth = RESULT_OVER_WIDTH;
	g_ResultPolygonData[3].nHeight = RESULT_OVER_HEIGHT;
	g_ResultPolygonData[3].pos = D3DXVECTOR3(640.0f, 150.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		RESULT_OVER_PATH,
		&g_ResultPolygonData[3].tex);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * USE_RESULT_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffResult,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffResult->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntResultPolyData = 0; nCntResultPolyData < USE_RESULT_POLYGON; nCntResultPolyData++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_ResultPolygonData[nCntResultPolyData].pos.x - (g_ResultPolygonData[nCntResultPolyData].nWidth / 2);
		pVtx[0].pos.y = g_ResultPolygonData[nCntResultPolyData].pos.y - (g_ResultPolygonData[nCntResultPolyData].nHeight / 2);
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_ResultPolygonData[nCntResultPolyData].pos.x + (g_ResultPolygonData[nCntResultPolyData].nWidth / 2);
		pVtx[1].pos.y = g_ResultPolygonData[nCntResultPolyData].pos.y - (g_ResultPolygonData[nCntResultPolyData].nHeight / 2);
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_ResultPolygonData[nCntResultPolyData].pos.x - (g_ResultPolygonData[nCntResultPolyData].nWidth / 2);
		pVtx[2].pos.y = g_ResultPolygonData[nCntResultPolyData].pos.y + (g_ResultPolygonData[nCntResultPolyData].nHeight / 2);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_ResultPolygonData[nCntResultPolyData].pos.x + (g_ResultPolygonData[nCntResultPolyData].nWidth / 2);
		pVtx[3].pos.y = g_ResultPolygonData[nCntResultPolyData].pos.y + (g_ResultPolygonData[nCntResultPolyData].nHeight / 2);
		pVtx[3].pos.z = 0.0f;

		//���W�ϊ��p�W���ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffResult->Unlock();

	//���Ԑݒ�
	g_dwCurrentTime = 0;
	g_dwStartTime = timeGetTime();

	//���ʐݒ�
	g_gameresult = result;

	//���ʂɂ���ĉ��y��ύX
	switch (g_gameresult)
	{
	case GAMERESULT_CLEAR:
		PlaySound(SOUND_LABEL_SE_CLEAR);
		break;
	case GAMERESULT_OVER:
		PlaySound(SOUND_LABEL_SE_OVER);
		break;
	}

	//�X�R�A�̒��_�o�b�t�@�ލĐ���
	InitScore(D3DXVECTOR3(304.0f, 360.0f, 0.0f), 1.0f);
}

//========================
//�I������
//========================
void UninitResult(void)
{
	int nCntUninitResult;	//�e�N�X�`���j���J�E���^

	//����~
	StopSound();

	//�X�R�A�I��
	UninitScore();

	for (nCntUninitResult = 0; nCntUninitResult < USE_RESULT_POLYGON; nCntUninitResult++)
	{
		if (g_ResultPolygonData[nCntUninitResult].tex != NULL)
		{
			g_ResultPolygonData[nCntUninitResult].tex->Release();
			g_ResultPolygonData[nCntUninitResult].tex = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffResult != NULL)
	{
		g_pVtxbuffResult->Release();
		g_pVtxbuffResult = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateResult(void)
{
	g_dwCurrentTime = timeGetTime();

	if (g_dwCurrentTime - g_dwStartTime >= RETURN_TIME || GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (GetFade() == FADE_NONE)
		{
			if (GetStage() == STAGE_TIMEATTACK)
			{
				SetFade(MODE_RANK, GAMERESULT_MAX);
			}
			else
			{
				SetFade(MODE_SELSTAGE, GAMERESULT_MAX);
			}
		}
	}

	//�X�R�A�X�V
	UpdateScore();
}

//========================
//�`�揈��
//========================
void DrawResult(void)
{
	int nCntTexPattern;		//�J�E���^

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	for (nCntTexPattern = g_gameresult; nCntTexPattern < USE_RESULT_POLYGON; nCntTexPattern += 2)
	{
		pDevice->SetTexture(0, g_ResultPolygonData[nCntTexPattern].tex);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexPattern * 4, 2);
	}

	//�^�C���A�^�b�N�̂Ƃ�or�X�g�[�����[�h�ŃN���A�����Ƃ��̓X�R�A�\��
	if (GetStage() == STAGE_TIMEATTACK || g_gameresult == GAMERESULT_CLEAR)
	{
		//�X�R�A�`��
		DrawScore();
	}
}