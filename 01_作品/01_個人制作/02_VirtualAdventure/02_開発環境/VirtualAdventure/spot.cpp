//==========================================
//
//�n�_�֌W�v���O����[spot.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "player.h"
#include "spot.h"
#include "map.h"
#include "camera.h"
#include "game.h"
#include "result.h"

//�}�N��
#define START_NUM	(1)	//�X�^�[�g�n�_�̌�
#define HALFWAY_NUM	(0)	//���Ԓn�_�̌�
#define GOAL_NUM	(1)	//�S�[���̌�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureSpot[SPOTTYPE_MAX] = {};		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffSpot;							//���_�o�b�t�@�|�C���^
Spot g_aSpot[START_NUM + HALFWAY_NUM + GOAL_NUM];				//�n�_�̏��
LPD3DXFONT g_pFontSpot = NULL;			//�t�H���g�ւ̃|�C���^

//�e�N�X�`���p�X
const char *c_apFileNameSpot[] =
{
	"data\\TEXTURE\\Goal_01.png",
	"data\\TEXTURE\\Goal_01.png",
	"data\\TEXTURE\\Goal_01.png"
};

//========================
//�n�_����������
//========================
void InitSpot(void)
{
	int nCntSpot;			//�n�_�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	for (nCntSpot = 0; nCntSpot < sizeof c_apFileNameSpot / sizeof(char *); nCntSpot++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameSpot[nCntSpot],
			&g_apTextureSpot[nCntSpot]);
	}

	//�f�o�b�O�\���p�t�H���g����
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFontSpot);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (START_NUM + HALFWAY_NUM + GOAL_NUM),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffSpot,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffSpot->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntSpot = 0; nCntSpot < START_NUM + HALFWAY_NUM + GOAL_NUM; nCntSpot++, pVtx += 4)
	{
		//�ϐ�������
		g_aSpot[nCntSpot].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu������
		g_aSpot[nCntSpot].spotType = SPOTTYPE_MAX;				//�n�_��ޏ�����
		g_aSpot[nCntSpot].fWidth = 0.0f;						//��������
		g_aSpot[nCntSpot].fHeight = 0.0f;						//����������
		g_aSpot[nCntSpot].bDisp = false;							//�g�p����Ă��Ȃ���Ԃɂ���

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxbuffSpot->Unlock();
}

//========================
//�n�_�I������
//========================
void UninitSpot(void)
{
	int nCntSpot;	//�j���J��Ԃ��J�E���^

	//�n�_������
	ResetSpot();

	//�e�N�X�`���̔j��
	for (nCntSpot = 0; nCntSpot < SPOTTYPE_MAX - 1; nCntSpot++)
	{
		if (g_apTextureSpot[nCntSpot] != NULL)
		{
			g_apTextureSpot[nCntSpot]->Release();
			g_apTextureSpot[nCntSpot] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffSpot != NULL)
	{
		g_pVtxbuffSpot->Release();
		g_pVtxbuffSpot = NULL;
	}
}

//========================
//�n�_�X�V����
//========================
void UpdateSpot(void)
{
	int nCntSpot;		//�n�_�J�E���^
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^
	Spot *pGoalSpot = RefSpot(SPOTTYPE_GOAL, 0);
	Player *pPlayer = GetPlayer();

	//�S�[������
	if (pPlayer->pos.x - PLAYER_SIZE_WIDTH / 2 > pGoalSpot->pos.x - pGoalSpot->fWidth / 2 &&
		pPlayer->pos.x + PLAYER_SIZE_WIDTH / 2 < pGoalSpot->pos.x + pGoalSpot->fWidth / 2 &&
		pPlayer->pos.y <= pGoalSpot->pos.y && pPlayer->pos.y >= pGoalSpot->pos.y - pGoalSpot->fHeight)
	{
		//���F���U���g�J�ځi���ۂ͉����{�^������������J�ځj
		SetResult(RESULT_CLEAR);
		SetGameState(GAMESTATE_END,0);
	}

	//���_�o�b�t�@���b�N
	g_pVtxbuffSpot->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntSpot = 0; nCntSpot < START_NUM + HALFWAY_NUM + GOAL_NUM; nCntSpot++, pVtx += 4)
	{
		pVtx[0].pos.x = g_aSpot[nCntSpot].pos.x - g_aSpot[nCntSpot].fWidth / 2 - GetCameraPos().x;
		pVtx[0].pos.y = g_aSpot[nCntSpot].pos.y - g_aSpot[nCntSpot].fHeight;
		pVtx[1].pos.x = g_aSpot[nCntSpot].pos.x + g_aSpot[nCntSpot].fWidth / 2 - GetCameraPos().x;
		pVtx[1].pos.y = g_aSpot[nCntSpot].pos.y - g_aSpot[nCntSpot].fHeight;
		pVtx[2].pos.x = g_aSpot[nCntSpot].pos.x - g_aSpot[nCntSpot].fWidth / 2 - GetCameraPos().x;
		pVtx[2].pos.y = g_aSpot[nCntSpot].pos.y;
		pVtx[3].pos.x = g_aSpot[nCntSpot].pos.x + g_aSpot[nCntSpot].fWidth / 2 - GetCameraPos().x;
		pVtx[3].pos.y = g_aSpot[nCntSpot].pos.y;
	}

	g_pVtxbuffSpot->Unlock();
}

