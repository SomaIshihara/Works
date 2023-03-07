//==========================================
//
//�i�s�x�\���v���O����[progressbar.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "progressbar.h"
#include "map.h"
#include "item.h"

//�}�N��
#define PROGBAR_USEPOLY			(2)		//�v���O���X�o�[�i�_�j�̎g�p�|���S�����i0:�Œ�/1:�ρj
#define PROGLINE_USEPOLY		(3)		//���C���̎g�p�|���S����

#define PROGBAR_TEX_WIDTH		(40)	//�_�̃T�C�Y�i��
#define PROGBAR_TEX_HEIGHT		(620)	//�_�̃T�C�Y�i����

#define PROGLINE_ANNI_WIDTH		(146)	//�A���j���C���̃e�N�X�`���T�C�Y�i��
#define PROGLINE_ANNI_HEIGHT	(58)	//�A���j���C���̃e�N�X�`���T�C�Y�i����

#define PROGLINE_APPEMIN_WIDTH	(182)	//�{�X�Œ჉�C���̃e�N�X�`���T�C�Y�i��
#define PROGLINE_APPEMIN_HEIGHT	(88)	//�{�X�Œ჉�C���̃e�N�X�`���T�C�Y�i����

#define PROGLINE_APPEMAX_WIDTH	(182)	//�{�X�ō����C���̃e�N�X�`���T�C�Y�i��
#define PROGLINE_APPEMAX_HEIGHT	(58)	//�{�X�ō����C���̃e�N�X�`���T�C�Y�i����

#define PROGNUM_PLACE			(3)		//����
#define PROGNUM_TEX_SIZE_WIDTH	(576)	//�i�s�x�����e�N�X�`���T�C�Y�i��
#define PROGNUM_TEX_SIZE_HEIGHT	(64)	//�i�s�x�����e�N�X�`���T�C�Y�i����
#define PROGNUM_TEX_PAT_WIDTH	(12)	//�i�s�x�����e�N�X�`���p�^�[���i��
#define PROGNUM_TEX_PAT_HEIGHT	(1)		//�i�s�x�����e�N�X�`���p�^�[���i����
#define PROGNUM_TEX_PAT_PARCE	(11)	//�i�s�x�����e�N�X�`���p�^�[���ԍ��i�p�[�Z���g

//�e�N�X�`���p�X
//�_
#define PROGBAR_BASE_PATH		"data\\TEXTURE\\Game_Progress_Bar_01.png"		//�y��
#define PROGBAR_ANNI_PATH		"data\\TEXTURE\\Game_Progress_Bar_02.png"		//�A���j�_
#define PROGBAR_APPEMIN_PATH	"data\\TEXTURE\\Game_Progress_Bar_03.png"		//�{�X�Œ�_
#define PROGBAR_APPEMAX_PATH	"data\\TEXTURE\\Game_Progress_Bar_04.png"		//�{�X�ō��_

//���C��
#define PROGLINE_ANNI_PATH		"data\\TEXTURE\\Game_Progress_Line_01.png"		//�A���j���C��
#define PROGLINE_APPEMIN_PATH	"data\\TEXTURE\\Game_Progress_Line_02.png"		//�{�X�Œ჉�C��
#define PROGLINE_APPEMAX_PATH	"data\\TEXTURE\\Game_Progress_Line_03.png"		//�{�X�ō����C��

//����
#define PROGNUM_ANNI_PATH		"data\\TEXTURE\\Number_Progress_01.png"			//�A���j����
#define PROGNUM_APPEMIN_PATH	"data\\TEXTURE\\Number_Progress_02.png"			//�{�X�Œᐔ��
#define PROGNUM_APPEMAX_PATH	"data\\TEXTURE\\Number_Progress_03.png"			//�{�X�ō�����

//�i�s�x���ށi��
typedef enum
{
	PROGLINE_ANNI = 0,
	PROGLINE_APPEMIN,
	PROGLINE_APPEMAX,
	PROGLINE_MAX
} PROGLINE;

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureProgressBar[PROGLINE_MAX + 1] = {};	//�_�e�N�X�`���|�C���^
LPDIRECT3DTEXTURE9 g_apTextureProgressNum[PROGLINE_MAX] = {};		//�i�s�x�����e�N�X�`���|�C���^
PolygonData g_aProgLinePolyData[PROGLINE_MAX] = {};					//���C���|���S�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffProgressBar;						//�_���_�o�b�t�@�|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffProgressLine;						//���C�����_�o�b�t�@�|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffProgressNum;						//�i�s�x�������_�o�b�t�@�|�C���^
D3DXVECTOR3 g_posPrgBar[PROGBAR_USEPOLY];							//�_�̈ʒu�i[1]�͉ρj
int g_nCurrentTime;													//�o�ߎ���
PROGLINE g_progLine;												//�i�s�x����
float g_fRateofProg;	//�i�s�x����

