//==========================================
//
//HP�E�G�l���M�[���\���v���O����[hpenestat.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "hpenestat.h"
#include "game.h"
#include "player.h"

//�}�N��
//HP�E�G�l���M�[�e�L�X�g
#define HPENE_TEXT_USEPOLY			(2)											//HP�E�G�l���M�[�̕����|���S����
#define HPENE_TEXT_PATH				"data\\TEXTURE\\Text_HPEne_01.png"			//HP�E�G�l���M�[�̕����e�N�X�`���p�X
#define HPENE_SIZE_WIDTH			(200)										//��
#define HPENE_SIZE_HEIGHT			(32)										//����

//HP�E�G�l���M�[����
#define HPENE_NUMPLACE				(3)											//����
#define HP_REMAIN_NUM_USEPOLY		(HPENE_NUMPLACE * 2 + 2)					//HP�Ŏg�p����|���S����
#define ENE_REMAIN_NUM_USEPOLY		(HPENE_NUMPLACE + 1)						//�G�l���M�[�Ŏg�p����|���S����
#define HPENE_REMAIN_NUM_USEPOLY	(12)										//HP�E�G�l���M�[�̐����|���S����
#define HPENE_REMAIN_NUM_PATH		"data\\TEXTURE\\Number_Parameter_01.png"	//HP�E�G�l���M�[�̐����e�N�X�`���p�X
#define HPENE_REMAIN_NUM_WIDTH		(288)										//�e�N�X�`����
#define HPENE_REMAIN_NUM_HEIGHT		(32)										//�e�N�X�`������
#define HPENE_REMAIN_NUM_PAT_WIDTH	(12)										//�p�^�[����
#define HPENE_REMAIN_NUM_PAT_HEIGHT	(1)											//�p�^�[������

//�e�N�X�`�����Ԋ֌W
#define HPENE_REMAIN_NUM_PAT_SLASH	(10)										//�X���b�V���̃p�^�[���ԍ��i0�n�_�j
#define HPENE_REMAIN_NUM_PAT_PARCE	(11)										//�p�[�Z���g�̃p�^�[���ԍ��i0�n�_�j

//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffHPEneText;					//HP�E�G�l���M�[�e�L�X�g���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureHPEneText;							//HP�E�G�l���M�[�e�L�X�g�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffHPEneRemain;					//HP�E�G�l���M�[�������_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureHPEneRemain;						//HP�E�G�l���M�[�����e�N�X�`���|�C���^

//�ʒu�iY���W�̓e�L�X�g�E�������ɓ��� X��HP�E�G�l���M�[���ɓ����j
float g_fStatposX[2];	//X���W�i0:�e�L�X�g/1:�����j
float g_fStatposY[2];	//Y���W�i0:HP/1:�G�l���M�[�j

//========================
//����������
//========================
void InitHpEneStat(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntHPEneStat;			//HP�E�G�l���M�[�؂�ւ��J�E���^
	int nCntHPEneNum;			//�����p�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���W�ݒ�
	//X
	g_fStatposX[0] = 936.0f;
	g_fStatposX[1] = 1036.0f;

	//Y
	g_fStatposY[0] = 468.0f;
	g_fStatposY[1] = 568.0f;

	//�e�N�X�`���ǂݍ���
	//�e�L�X�g
	D3DXCreateTextureFromFile(pDevice,
		HPENE_TEXT_PATH,
		&g_pTextureHPEneText);

	//����
	D3DXCreateTextureFromFile(pDevice,
		HPENE_REMAIN_NUM_PATH,
		&g_pTextureHPEneRemain);

	//�e�L�X�g���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * HPENE_TEXT_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffHPEneText,
		NULL);

	//�������_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * HPENE_REMAIN_NUM_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffHPEneRemain,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffHPEneText->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntHPEneStat = 0; nCntHPEneStat < 2; nCntHPEneStat++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_fStatposX[0], g_fStatposY[nCntHPEneStat], 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_fStatposX[0] + HPENE_SIZE_WIDTH / 2, g_fStatposY[nCntHPEneStat], 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_fStatposX[0], g_fStatposY[nCntHPEneStat] + HPENE_SIZE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_fStatposX[0] + HPENE_SIZE_WIDTH / 2, g_fStatposY[nCntHPEneStat] + HPENE_SIZE_HEIGHT, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.5f * nCntHPEneStat, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f * (nCntHPEneStat + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f * nCntHPEneStat, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f * (nCntHPEneStat + 1), 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffHPEneText->Unlock();


	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffHPEneRemain->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntHPEneNum = 0; nCntHPEneNum < HP_REMAIN_NUM_USEPOLY; nCntHPEneNum++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_fStatposX[1] + HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH * nCntHPEneNum, 
			g_fStatposY[0], 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_fStatposX[1] + (HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH) * (nCntHPEneNum + 1), 
			g_fStatposY[0], 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_fStatposX[1] + HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH * nCntHPEneNum,
			g_fStatposY[0] + HPENE_REMAIN_NUM_HEIGHT / HPENE_REMAIN_NUM_PAT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_fStatposX[1] + (HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH) * (nCntHPEneNum + 1),
			g_fStatposY[0] + HPENE_REMAIN_NUM_HEIGHT / HPENE_REMAIN_NUM_PAT_HEIGHT, 0.0f);

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

	for (nCntHPEneNum = 0; nCntHPEneNum < ENE_REMAIN_NUM_USEPOLY; nCntHPEneNum++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_fStatposX[1] + HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH * nCntHPEneNum,
			g_fStatposY[1], 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_fStatposX[1] + (HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH + 1) * (nCntHPEneNum + 1),
			g_fStatposY[1], 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_fStatposX[1] + HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH * nCntHPEneNum,
			g_fStatposY[1] + HPENE_REMAIN_NUM_HEIGHT / HPENE_REMAIN_NUM_PAT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_fStatposX[1] + (HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH + 1) * (nCntHPEneNum + 1),
			g_fStatposY[1] + HPENE_REMAIN_NUM_HEIGHT / HPENE_REMAIN_NUM_PAT_HEIGHT, 0.0f);

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
	g_pVtxbuffHPEneRemain->Unlock();
}

