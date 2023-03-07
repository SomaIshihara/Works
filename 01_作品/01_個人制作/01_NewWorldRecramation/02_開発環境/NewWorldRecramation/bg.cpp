//==========================================
//
//�w�i�\���v���O����[bg.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "bg.h"
#include "player.h"

//�}�N��
#define NUM_BG		(5)		//�w�i�̐�
#define TEX_USPEED	(0.25f)	//�e�N�X�`���X�s�[�h
#define TEX_WIDTH	(1.0f)	//�w�i�̕��̎g�����W
#define TEX_HEIGHT	(0.5f)	//�w�i�̍������g�����W
#define TEXU_SLIDE	(0.12f)	//U���W���炷���

//�X�e�[�W�e�N�X�`���p�X�i2TA��1�`4�̂ǂꂩ�j
#define BG_TEXTURE_STG1_PATH	"data\\TEXTURE\\BG_GrassLands_01.png"	//�X�e�[�W1�̃e�N�X�`���p�X
#define BG_TEXTURE_STG2_PATH	"data\\TEXTURE\\BG_GrassLands_02.png"	//�X�e�[�W2�̃e�N�X�`���p�X
#define BG_TEXTURE_STG3_PATH	"data\\TEXTURE\\BG_City_01.png"			//�X�e�[�W3�̃e�N�X�`���p�X
#define BG_TEXTURE_STG4_PATH	"data\\TEXTURE\\BG_City_02.png"			//�X�e�[�W4�̃e�N�X�`���p�X
#define BG_TEXTURE_STGLAST_PATH	"data\\TEXTURE\\BG_Desurt_01.png"		//�X�e�[�WLAST�̃e�N�X�`���p�X

LPDIRECT3DTEXTURE9 g_apTextureBg[NUM_BG] = {};	//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBg = NULL;	//���_�o�b�t�@�|�C���^
int g_nBGSpeed;							//BG�̗���鑬�x
float g_aTexU;					//�e�N�X�`�����W�̊J�n�ʒu(U
float g_aTexV;					//�e�N�X�`�����W�̊J�n�ʒu(V
float g_fTexVSpeed;						//V�l�ړ��̑��x
LPD3DXFONT g_pFontBG = NULL;			//�t�H���g�ւ̃|�C���^

//========================
//�w�i����������
//========================
void InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�w�i�ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		BG_TEXTURE_STG1_PATH,
		&g_apTextureBg[0]);
	D3DXCreateTextureFromFile(pDevice,
		BG_TEXTURE_STG2_PATH,
		&g_apTextureBg[1]);
	D3DXCreateTextureFromFile(pDevice,
		BG_TEXTURE_STG3_PATH,
		&g_apTextureBg[2]);
	D3DXCreateTextureFromFile(pDevice,
		BG_TEXTURE_STG4_PATH,
		&g_apTextureBg[3]);
	D3DXCreateTextureFromFile(pDevice,
		BG_TEXTURE_STGLAST_PATH,
		&g_apTextureBg[4]);

	//�e�N�X�`��UV�l�̏�����
	g_aTexU = 0.0f;
	g_aTexV = 0.0f;

	//�f�o�b�O�\���p�t�H���g����
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFontBG);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBg,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBg->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, (float)SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f);

	//���W�ϊ��p�W���ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aTexU, g_aTexV);
	pVtx[1].tex = D3DXVECTOR2(g_aTexU + TEX_WIDTH, g_aTexV);
	pVtx[2].tex = D3DXVECTOR2(g_aTexU, g_aTexV + TEX_HEIGHT);
	pVtx[3].tex = D3DXVECTOR2(g_aTexU + TEX_WIDTH, g_aTexV + TEX_HEIGHT);

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffBg->Unlock();

	//BG���x�������ix1.00�j
	g_nBGSpeed = 100;
}

//========================
//�w�i�I������
//========================
void UninitBg(void)
{
	int nCntTexBG;	//�J�E���^

	//�e�N�X�`���̔j��
	for (nCntTexBG = 0; nCntTexBG < NUM_BG; nCntTexBG++)
	{
		if (g_apTextureBg[nCntTexBG] != NULL)
		{
			g_apTextureBg[nCntTexBG]->Release();
			g_apTextureBg[nCntTexBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffBg != NULL)
	{
		g_pVtxbuffBg->Release();
		g_pVtxbuffBg = NULL;
	}
}

//========================
//�w�i�X�V����
//========================
void UpdateBg(void)
{
	if (GetGameState() != GAMESTATE_END)
	{
		VERTEX_2D *pVtx;					//�ݒ�p�|�C���^
		Player *playerData = GetPlayer();	//�v���C���[���̂���|�C���^	

#if 1
		//�e�N�X�`��U�l�X�V
		g_aTexU = (playerData->pos.x * TEX_USPEED / SCREEN_WIDTH) * TEX_WIDTH - TEXU_SLIDE;
#endif
		//�e�N�X�`��V�l�X�V
		g_aTexV = (float)fmod(g_aTexV + 1.0f - BG_TEX_SPEED * g_nBGSpeed * 0.01f, 1.0f);

		//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
		g_pVtxbuffBg->Lock(0, 0, (void **)&pVtx, 0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aTexU, g_aTexV);
		pVtx[1].tex = D3DXVECTOR2(g_aTexU + TEX_WIDTH, g_aTexV);
		pVtx[2].tex = D3DXVECTOR2(g_aTexU, g_aTexV + TEX_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2(g_aTexU + TEX_WIDTH, g_aTexV + TEX_HEIGHT);

		//���_�o�b�t�@���A�����b�N
		g_pVtxbuffBg->Unlock();
	}
}

//========================
//�w�i�`�揈��
//========================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffBg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	if (GetStage() == STAGE_TIMEATTACK)
	{
		pDevice->SetTexture(0, g_apTextureBg[3]);
	}
	else
	{
		pDevice->SetTexture(0, g_apTextureBg[GetStage() - 1]);
	}
	
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================
//�f�o�b�O�i�ʒu�j
//========================
void DrawTexU(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��(x
	wsprintf(&aStr[0], "\n\n\ntex.u:0.%d",(int)(g_aTexU * 100));

	//�e�L�X�g�`��(x
	g_pFontBG->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================
//BG������鑬�x�ݒ�
//========================
void SetBGSpeed(int nSpeed)
{
	g_nBGSpeed = nSpeed;
}

//========================
//BG������鑬�x�擾
//========================
int GetBGSpeed(void)
{
	return g_nBGSpeed;
}