//========================
//����������
//========================
void InitProgressBar(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntProgress;				//�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	for (nCntProgress = 0; nCntProgress < PROGBAR_USEPOLY; nCntProgress++)
	{
		g_posPrgBar[nCntProgress] = D3DXVECTOR3(216.0f, 50.0f, 0.0f);
	}

	//�_�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		PROGBAR_BASE_PATH,
		&g_apTextureProgressBar[0]);
	D3DXCreateTextureFromFile(pDevice,
		PROGBAR_ANNI_PATH,
		&g_apTextureProgressBar[1]);
	D3DXCreateTextureFromFile(pDevice,
		PROGBAR_APPEMIN_PATH,
		&g_apTextureProgressBar[2]);
	D3DXCreateTextureFromFile(pDevice,
		PROGBAR_APPEMAX_PATH,
		&g_apTextureProgressBar[3]);

	//���C���|���S�����ݒ�
	//�A���j
	g_aProgLinePolyData[0].nWidth = PROGLINE_ANNI_WIDTH;
	g_aProgLinePolyData[0].nHeight = PROGLINE_ANNI_HEIGHT;
	g_aProgLinePolyData[0].pos = D3DXVECTOR3(72.0f, 670.0f - PROGLINE_ANNI_HEIGHT, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		PROGLINE_ANNI_PATH,
		&g_aProgLinePolyData[0].tex);
	g_aProgLinePolyData[0].bDisp = true;
	
	//�{�X�Œ�
	g_aProgLinePolyData[1].nWidth = PROGLINE_APPEMIN_WIDTH;
	g_aProgLinePolyData[1].nHeight = PROGLINE_APPEMIN_HEIGHT;
	g_aProgLinePolyData[1].pos = D3DXVECTOR3(72.0f, 670.0f - PROGBAR_TEX_HEIGHT * PROGLINE_APPEMIN_ROP, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		PROGLINE_APPEMIN_PATH,
		&g_aProgLinePolyData[1].tex);
	g_aProgLinePolyData[1].bDisp = true;
	
	//�{�X�ō�
	g_aProgLinePolyData[2].nWidth = PROGLINE_APPEMAX_WIDTH;
	g_aProgLinePolyData[2].nHeight = PROGLINE_APPEMAX_HEIGHT;
	g_aProgLinePolyData[2].pos = D3DXVECTOR3(72.0f, 670.0f - PROGBAR_TEX_HEIGHT * PROGLINE_APPEMAX_ROP, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		PROGLINE_APPEMAX_PATH,
		&g_aProgLinePolyData[2].tex);
	g_aProgLinePolyData[2].bDisp = true;

	//�i�s�x�����e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		PROGNUM_ANNI_PATH,
		&g_apTextureProgressNum[0]);
	D3DXCreateTextureFromFile(pDevice,
		PROGNUM_APPEMIN_PATH,
		&g_apTextureProgressNum[1]);
	D3DXCreateTextureFromFile(pDevice,
		PROGNUM_APPEMAX_PATH,
		&g_apTextureProgressNum[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PROGBAR_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffProgressBar,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PROGLINE_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffProgressLine,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (PROGNUM_PLACE + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffProgressNum,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//�_���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffProgressBar->Lock(0, 0, (void **)&pVtx, 0);

	//�_�̒��_���ݒ�
	for (nCntProgress = 0; nCntProgress < PROGBAR_USEPOLY; nCntProgress++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = g_posPrgBar[nCntProgress];
		pVtx[1].pos.x = g_posPrgBar[nCntProgress].x + PROGBAR_TEX_WIDTH;
		pVtx[1].pos.y = g_posPrgBar[nCntProgress].y;
		pVtx[2].pos.x = g_posPrgBar[nCntProgress].x;
		pVtx[2].pos.y = g_posPrgBar[nCntProgress].y + PROGBAR_TEX_HEIGHT;
		pVtx[3].pos.x = g_posPrgBar[nCntProgress].x + PROGBAR_TEX_WIDTH;
		pVtx[3].pos.y = g_posPrgBar[nCntProgress].y + PROGBAR_TEX_HEIGHT;

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
	g_pVtxbuffProgressBar->Unlock();

	//���C�����_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffProgressLine->Lock(0, 0, (void **)&pVtx, 0);

	//���C���̒��_���ݒ�
	for (nCntProgress = 0; nCntProgress < PROGLINE_MAX; nCntProgress++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = g_aProgLinePolyData[nCntProgress].pos;
		pVtx[1].pos.x = g_aProgLinePolyData[nCntProgress].pos.x + g_aProgLinePolyData[nCntProgress].nWidth;
		pVtx[1].pos.y = g_aProgLinePolyData[nCntProgress].pos.y;
		pVtx[2].pos.x = g_aProgLinePolyData[nCntProgress].pos.x;
		pVtx[2].pos.y = g_aProgLinePolyData[nCntProgress].pos.y + g_aProgLinePolyData[nCntProgress].nHeight;
		pVtx[3].pos.x = g_aProgLinePolyData[nCntProgress].pos.x + g_aProgLinePolyData[nCntProgress].nWidth;
		pVtx[3].pos.y = g_aProgLinePolyData[nCntProgress].pos.y + g_aProgLinePolyData[nCntProgress].nHeight;

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
	g_pVtxbuffProgressLine->Unlock();


	//�������_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffProgressNum->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntProgress = 0; nCntProgress < PROGNUM_PLACE + 1; nCntProgress++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(14.0f + PROGNUM_TEX_SIZE_WIDTH / PROGNUM_TEX_PAT_WIDTH * nCntProgress,
			50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(14.0f + (PROGNUM_TEX_SIZE_WIDTH / PROGNUM_TEX_PAT_WIDTH + 1) * (nCntProgress + 1),
			50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(14.0f + PROGNUM_TEX_SIZE_WIDTH / PROGNUM_TEX_PAT_WIDTH * nCntProgress,
			50.0f + PROGNUM_TEX_SIZE_HEIGHT / PROGNUM_TEX_PAT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(14.0f + (PROGNUM_TEX_SIZE_WIDTH / PROGNUM_TEX_PAT_WIDTH + 1) * (nCntProgress + 1),
			50.0f + PROGNUM_TEX_SIZE_HEIGHT / PROGNUM_TEX_PAT_HEIGHT, 0.0f);

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
	g_pVtxbuffProgressNum->Unlock();

	//���l������
	g_nCurrentTime = 0;
	g_progLine = PROGLINE_ANNI;
}

//========================
//�I������
//========================
void UninitProgressBar(void)
{
	int nCntTexUnini;		//�e�N�X�`���j���J�E���^

	//�e�N�X�`���̔j��
	//�_
	for (nCntTexUnini = 0; nCntTexUnini < PROGLINE_MAX + 1; nCntTexUnini++)
	{
		if (g_apTextureProgressBar[nCntTexUnini] != NULL)
		{
			g_apTextureProgressBar[nCntTexUnini]->Release();
			g_apTextureProgressBar[nCntTexUnini] = NULL;
		}
	}

	//���C��
	for (nCntTexUnini = 0; nCntTexUnini < PROGLINE_MAX; nCntTexUnini++)
	{
		if (g_aProgLinePolyData[nCntTexUnini].tex != NULL)
		{
			g_aProgLinePolyData[nCntTexUnini].tex->Release();
			g_aProgLinePolyData[nCntTexUnini].tex = NULL;
		}
	}

	//����
	for (nCntTexUnini = 0; nCntTexUnini < PROGLINE_MAX; nCntTexUnini++)
	{
		if (g_apTextureProgressNum[nCntTexUnini] != NULL)
		{
			g_apTextureProgressNum[nCntTexUnini]->Release();
			g_apTextureProgressNum[nCntTexUnini] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	//�_
	if (g_pVtxbuffProgressBar != NULL)
	{
		g_pVtxbuffProgressBar->Release();
		g_pVtxbuffProgressBar = NULL;
	}

	//���C��
	if (g_pVtxbuffProgressLine != NULL)
	{
		g_pVtxbuffProgressLine->Release();
		g_pVtxbuffProgressLine = NULL;
	}

	//����
	if (g_pVtxbuffProgressNum != NULL)
	{
		g_pVtxbuffProgressNum->Release();
		g_pVtxbuffProgressNum = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateProgressBar(void)
{
	int nCntProgress;	//�J�E���^
	int nTexU;			//�e���̐����i�[
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//�o�ߎ��ԉ��Z
	g_nCurrentTime++;

	//�i�s�x�v�Z
	g_fRateofProg = ((float)g_nCurrentTime / GetBGMTime());
	if (g_fRateofProg > 1.0f)
	{//100%�����Ă���100%�ɖ߂�
		g_fRateofProg = 1.0f;
	}

	//�i�s�x���ސݒ�
	if (g_fRateofProg >= PROGLINE_APPEMAX_ROP)
	{
		g_progLine = PROGLINE_APPEMAX;
	}
	else if (g_fRateofProg >= PROGLINE_APPEMIN_ROP)
	{
		g_progLine = PROGLINE_APPEMIN;
	}
	else
	{
		g_progLine = PROGLINE_ANNI;
	}

	//�_�̃|���S���T�C�Y�E�e�N�X�`���T�C�Y�ݒ�
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffProgressBar->Lock(0, 0, (void **)&pVtx, 0);


	pVtx += 4;//�ϖ_�Ɉړ�

	//�|���S���̃T�C�Y�ύX
	pVtx[0].pos.y = g_posPrgBar[0].y + (PROGBAR_TEX_HEIGHT * (1.0f - g_fRateofProg));
	pVtx[1].pos.y = g_posPrgBar[0].y + (PROGBAR_TEX_HEIGHT * (1.0f - g_fRateofProg));

	//�e�N�X�`���T�C�Y�ύX
	pVtx[0].tex.y = 1.0f - g_fRateofProg;
	pVtx[1].tex.y = 1.0f - g_fRateofProg;

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffProgressBar->Unlock();


	//���C���̃|���S���T�C�Y�E�e�N�X�`���T�C�Y�ݒ�
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffProgressLine->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntProgress = 0; nCntProgress < PROGLINE_MAX; nCntProgress++, pVtx += 4)
	{
		if (nCntProgress == g_progLine)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffProgressLine->Unlock();


	//�������_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffProgressNum->Lock(0, 0, (void **)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	//��������
	for (nCntProgress = 0; nCntProgress < PROGNUM_PLACE; nCntProgress++, pVtx += 4)
	{
		nTexU = (int)(g_fRateofProg * 100) % (int)pow(10, (PROGNUM_PLACE - nCntProgress)) / (int)pow(10, PROGNUM_PLACE - 1 - nCntProgress);
		pVtx[0].tex = D3DXVECTOR2((float)nTexU / PROGNUM_TEX_PAT_WIDTH, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(nTexU + 1) / PROGNUM_TEX_PAT_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)nTexU / PROGNUM_TEX_PAT_WIDTH, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(nTexU + 1) / PROGNUM_TEX_PAT_WIDTH, 1.0f);
	}

	//�p�[�Z���g
	pVtx[0].tex = D3DXVECTOR2((float)PROGNUM_TEX_PAT_PARCE / PROGNUM_TEX_PAT_WIDTH, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(PROGNUM_TEX_PAT_PARCE + 1) / PROGNUM_TEX_PAT_WIDTH, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)PROGNUM_TEX_PAT_PARCE / PROGNUM_TEX_PAT_WIDTH, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(PROGNUM_TEX_PAT_PARCE + 1) / PROGNUM_TEX_PAT_WIDTH, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffProgressNum->Unlock();
}

//========================
//�`�揈��
//========================
void DrawProgressBar(void)
{
	int nCntProgressBar;		//�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾


	//�_���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffProgressBar, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�E�|���S���`��
	//�y��
	pDevice->SetTexture(0, g_apTextureProgressBar[0]);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�ϖ_
	pDevice->SetTexture(0, g_apTextureProgressBar[g_progLine + 1]);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);


	//���C�����_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffProgressLine, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntProgressBar = 0; nCntProgressBar < PROGLINE_MAX; nCntProgressBar++)
	{
		//�e�N�X�`���ݒ�E�|���S���`��
		pDevice->SetTexture(0, g_aProgLinePolyData[nCntProgressBar].tex);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntProgressBar * 4, 2);
	}


	//�������_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffProgressNum, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntProgressBar = 0; nCntProgressBar < PROGNUM_PLACE + 1; nCntProgressBar++)
	{
		//�e�N�X�`���ݒ�E�|���S���`��
		pDevice->SetTexture(0, g_apTextureProgressNum[g_progLine]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntProgressBar * 4, 2);
	}
}

//========================
//�i�s�x�ݒ�
//========================
void SetRateofProg(float fRoP)
{
	if ((float)g_nCurrentTime / GetBGMTime() < fRoP)
	{
		g_nCurrentTime = (int)(GetBGMTime() * fRoP);
	}
}

//========================
//�i�s�x�擾
//========================
float GetProgress(void)
{
	return g_fRateofProg;
}