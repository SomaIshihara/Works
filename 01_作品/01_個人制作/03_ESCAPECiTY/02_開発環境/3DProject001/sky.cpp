//==========================================
//
//���b�V�����v���O����[sky.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "sky.h"
#include "input.h"

//�}�N��
#define SKY_DIVISION_HORIZONTAL	(8)				//���̕�����
#define SKY_DIVISION_VERTICAL	(16)			//�c�̕�����
#define SKY_DIST_HEIGHT		(200.0f)			//�c�̒��_�Ԋu
#define SKY_RADIUS			(2500.0f)			//���a
#define SKY_NONDRAW_AREA	(0.4f)				//��̃��b�V���h�[����`�悵�Ȃ�����
#define SKY_SUMMIT_NUM	((SKY_DIVISION_VERTICAL + 1) * (SKY_DIVISION_HORIZONTAL + 1))	//���_��
#define SKY_IDXNUM		(((SKY_DIVISION_VERTICAL + 1) * SKY_DIVISION_HORIZONTAL * 2) + (2 * (SKY_DIVISION_HORIZONTAL - 1)))	//�C���f�b�N�X��
#define SKY_POLYNUM		(SKY_IDXNUM - 2)		//�|���S����
#define SKY_NORVECTER	(-1)					//�@���̌����i1�ŕ\�E-1�ŗ��j

//�v���g
WORD *SetIdxSwaingCylinder(int nCntWidth, WORD *pIdx);

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffSky;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSky;				//�e�N�X�`���|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSky = NULL;	//�C���f�b�N�X�o�b�t�@
D3DXVECTOR3 g_posSky;							//�ʒu
D3DXVECTOR3 g_rotSky;							//����
D3DXMATRIX g_mtxWorldSky;						//���[���h�}�g���b�N�X
D3DCULL g_cullMode = D3DCULL_CCW;				//�J�����O���[�h

//========================
//����������
//========================
void InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sky002.jpg",
		&g_pTextureSky);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * SKY_SUMMIT_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffSky,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * SKY_IDXNUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSky,
		NULL);

	//�ϐ�������
	g_posSky = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotSky = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_cullMode = D3DCULL_CW;

	VERTEX_3D *pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffSky->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W+�e�N�X�`�����W
	for (int nCntHorizontal = 0; nCntHorizontal < SKY_DIVISION_HORIZONTAL + 1; nCntHorizontal++)
	{
		for (int nCntVertical = 0; nCntVertical < SKY_DIVISION_VERTICAL + 1; nCntVertical++, pVtx++)
		{
			//�v�Z�p
			float fAngle = fmodf(((float)nCntVertical / (SKY_DIVISION_VERTICAL / 2) * D3DX_PI) + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			D3DXVECTOR3 nor;

			//���_���W�i���΍��W�j
			pVtx->pos = D3DXVECTOR3(sinf(fAngle) * SKY_RADIUS * sinf((SKY_NONDRAW_AREA + ((float)nCntHorizontal / SKY_DIVISION_HORIZONTAL) * (0.5f - SKY_NONDRAW_AREA)) * D3DX_PI),
				SKY_DIST_HEIGHT * (SKY_DIVISION_HORIZONTAL - nCntHorizontal), 
				-cosf(fAngle) * SKY_RADIUS * sinf((SKY_NONDRAW_AREA + ((float)nCntHorizontal / SKY_DIVISION_HORIZONTAL) * (0.5f - SKY_NONDRAW_AREA)) * D3DX_PI));

			//�@���x�N�g��
			nor = pVtx->pos;	//���_�ʒu���
			nor.y = 0.0f;		//y�͂���Ȃ��̂�0
			nor.x *= SKY_NORVECTER;
			nor.z *= SKY_NORVECTER;	//xz�͕\���w��
			D3DXVec3Normalize(&nor, &nor);		//���K��
			pVtx->nor = nor;					//���_���ɑ��

			//�J���[
			pVtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx->tex = D3DXVECTOR2(((float)nCntVertical / SKY_DIVISION_VERTICAL), ((float)nCntHorizontal / SKY_DIVISION_HORIZONTAL));
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffSky->Unlock();

	//�C���f�b�N�X�o�b�t�@�ݒ�
	WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^
	int nCntWidth = 0;	//�C���f�b�N�X�J�E���^

	//�o�b�t�@���b�N
	g_pIdxBuffSky->Lock(0, 0, (void **)&pIdx, 0);

	for (nCntWidth = 0; nCntWidth < SKY_DIVISION_HORIZONTAL - 1; nCntWidth++)
	{
		//�O�l�O�l�p�[�g
		pIdx = SetIdxSwaingCylinder(nCntWidth, pIdx);
		
		//�`�����ł�����p�[�g
		//�Ō�̃C���f�b�N�X�������̂ɂ������
		*pIdx = SKY_DIVISION_VERTICAL + (SKY_DIVISION_VERTICAL + 1) * nCntWidth;
		pIdx++;

		//���̎��̂Ɏ��̃��[�v�ōŏ��ɓ��鐔��������
		*pIdx = (SKY_DIVISION_VERTICAL + 1) + (SKY_DIVISION_VERTICAL + 1) * (nCntWidth + 1);
		pIdx++;
	}

	//�Ō�̃O�l�O�l�p�[�g
	SetIdxSwaingCylinder(nCntWidth, pIdx);
	
	//�o�b�t�@�A�����b�N
	g_pIdxBuffSky->Unlock();
}

//========================
//�I������
//========================
void UninitSky(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSky != NULL)
	{
		g_pTextureSky->Release();
		g_pTextureSky = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffSky != NULL)
	{
		g_pVtxbuffSky->Release();
		g_pVtxbuffSky = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�j��
	if (g_pIdxBuffSky != NULL)
	{
		g_pIdxBuffSky->Release();
		g_pIdxBuffSky = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateSky(void)
{
	//��
}

//========================
//�`�揈��
//========================
void DrawSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p

	//�J�����O�ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, g_cullMode);

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&g_mtxWorldSky);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotSky.y, g_rotSky.x, g_rotSky.z);
	D3DXMatrixMultiply(&g_mtxWorldSky, &g_mtxWorldSky, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_posSky.x, g_posSky.y, g_posSky.z);
	D3DXMatrixMultiply(&g_mtxWorldSky, &g_mtxWorldSky, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSky);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffSky, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffSky);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureSky);

	//�|���S���`��i�C���f�b�N�X���ꂽ��j
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SKY_SUMMIT_NUM, 0, SKY_POLYNUM);

	//�J�����O�߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//========================
//�O�l�O�l�C���f�b�N�X�ݒ菈��
//========================
WORD *SetIdxSwaingCylinder(int nCntWidth, WORD *pIdx)
{
	//�O�l�O�l�p�[�g
	for (int nCountHeight = 0; nCountHeight < (SKY_DIVISION_VERTICAL + 1) * 2; nCountHeight++, pIdx++)
	{
		*pIdx = (SKY_DIVISION_VERTICAL + 1) * ((nCountHeight % 2) ^ 0x1) + nCountHeight / 2 + (SKY_DIVISION_VERTICAL + 1) * nCntWidth;
	}
	return pIdx;
}