//==========================================
//
//�|���S���֌W�v���O����[wall.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "wall.h"
#include "input.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffWall;	//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall;		//�e�N�X�`���|�C���^
Wall g_wall[MAX_WALL];
bool g_bDispAdultWall;

//========================
//����������
//========================
void InitWall(void)
{
	int nCntWall;	//�J�E���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffWall,
		NULL);

	//�\���̏�����
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].fWidth = 0.0f;
		g_wall[nCntWall].fHeight = 0.0f;
		g_wall[nCntWall].bUse = false;
	}

	//�ϐ�������
	g_bDispAdultWall = false;

	VERTEX_3D *pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffWall->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�i���΍��W�j
	pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffWall->Unlock();
}

//========================
//�I������
//========================
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffWall != NULL)
	{
		g_pVtxbuffWall->Release();
		g_pVtxbuffWall = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateWall(void)
{
	if (GetKeyboardTrigger(DIK_F4) == true)
	{
		//g_bDispAdultWall = g_bDispAdultWall ? false : true;
	}
}

//========================
//�`�揈��
//========================
void DrawWall(void)
{
	int nCntWall;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffWall, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_wall[nCntWall].bUse == true)
		{
			if (g_wall[nCntWall].bAdult == false || g_bDispAdultWall == true)
			{
				//���[���h�}�g���b�N�X������
				D3DXMatrixIdentity(&g_wall[nCntWall].mtxWorld);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall[nCntWall].rot.y, g_wall[nCntWall].rot.x, g_wall[nCntWall].rot.z);
				D3DXMatrixMultiply(&g_wall[nCntWall].mtxWorld, &g_wall[nCntWall].mtxWorld, &mtxRot);

				//�ʒu���f
				D3DXMatrixTranslation(&mtxTrans, g_wall[nCntWall].pos.x, g_wall[nCntWall].pos.y, g_wall[nCntWall].pos.z);
				D3DXMatrixMultiply(&g_wall[nCntWall].mtxWorld, &g_wall[nCntWall].mtxWorld, &mtxTrans);

				//���[���h�}�g���b�N�X�ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_wall[nCntWall].mtxWorld);

				//�e�N�X�`���ݒ�
				pDevice->SetTexture(0, g_pTextureWall);

				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntWall, 2);
			}
		}
	}
}

//========================
//�z�u����
//========================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, bool bAdult)
{
	VERTEX_3D *pVtx;

	for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{
		if (!g_wall[nCount].bUse)
		{
			g_wall[nCount].pos = pos;
			g_wall[nCount].rot = rot;
			g_wall[nCount].fWidth = fWidth;
			g_wall[nCount].fHeight = fHeight;
			g_wall[nCount].bAdult = bAdult;
			g_wall[nCount].bUse = true;

			if (g_wall[nCount].bAdult == false || true)
			{
				//���_���ݒ�
				//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
				g_pVtxbuffWall->Lock(0, 0, (void **)&pVtx, 0);

				//�|�C���^���炷
				pVtx += 4 * nCount;

				//���_���W�i���΍��W�j�i�n�ʒ��S�j
				pVtx[0].pos = D3DXVECTOR3(-g_wall[nCount].fWidth / 2, g_wall[nCount].fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_wall[nCount].fWidth / 2, g_wall[nCount].fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_wall[nCount].fWidth / 2, 0.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_wall[nCount].fWidth / 2, 0.0f, 0.0f);

				//�@���x�N�g��
				pVtx[0].nor = D3DXVECTOR3(sinf(g_wall[nCount].rot.y), 0.0f, -cosf(g_wall[nCount].rot.y));
				pVtx[1].nor = D3DXVECTOR3(sinf(g_wall[nCount].rot.y), 0.0f, -cosf(g_wall[nCount].rot.y));
				pVtx[2].nor = D3DXVECTOR3(sinf(g_wall[nCount].rot.y), 0.0f, -cosf(g_wall[nCount].rot.y));
				pVtx[3].nor = D3DXVECTOR3(sinf(g_wall[nCount].rot.y), 0.0f, -cosf(g_wall[nCount].rot.y));

				//�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_wall[nCount].fWidth / 50.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, g_wall[nCount].fHeight / 50.0f);
				pVtx[3].tex = D3DXVECTOR2(g_wall[nCount].fWidth / 50.0f, g_wall[nCount].fHeight / 50.0f);

				//���_�o�b�t�@���A�����b�N
				g_pVtxbuffWall->Unlock();
			}

			//������
			break;
		}
	}
}

//========================
//�擾����
//========================
Wall *GetWall(void)
{
	return &g_wall[0];
}