//========================
//�I������
//========================
void UninitHpEneStat(void)
{
	//�e�N�X�`���̔j��
	//�e�L�X�g
	if (g_pTextureHPEneText != NULL)
	{
		g_pTextureHPEneText->Release();
		g_pTextureHPEneText = NULL;
	}

	//����
	if (g_pTextureHPEneRemain != NULL)
	{
		g_pTextureHPEneRemain->Release();
		g_pTextureHPEneRemain = NULL;
	}


	//���_�o�b�t�@�̔j��
	//�e�L�X�g
	if (g_pVtxbuffHPEneText != NULL)
	{
		g_pVtxbuffHPEneText->Release();
		g_pVtxbuffHPEneText = NULL;
	}

	//����
	if (g_pVtxbuffHPEneRemain != NULL)
	{
		g_pVtxbuffHPEneRemain->Release();
		g_pVtxbuffHPEneRemain = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateHpEneStat(void)
{
	Player *pPlayer = GetPlayer();	//�v���C���[�|�C���^�i�擾�j
	int nTexU;						//�e���̐����i�[
	int nCntHpEneStatCulc;			//�v�Z�J�E���^

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffHPEneRemain->Lock(0, 0, (void **)&pVtx, 0);

	//�ʏ�̗�
	for (nCntHpEneStatCulc = 0; nCntHpEneStatCulc < HPENE_NUMPLACE; nCntHpEneStatCulc++, pVtx += 4)
	{
		nTexU = pPlayer->nLife % (int)pow(10, (HPENE_NUMPLACE - nCntHpEneStatCulc)) / (int)pow(10, HPENE_NUMPLACE - 1 - nCntHpEneStatCulc);
		pVtx[0].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	}

	//�X���b�V��
	pVtx[0].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_SLASH / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_SLASH + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_SLASH / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_SLASH + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	pVtx += 4;	//�X���b�V�����ő�̗�3����

	//�ő�̗�
	for (nCntHpEneStatCulc = 0; nCntHpEneStatCulc < HPENE_NUMPLACE; nCntHpEneStatCulc++, pVtx += 4)
	{
		nTexU = pPlayer->nMaxLife % (int)pow(10, (HPENE_NUMPLACE - nCntHpEneStatCulc)) / (int)pow(10, HPENE_NUMPLACE - 1 - nCntHpEneStatCulc);
		pVtx[0].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	}

	//�p�[�Z���g
	pVtx[0].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_PARCE / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_PARCE + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_PARCE / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_PARCE + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	pVtx += 4;	//�p�[�Z���g���G�l���M�[3����

	//�G�l���M�[
	for (nCntHpEneStatCulc = 0; nCntHpEneStatCulc < HPENE_NUMPLACE; nCntHpEneStatCulc++, pVtx += 4)
	{
		nTexU = pPlayer->nEnergy % (int)pow(10, (HPENE_NUMPLACE - nCntHpEneStatCulc)) / (int)pow(10, HPENE_NUMPLACE - 1 - nCntHpEneStatCulc);
		pVtx[0].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	}

	//�p�[�Z���g
	pVtx[0].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_PARCE / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_PARCE + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_PARCE / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_PARCE + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffHPEneRemain->Unlock();
}

//========================
//�`�揈��
//========================
void DrawHpEneStat(void)
{
	int nCntHpEneStat;				//�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�L�X�g���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffHPEneText, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureHPEneText);

	for (nCntHpEneStat = 0; nCntHpEneStat < 2; nCntHpEneStat++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHpEneStat * 4, 2);
	}


	//�������_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffHPEneRemain, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureHPEneRemain);

	for (nCntHpEneStat = 0; nCntHpEneStat < HPENE_REMAIN_NUM_USEPOLY; nCntHpEneStat++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHpEneStat * 4, 2);
	}
}