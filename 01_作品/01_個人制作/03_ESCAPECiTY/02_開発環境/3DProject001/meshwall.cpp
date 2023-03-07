//==========================================
//
//�|���S���֌W�v���O����[meshfield.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "meshfield.h"
#include "input.h"

//�}�N��
#define MESHFIELD_LENGTH	(1.0f)
#define MESHFIELD_WIDTH		(28 * 5)
#define MESHFIELD_HEIGHT	(34 * 5)
#define MESHFIELD_IDXNUM	(((MESHFIELD_WIDTH + 1) * MESHFIELD_HEIGHT * 2) + (2 * (MESHFIELD_HEIGHT - 1)))
#define MESHFIELD_POLYNUM	(MESHFIELD_IDXNUM - 2)

//�v���g
WORD *SetIdxSwaingField(int nCntWidth, WORD *pIdx);

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffMeshfield;	//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfield;		//�e�N�X�`���|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//�C���f�b�N�X�o�b�t�@
D3DXVECTOR3 g_posMeshfield;					//�ʒu
D3DXVECTOR3 g_rotMeshfield;					//����
D3DXMATRIX g_mtxWorldMeshfield;				//���[���h�}�g���b�N�X

//========================
//����������
//========================
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTextureMeshfield);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * (MESHFIELD_WIDTH + 1) * (MESHFIELD_HEIGHT + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffMeshfield,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_IDXNUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	int hoge = MESHFIELD_IDXNUM;

	//�ϐ�������
	g_posMeshfield = D3DXVECTOR3(-MESHFIELD_WIDTH / 2 * MESHFIELD_LENGTH, 0.0f, MESHFIELD_HEIGHT / 2 * MESHFIELD_LENGTH);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D *pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffMeshfield->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W+�e�N�X�`�����W
	for (int nCount = 0; nCount < (MESHFIELD_WIDTH + 1) * (MESHFIELD_HEIGHT + 1); nCount++, pVtx++)
	{
		//���_���W�i���΍��W�j
		pVtx->pos = D3DXVECTOR3(MESHFIELD_LENGTH * (nCount % (MESHFIELD_WIDTH + 1)), 0.0f, -MESHFIELD_LENGTH * (nCount / (MESHFIELD_WIDTH + 1)));

		//�@���x�N�g��
		pVtx->nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//�J���[
		pVtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx->tex = D3DXVECTOR2(((float)(nCount % (MESHFIELD_WIDTH + 1)) / (MESHFIELD_WIDTH + 1)), ((float)(nCount / (MESHFIELD_WIDTH + 1)) / (MESHFIELD_HEIGHT + 1)));
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffMeshfield->Unlock();

	//�C���f�b�N�X�o�b�t�@�ݒ�
	WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^
	int nCntWidth;	//�C���f�b�N�X�J�E���^

	//�o�b�t�@���b�N
	g_pIdxBuffMeshField->Lock(0, 0, (void **)&pIdx, 0);

	for (nCntWidth = 0; nCntWidth < MESHFIELD_HEIGHT - 1; nCntWidth++)
	{
		//�O�l�O�l�p�[�g
		pIdx = SetIdxSwaingField(nCntWidth, pIdx);
		
		//�`�����ł�����p�[�g
		//�Ō�̃C���f�b�N�X�������̂ɂ������
		*pIdx = MESHFIELD_WIDTH + (MESHFIELD_WIDTH + 1) * nCntWidth;
		pIdx++;

		//���̎��̂Ɏ��̃��[�v�ōŏ��ɓ��鐔��������
		*pIdx = (MESHFIELD_WIDTH + 1) + (MESHFIELD_WIDTH + 1) * (nCntWidth + 1);
		pIdx++;
	}

	//�Ō�̃O�l�O�l�p�[�g
	SetIdxSwaingField(nCntWidth, pIdx);

	//�o�b�t�@�A�����b�N
	g_pIdxBuffMeshField->Unlock();
}

//========================
//�I������
//========================
void UninitMeshfield(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffMeshfield != NULL)
	{
		g_pVtxbuffMeshfield->Release();
		g_pVtxbuffMeshfield = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�j��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateMeshfield(void)
{
	//��
}

//========================
//�`�揈��
//========================
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffMeshfield, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//�|���S���`��i�C���f�b�N�X���ꂽ��j
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MESHFIELD_WIDTH + 1) * (MESHFIELD_HEIGHT + 1), 0, MESHFIELD_POLYNUM);
}

//========================
//�O�l�O�l�C���f�b�N�X�ݒ菈��
//========================
WORD *SetIdxSwaingField(int nCntWidth, WORD *pIdx)
{
	//�O�l�O�l�p�[�g
	for (int nCountHeight = 0; nCountHeight < (MESHFIELD_WIDTH + 1) * 2; nCountHeight++, pIdx++)
	{
		*pIdx = (MESHFIELD_WIDTH + 1) * ((nCountHeight % 2) ^ 0x1) + nCountHeight / 2 + (MESHFIELD_WIDTH + 1) * nCntWidth;
	}
	return pIdx;
}