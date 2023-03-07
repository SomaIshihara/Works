//==========================================
//
//�G�֌W�v���O����[ending.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "file.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//�}�N��
#define CREDIT_NUM	(26)	//�N���W�b�g�\��������
#define SONG_NUM	(6)		//�Ȑ�
#define SONG_TITLE_SHIFT	(70.0f)	//�ȃ^�C�g���̂��炷����
#define CREDIT_TEX_SIZE_WIDTH	(1280)	//�e�N�X�`����
#define CREDIT_TEX_SIZE_HEIGHT	(624)	//�e�N�X�`������
#define CREDIT_TEX_PATT_WIDTH	(2)		//�e�N�X�`���p�^�[������
#define CREDIT_TEX_PATT_HEIGHT	(13)	//�e�N�X�`���p�^�[����
#define CREDIT_NEXTDISPTIME		(120)	//���̕������\������鎞��
#define CREDIT_SPEED			(1.0f)	//�X�s�[�h

//�e�N�X�`���̃p�X
#define TITLE_PATH		"data\\TEXTURE\\NWR_Rogo_New_01.png"
#define CREDIT_MAIN		"data\\TEXTURE\\Credit.png"
#define CREDIT_HARUNA	"data\\TEXTURE\\Credit_Haruna.png"

//�N���W�b�g�\����
typedef struct
{
	int nTexU;	//U���W
	int nTexV;	//V���W
	D3DXVECTOR3 pos;	//�|���S�����W
	int nDispTime;	//����
	bool bUse;	//�\�����邩
} Ending;

//�O���[�o���ϐ�
Ending g_aEnding[CREDIT_NUM];					//�\����
Ending g_EndingHaruna;							//�\���́i�B���\�j
Ending g_EndingTitle;							//�\���́i�^�C�g���j
LPDIRECT3DTEXTURE9 g_pTextureEnding = {};		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffEnding;		//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureHaruna = {};		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffHaruna;		//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitle = {};		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffEndTitle;		//���_�o�b�t�@�|�C���^
int g_nDispCredit;	//�\����
bool g_bDispHaruna;	//�z�؂����\��
int g_nDispTime;	//����

//========================
//�G����������
//========================
void InitEnding(void)
{
	int aCreditWidth[CREDIT_NUM] = { 
		0,1,0,1,0,
		1,0,0,1,1,
		1,0,1,0,1,
		1,0,0,0,0,
		0,1,1,1,1,0 };
	int aCreditHeight[CREDIT_NUM] = { 
		0,12,1,12,2,
		12,3,7,2,3,
		4,8,5,9,0,
		1,4,10,5,11,
		6,8,9,10,11,12 };
	int aCreditTime[CREDIT_NUM] = {
		360,120,180,120,180,
		120,180,120,60,60,
		60,120,60,120,60,
		60,180,120,180,120,
		180,120,120,120,120,240 };
	int aSongTitleNum[SONG_NUM] = { 8,9,10,12,14,15 };
	int nCntEnding;			//�G�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�^�C�g����
	D3DXCreateTextureFromFile(pDevice,
		TITLE_PATH,
		&g_pTextureTitle);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffEndTitle,
		NULL);

	//�e�N�X�`�����W�E�ʒu�ݒ�
	g_EndingTitle.nTexU = 0;
	g_EndingTitle.nTexV = 0;
	g_EndingTitle.pos = D3DXVECTOR3(640.0f, 815.0f, 0.0f);
	g_EndingTitle.bUse = false;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffEndTitle->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = g_EndingTitle.pos + D3DXVECTOR3(-205.0f, -95.0f, 0.0f);
	pVtx[1].pos = g_EndingTitle.pos + D3DXVECTOR3(205.0f, -95.0f, 0.0f);
	pVtx[2].pos = g_EndingTitle.pos + D3DXVECTOR3(-205.0f, 95.0f, 0.0f);
	pVtx[3].pos = g_EndingTitle.pos + D3DXVECTOR3(205.0f, 95.0f, 0.0f);

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

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffEndTitle->Unlock();


	//�N���W�b�g��
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		CREDIT_MAIN,
		&g_pTextureEnding);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * CREDIT_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffEnding,
		NULL);

	//�e�N�X�`�����W�E�ʒu�ݒ�
	for (nCntEnding = 0; nCntEnding < CREDIT_NUM; nCntEnding++)
	{
		g_aEnding[nCntEnding].nTexU = aCreditWidth[nCntEnding];
		g_aEnding[nCntEnding].nTexV = aCreditHeight[nCntEnding];
		g_aEnding[nCntEnding].pos = D3DXVECTOR3(640.0f, 744.0f, 0.0f);
		for (int nCount = 0; nCount < SONG_NUM; nCount++)
		{
			if (nCntEnding == aSongTitleNum[nCount])
			{
				g_aEnding[nCntEnding].pos.x += SONG_TITLE_SHIFT;
			}
		}

		g_aEnding[nCntEnding].nDispTime = aCreditTime[nCntEnding];
		g_aEnding[nCntEnding].bUse = false;
	}

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffEnding->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntEnding = 0; nCntEnding < CREDIT_NUM; nCntEnding++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(-320.0f, -24.0f, 0.0f);
		pVtx[1].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(320.0f, -24.0f, 0.0f);
		pVtx[2].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(-320.0f, 24.0f, 0.0f);
		pVtx[3].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(320.0f, 24.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(((float)g_aEnding[nCntEnding].nTexU) / CREDIT_TEX_PATT_WIDTH,
			((float)g_aEnding[nCntEnding].nTexV) / CREDIT_TEX_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2(((float)g_aEnding[nCntEnding].nTexU + 1) / CREDIT_TEX_PATT_WIDTH,
			((float)g_aEnding[nCntEnding].nTexV) / CREDIT_TEX_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2(((float)g_aEnding[nCntEnding].nTexU) / CREDIT_TEX_PATT_WIDTH,
			((float)g_aEnding[nCntEnding].nTexV + 1) / CREDIT_TEX_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2(((float)g_aEnding[nCntEnding].nTexU + 1) / CREDIT_TEX_PATT_WIDTH,
			((float)g_aEnding[nCntEnding].nTexV + 1) / CREDIT_TEX_PATT_HEIGHT);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffEnding->Unlock();


	//�B���\��
	if (GetSkip() == true)
	{
		D3DXCreateTextureFromFile(pDevice,
			CREDIT_HARUNA,
			&g_pTextureHaruna);

		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxbuffHaruna,
			NULL);

		g_EndingHaruna.nTexU = 0;
		g_EndingHaruna.nTexV = 0;
		g_EndingHaruna.pos = D3DXVECTOR3(640.0f, 744.0f, 0.0f);
		g_EndingHaruna.bUse = false;


		//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
		g_pVtxbuffHaruna->Lock(0, 0, (void **)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = g_EndingHaruna.pos + D3DXVECTOR3(-320.0f, -24.0f, 0.0f);
		pVtx[1].pos = g_EndingHaruna.pos + D3DXVECTOR3(320.0f, -24.0f, 0.0f);
		pVtx[2].pos = g_EndingHaruna.pos + D3DXVECTOR3(-320.0f, 24.0f, 0.0f);
		pVtx[3].pos = g_EndingHaruna.pos + D3DXVECTOR3(320.0f, 24.0f, 0.0f);

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

		//���_�o�b�t�@���A�����b�N
		g_pVtxbuffHaruna->Unlock();
	}

	//�ϐ�������
	g_nDispCredit = 0;
	g_bDispHaruna = false;
	g_nDispTime = 60;
}

//========================
//�G�I������
//========================
void UninitEnding(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}
	if (g_pTextureEnding != NULL)
	{
		g_pTextureEnding->Release();
		g_pTextureEnding = NULL;
	}
	if (g_pTextureHaruna != NULL)
	{
		g_pTextureHaruna->Release();
		g_pTextureHaruna = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffEndTitle != NULL)
	{
		g_pVtxbuffEndTitle->Release();
		g_pVtxbuffEndTitle = NULL;
	}
	if (g_pVtxbuffEnding != NULL)
	{
		g_pVtxbuffEnding->Release();
		g_pVtxbuffEnding = NULL;
	}

	if (g_pVtxbuffHaruna != NULL)
	{
		g_pVtxbuffHaruna->Release();
		g_pVtxbuffHaruna = NULL;
	}
}

//========================
//�G�X�V����
//========================
void UpdateEnding(void)
{
	int nCntEnding;		//�J�E���^
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^


	//�\���ؑ�
	g_nDispTime -= 1;
	if (g_nDispTime < 0)
	{
		if (g_nDispCredit == 0)
		{
			g_EndingTitle.bUse = true;
			g_nDispCredit++;
			g_nDispTime = g_aEnding[0].nDispTime;
		}
		else if (g_nDispCredit >= 1 && g_nDispCredit <= CREDIT_NUM)
		{
			if (!g_bDispHaruna && g_nDispCredit == CREDIT_NUM - 1 && GetSkip() == true)
			{
				g_EndingHaruna.bUse = true;
				g_bDispHaruna = true;
				g_nDispTime = g_aEnding[g_nDispCredit].nDispTime;
			}
			else
			{
				g_aEnding[g_nDispCredit - 1].bUse = true;
				if (GetSkip() == true && g_nDispCredit == CREDIT_NUM - 1 && !g_bDispHaruna)
				{
					g_nDispTime = 120;
				}
				else
				{
					g_nDispTime = g_aEnding[g_nDispCredit].nDispTime;
					
					if (g_nDispCredit == CREDIT_NUM)
					{
						g_nDispTime = 768;
					}

					g_nDispCredit++;
				}
			}
		}
		else if (g_nDispCredit > CREDIT_NUM && GetFade() == FADE_NONE)
		{
			SetFade(MODE_TITLE, GAMERESULT_MAX);
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_TITLE, GAMERESULT_MAX);
	}

	//�^�C�g����
	//���_�o�b�t�@���b�N
	g_pVtxbuffEndTitle->Lock(0, 0, (void **)&pVtx, 0);

	if (g_EndingTitle.bUse)
	{
		//�ړ�
		g_EndingTitle.pos.y -= CREDIT_SPEED;

		//�ړ�
		pVtx[0].pos = g_EndingTitle.pos + D3DXVECTOR3(-205.0f, -95.0f, 0.0f);
		pVtx[1].pos = g_EndingTitle.pos + D3DXVECTOR3(205.0f, -95.0f, 0.0f);
		pVtx[2].pos = g_EndingTitle.pos + D3DXVECTOR3(-205.0f, 95.0f, 0.0f);
		pVtx[3].pos = g_EndingTitle.pos + D3DXVECTOR3(205.0f, 95.0f, 0.0f);

		//��ʒ[�ɗ����������i�T�C���ړ��p�j
		if (g_EndingTitle.pos.y <= -CREDIT_TEX_SIZE_HEIGHT / CREDIT_TEX_PATT_HEIGHT)
		{
			g_EndingTitle.bUse = false;
		}
	}

	g_pVtxbuffEndTitle->Unlock();


	//�N���W�b�g��
	//���_�o�b�t�@���b�N
	g_pVtxbuffEnding->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntEnding = 0; nCntEnding < CREDIT_NUM; nCntEnding++, pVtx += 4)
	{
		if (g_aEnding[nCntEnding].bUse)
		{
			//�ړ�
			g_aEnding[nCntEnding].pos.y -= CREDIT_SPEED;

			//�ړ�
			pVtx[0].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(-320.0f, -24.0f, 0.0f);
			pVtx[1].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(320.0f, -24.0f, 0.0f);
			pVtx[2].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(-320.0f, 24.0f, 0.0f);
			pVtx[3].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(320.0f, 24.0f, 0.0f);

			//��ʒ[�ɗ����������
			if (g_aEnding[nCntEnding].pos.y <= -CREDIT_TEX_SIZE_HEIGHT / CREDIT_TEX_PATT_HEIGHT)
			{
				g_aEnding[nCntEnding].bUse = false;
			}
		}
	}

	g_pVtxbuffEnding->Unlock();


	//�B���\��
	if (GetSkip() == true)
	{
		//���_�o�b�t�@���b�N
		g_pVtxbuffHaruna->Lock(0, 0, (void **)&pVtx, 0);

		if (g_EndingHaruna.bUse)
		{
			//�ړ�
			g_EndingHaruna.pos.y -= CREDIT_SPEED;

			//�ړ�
			pVtx[0].pos = g_EndingHaruna.pos + D3DXVECTOR3(-320.0f, -24.0f, 0.0f);
			pVtx[1].pos = g_EndingHaruna.pos + D3DXVECTOR3(320.0f, -24.0f, 0.0f);
			pVtx[2].pos = g_EndingHaruna.pos + D3DXVECTOR3(-320.0f, 24.0f, 0.0f);
			pVtx[3].pos = g_EndingHaruna.pos + D3DXVECTOR3(320.0f, 24.0f, 0.0f);

			//��ʒ[�ɗ����������i�T�C���ړ��p�j
			if (g_EndingHaruna.pos.y <= -CREDIT_TEX_SIZE_HEIGHT / CREDIT_TEX_PATT_HEIGHT)
			{
				g_EndingHaruna.bUse = false;
			}
		}

		g_pVtxbuffHaruna->Unlock();
	}
}

//========================
//�G�`�揈��
//========================
void DrawEnding(void)
{
	int nCntEnding;			//�G�e�N�X�`���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�^�C�g����
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffEndTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	if (g_EndingTitle.bUse)
	{
		pDevice->SetTexture(0, g_pTextureTitle);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}


	//�N���W�b�g��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffEnding, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	for (nCntEnding = 0; nCntEnding < CREDIT_NUM; nCntEnding++)
	{
		if (g_aEnding[nCntEnding].bUse)
		{
			pDevice->SetTexture(0, g_pTextureEnding);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnding * 4, 2);
		}
	}


	//�B���\��
	if (GetSkip() == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxbuffHaruna, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���ݒ�
		if (g_EndingHaruna.bUse)
		{
			pDevice->SetTexture(0, g_pTextureHaruna);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}