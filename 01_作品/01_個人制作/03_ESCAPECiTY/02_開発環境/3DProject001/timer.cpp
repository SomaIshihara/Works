//==========================================
//
//���ԕ\���v���O����[timer.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "timer.h"

//�}�N��
#define CHAR_TIME_NUM			(5)					//TIME�Ŏg��������
#define TIMER_NUM_PLACE			(CHAR_TIME_NUM + 5)	//�������iCHAR_TIME_NUM + Num*5�j

LPDIRECT3DTEXTURE9 g_pTextureTimer;								//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTimer;						//���_�o�b�t�@�|�C���^
D3DXVECTOR3 g_posTimer;											//�X�R�A���W
int g_nTimer;													//����
const char c_aTextTime[CHAR_TIME_NUM + 1] = "TIME:";

//========================
//����������
//========================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntTimer;				//�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\EC_CharTex_01.png",
		&g_pTextureTimer);

	//�X�R�A�ʒu�E�l�E��ޏ�����
	g_posTimer = D3DXVECTOR3(420.0f, 16.0f, 0.0f);
	g_nTimer = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIMER_NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTimer,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTimer->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntTimer = 0; nCntTimer < TIMER_NUM_PLACE; nCntTimer++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTimer.x + (TIMER_CHAR_SIZE_WIDTH * nCntTimer),
			g_posTimer.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTimer.x + (TIMER_CHAR_SIZE_WIDTH * (nCntTimer + 1)),
			g_posTimer.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTimer.x + (TIMER_CHAR_SIZE_WIDTH * nCntTimer),
			g_posTimer.y + TIMER_CHAR_SIZE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTimer.x + (TIMER_CHAR_SIZE_WIDTH * (nCntTimer + 1)),
			g_posTimer.y + TIMER_CHAR_SIZE_HEIGHT, 0.0f);

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
	g_pVtxbuffTimer->Unlock();

	//�X�R�A�\��
	SetTimer(0);
}

//========================
//�I������
//========================
void UninitTimer(void)
{
	//�e�N�X�`���j��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffTimer != NULL)
	{
		g_pVtxbuffTimer->Release();
		g_pVtxbuffTimer = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateTimer(void)
{
	int nMinutes, nSeconds;
	int aTexU[TIMER_NUM_PLACE];		//�e���̐����i�[
	int nCntTimeStr;				//�v�Z�J�E���^

	//���b�v�Z
	nMinutes = g_nTimer / 60;
	nSeconds = g_nTimer % 60;

	//�����̊i�[
	for (nCntTimeStr = 0; nCntTimeStr < CHAR_TIME_NUM - 1; nCntTimeStr++)
	{
		aTexU[nCntTimeStr] = CHARDATA(c_aTextTime[nCntTimeStr]);
	}
	//�R����
	aTexU[nCntTimeStr] = CHAR_SPACE;	//[4]
	nCntTimeStr++;

	//��
	aTexU[nCntTimeStr] = nMinutes / 10;	//[5]
	nCntTimeStr++;
	aTexU[nCntTimeStr] = nMinutes % 10;	//[6]
	nCntTimeStr++;

	//�R����
	aTexU[nCntTimeStr] = CHAR_COLON;	//[7]
	nCntTimeStr++;

	//�b
	aTexU[nCntTimeStr] = nSeconds / 10;	//[8]
	nCntTimeStr++;
	aTexU[nCntTimeStr] = nSeconds % 10;	//[9]

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTimer->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntTimeStr = 0; nCntTimeStr < TIMER_NUM_PLACE; nCntTimeStr++, pVtx += 4)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(aTexU[nCntTimeStr] % CHAR_PATT_WIDTH) / CHAR_PATT_WIDTH,
			(float)(aTexU[nCntTimeStr] / CHAR_PATT_WIDTH) / CHAR_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(aTexU[nCntTimeStr] % CHAR_PATT_WIDTH + 1) / CHAR_PATT_WIDTH,
			(float)(aTexU[nCntTimeStr] / CHAR_PATT_WIDTH) / CHAR_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(aTexU[nCntTimeStr] % CHAR_PATT_WIDTH) / CHAR_PATT_WIDTH,
			(float)(aTexU[nCntTimeStr] / CHAR_PATT_WIDTH + 1) / CHAR_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(aTexU[nCntTimeStr] % CHAR_PATT_WIDTH + 1) / CHAR_PATT_WIDTH,
			(float)(aTexU[nCntTimeStr] / CHAR_PATT_WIDTH + 1) / CHAR_PATT_HEIGHT);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffTimer->Unlock();
}

//========================
//�`�揈��
//========================
void DrawTimer(void)
{
	int nCntTimer;				//�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffTimer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureTimer);

	for (nCntTimer = 0; nCntTimer < TIMER_NUM_PLACE; nCntTimer++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTimer * 4, 2);
	}
}

//========================
//�ݒ菈��
//========================
void SetTimer(int nTimer)
{
	g_nTimer = nTimer;

#if 0
	int aTexU[TIMERNUM_PLACE];		//�e���̐����i�[
	int nCntTimerCulc;				//�v�Z�J�E���^

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTimer->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntTimerCulc = 0; nCntTimerCulc < TIMERNUM_PLACE; nCntTimerCulc++, pVtx += 4)
	{
		aTexU[nCntTimerCulc] = g_nTimer % (int)pow(10, (TIMERNUM_PLACE - nCntTimerCulc)) / (int)pow(10, TIMERNUM_PLACE - 1 - nCntTimerCulc);
		pVtx[0].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffTimer->Unlock();
#endif
}

//========================
//���Z����
//========================
void AddTimer(int nValue)
{
	g_nTimer += nValue;
}

//========================
//���ԁi�b�P�ʁj�擾
//========================
int GetTimer(void)
{
	return g_nTimer;
}