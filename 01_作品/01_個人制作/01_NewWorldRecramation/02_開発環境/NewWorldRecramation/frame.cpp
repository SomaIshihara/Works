//==========================================
//
//�g�֌W�v���O����[frame.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "sound.h"
#include "input.h"
#include "frame.h"

#define USE_FRAME_POLYGON		(2)								//�g�p����|���S����

//�|���S�����
#define FRAME_GAME_PATH		"data\\TEXTURE\\Game_Side_Base.png"	//�Q�[���g�̃p�X
#define FRAME_GAME_WIDTH	(1280)								//�Q�[���g�̕�
#define FRAME_GAME_HEIGHT	(720)								//�Q�[���g�̍���

#define FRAME_SCORE_PATH	"data\\TEXTURE\\Score_Frame_01.png"	//�X�R�A�g�̃p�X
#define FRAME_SCORE_WIDTH	(352)								//�X�R�A�g�̕�
#define FRAME_SCORE_HEIGHT	(160)								//�X�R�A�g�̍���

//�O���[�o���ϐ�
PolygonData g_FramePolygonData[USE_FRAME_POLYGON];
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffFrame = NULL;					//���_�o�b�t�@�|�C���^

//========================
//����������
//========================
void InitFrame(void)
{
	int nCntPolyData;			//�|���S���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�|���S���f�[�^�i�[
	//�Q�[���g
	g_FramePolygonData[0].nWidth = FRAME_GAME_WIDTH;
	g_FramePolygonData[0].nHeight = FRAME_GAME_HEIGHT;
	g_FramePolygonData[0].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		FRAME_GAME_PATH,
		&g_FramePolygonData[0].tex);
	g_FramePolygonData[0].bDisp = true;

	//�X�R�A�g
	g_FramePolygonData[1].nWidth = FRAME_SCORE_WIDTH;
	g_FramePolygonData[1].nHeight = FRAME_SCORE_HEIGHT;
	g_FramePolygonData[1].pos = D3DXVECTOR3(1080.0f, 120.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		FRAME_SCORE_PATH,
		&g_FramePolygonData[1].tex);
	g_FramePolygonData[1].bDisp = true;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * USE_FRAME_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffFrame,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffFrame->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntPolyData = 0; nCntPolyData < USE_FRAME_POLYGON; nCntPolyData++,pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_FramePolygonData[nCntPolyData].pos.x - (g_FramePolygonData[nCntPolyData].nWidth / 2);
		pVtx[0].pos.y = g_FramePolygonData[nCntPolyData].pos.y - (g_FramePolygonData[nCntPolyData].nHeight / 2);
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_FramePolygonData[nCntPolyData].pos.x + (g_FramePolygonData[nCntPolyData].nWidth / 2);
		pVtx[1].pos.y = g_FramePolygonData[nCntPolyData].pos.y - (g_FramePolygonData[nCntPolyData].nHeight / 2);
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_FramePolygonData[nCntPolyData].pos.x - (g_FramePolygonData[nCntPolyData].nWidth / 2);
		pVtx[2].pos.y = g_FramePolygonData[nCntPolyData].pos.y + (g_FramePolygonData[nCntPolyData].nHeight / 2);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_FramePolygonData[nCntPolyData].pos.x + (g_FramePolygonData[nCntPolyData].nWidth / 2);
		pVtx[3].pos.y = g_FramePolygonData[nCntPolyData].pos.y + (g_FramePolygonData[nCntPolyData].nHeight / 2);
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
	g_pVtxbuffFrame->Unlock();
}

//========================
//�I������
//========================
void UninitFrame(void)
{
	int nCntUninitFrame;	//�j���p�J�E���^

	StopSound();
	for (nCntUninitFrame = 0; nCntUninitFrame < USE_FRAME_POLYGON; nCntUninitFrame++)
	{
		if (g_FramePolygonData[nCntUninitFrame].tex != NULL)
		{
			g_FramePolygonData[nCntUninitFrame].tex->Release();
			g_FramePolygonData[nCntUninitFrame].tex = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffFrame != NULL)
	{
		g_pVtxbuffFrame->Release();
		g_pVtxbuffFrame = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateFrame(void)
{
	//�����Ȃ�
}

//========================
//�`�揈��
//========================
void DrawFrame(void)
{
	int nCntFrame;			//�e�N�X�`���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffFrame, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFrame = 0; nCntFrame < USE_FRAME_POLYGON; nCntFrame++)
	{
		if (g_FramePolygonData[nCntFrame].bDisp)
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_FramePolygonData[nCntFrame].tex);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFrame * 4, 2);
		}
	}
}