//========================
//�n�_�`�揈��
//========================
void DrawSpot(void)
{
	int nCntSpot;			//�n�_�e�N�X�`���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffSpot, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	for (nCntSpot = 0; nCntSpot < START_NUM + HALFWAY_NUM + GOAL_NUM; nCntSpot++)
	{
		if (g_aSpot[nCntSpot].bDisp)
		{
			pDevice->SetTexture(0, g_apTextureSpot[g_aSpot[nCntSpot].spotType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSpot * 4, 2);
		}
	}
}

//========================
//�n�_�ݒ菈��
//========================
void SetSpot(Spot setSpotData)
{
	int nCntSpot;		//�J�E���^

	for (nCntSpot = 0; nCntSpot < START_NUM + HALFWAY_NUM + GOAL_NUM; nCntSpot++)
	{
		if (!g_aSpot[nCntSpot].bDisp)
		{
			//�����̏��
			g_aSpot[nCntSpot].pos = setSpotData.pos;
			g_aSpot[nCntSpot].fWidth = setSpotData.fWidth;
			g_aSpot[nCntSpot].fHeight = setSpotData.fHeight;
			g_aSpot[nCntSpot].spotType = setSpotData.spotType;
			g_aSpot[nCntSpot].bDisp = true;

			//���_���W�ݒ�
			VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

			g_pVtxbuffSpot->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntSpot;

			pVtx[0].pos.x = g_aSpot[nCntSpot].pos.x - g_aSpot[nCntSpot].fWidth / 2;
			pVtx[0].pos.y = g_aSpot[nCntSpot].pos.y - g_aSpot[nCntSpot].fHeight;
			pVtx[1].pos.x = g_aSpot[nCntSpot].pos.x + g_aSpot[nCntSpot].fWidth / 2;
			pVtx[1].pos.y = g_aSpot[nCntSpot].pos.y - g_aSpot[nCntSpot].fHeight / 2;
			pVtx[2].pos.x = g_aSpot[nCntSpot].pos.x - g_aSpot[nCntSpot].fWidth / 2;
			pVtx[2].pos.y = g_aSpot[nCntSpot].pos.y;
			pVtx[3].pos.x = g_aSpot[nCntSpot].pos.x + g_aSpot[nCntSpot].fWidth / 2;
			pVtx[3].pos.y = g_aSpot[nCntSpot].pos.y;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_pVtxbuffSpot->Unlock();

			//������
			break;
		}
	}
}

//========================
//�I�������n�_�̏��̃|�C���^��Ԃ�
//========================
Spot *RefSpot(SPOTTYPE type, int nNumber)
{
	int nCount;	//�J�E���^
	int nCounterNumber = 0;	//�������ɍ��������̂𐔂�����

	for (nCount = 0; nCount < START_NUM + HALFWAY_NUM + GOAL_NUM; nCount++)
	{
		if (g_aSpot[nCount].spotType == type)
		{
			nCounterNumber++;
			if (nCounterNumber > nNumber)
			{
				return &g_aSpot[nCount];	//���������̂Ō��������̃|�C���^��Ԃ�
			}
		}
	}

	return nullptr;	//������Ȃ������̂�nullptr
}

//========================
//�n�_���Z�b�g����
//========================
void ResetSpot(void)
{
	int nCntSpot;	//�j���J��Ԃ��J�E���^

	//�n�_������
	for (nCntSpot = 0; nCntSpot < START_NUM + HALFWAY_NUM + GOAL_NUM; nCntSpot++)
	{
		g_aSpot[nCntSpot] = {};
	}
}