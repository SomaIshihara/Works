//==========================================
//
//�e�v���O����[shadow.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "shadow.h"

//�}�N��
#define MAX_SHADOW	(256)
#define SHADOW_ALPHA	(0.5f)

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffShadow;	//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow;		//�e�N�X�`���|�C���^
Shadow g_aShadow[MAX_SHADOW];				//�e

//========================
//����������
//========================
void InitShadow(void)
{
	int nCntShadow;	//�J�E���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffShadow,
		NULL);

	//�ϐ�������
	for (int nCntInitShadow = 0; nCntInitShadow < MAX_SHADOW; nCntInitShadow++)
	{
		g_aShadow[nCntInitShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntInitShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntInitShadow].bUse = false;
	}

	VERTEX_3D *pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffShadow->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
	{
		//���_���W�i���΍��W�j
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 0.0f, 5.0f);
		pVtx[1].pos = D3DXVECTOR3(5.0f, 0.0f, 5.0f);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, 0.0f, -5.0f);
		pVtx[3].pos = D3DXVECTOR3(5.0f, 0.0f, -5.0f);

		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, SHADOW_ALPHA);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, SHADOW_ALPHA);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, SHADOW_ALPHA);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, SHADOW_ALPHA);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffShadow->Unlock();
}

//========================
//�I������
//========================
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffShadow != NULL)
	{
		g_pVtxbuffShadow->Release();
		g_pVtxbuffShadow = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateShadow(void)
{
	//��
}

//========================
//�`�揈��
//========================
void DrawShadow(void)
{
	int nCntShadow;	//�J�E���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p

	//���Z�����ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffShadow, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureShadow);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			//���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//�ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntShadow, 2);
		}
	}

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//========================
//�ԍ�����U�菈��
//========================
int SetShadow(void)
{
	int nCntShadow = -1;

	for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	{
		if (!g_aShadow[nCount].bUse)
		{
			g_aShadow[nCount].bUse = true;
			nCntShadow = nCount;
			break;
		}
	}

	return nCntShadow;
}

//========================
//�e�ʒu�ݒ菈��
//========================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = pos;
	g_aShadow[nIdxShadow].pos.y = 0.0f;
}

//========================
//�e�������
//========================
void ReleaseIdxShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}