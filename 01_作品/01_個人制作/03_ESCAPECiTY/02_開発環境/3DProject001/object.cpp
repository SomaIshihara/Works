//==========================================
//
//���f���֌W�v���O����[object.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "object.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"

//�}�N��
#define OBJ_MOVE_SPEED		(1.0f)	//���f���ړ����x

//�O���[�o���ϐ�
BluePrint g_aBPrint[BLUEPRINTIDX_MAX];
Object g_aObject[MAX_OBJECT];
int g_nNumObj = 0;

//�t�@�C���p�X
const char* c_apFilePathObject[] =
{
	"data\\MODEL\\jobi.x",
	"data\\MODEL\\subway_entrance.x",
	"data\\MODEL\\Rock_xfile\\Rock_01.x",
	"data\\MODEL\\Rock_xfile\\Rock_02.x",
	"data\\MODEL\\Rock_xfile\\Rock_03.x",
	"data\\MODEL\\Rock_xfile\\Rock_04.x",
	"data\\MODEL\\Rock_xfile\\Rock_05.x",
	"data\\MODEL\\Rock_xfile\\Rock_06.x",
	"data\\MODEL\\Rock_xfile\\Rock_07.x",
	"data\\MODEL\\Rock_xfile\\Rock_08.x",
	"data\\MODEL\\Rock_xfile\\Rock_09.x",
	"data\\MODEL\\Rock_xfile\\Rock_10.x",
	"data\\MODEL\\Rock_xfile\\Rock_11.x",
	"data\\MODEL\\building002.x",
	"data\\MODEL\\building102.x",
	"data\\MODEL\\building202.x",
	"data\\MODEL\\building302.x",
	"data\\MODEL\\building402.x",
	"data\\MODEL\\building502.x"
};

//========================
//����������
//========================
void InitObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATERIAL *pMat;	//�}�e���A���|�C���^
	int nNumVtx;		//���_��
	DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�|�C���^

	//�ϐ�������
	for (int nCntInitBP = 0; nCntInitBP < BLUEPRINTIDX_MAX; nCntInitBP++)
	{
		g_aBPrint[nCntInitBP].dwNumMat = 0;
		g_aBPrint[nCntInitBP].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBPrint[nCntInitBP].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	for (int nCntInitOBJ = 0; nCntInitOBJ < MAX_OBJECT; nCntInitOBJ++)
	{
		g_aObject[nCntInitOBJ].bpidx = {};
		g_aObject[nCntInitOBJ].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntInitOBJ].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntInitOBJ].bLifeUse = true;
		g_aObject[nCntInitOBJ].nLife = 0;
		g_aObject[nCntInitOBJ].state = OBJSTATE_BROKEN;
		g_aObject[nCntInitOBJ].nCounterState = 0;
		g_aObject[nCntInitOBJ].nIdxShadow = -1;
		g_aObject[nCntInitOBJ].bUse = false;
	}

	//�ǂݍ���
	for (int nCntModel = 0; nCntModel < BLUEPRINTIDX_MAX && nCntModel < (sizeof c_apFilePathObject / sizeof(char *)); nCntModel++)
	{
		//X�t�@�C���ǂݍ���		
		if (SUCCEEDED(D3DXLoadMeshFromX(
			c_apFilePathObject[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aBPrint[nCntModel].pBuffMat,
			NULL,
			&g_aBPrint[nCntModel].dwNumMat,
			&g_aBPrint[nCntModel].pMesh)))
		{
			//���_�����擾
			nNumVtx = g_aBPrint[nCntModel].pMesh->GetNumVertices();

			//���_�t�H�[�}�b�g
			dwSizeFVF = D3DXGetFVFVertexSize(g_aBPrint[nCntModel].pMesh->GetFVF());

			//���_�o�b�t�@���b�N
			g_aBPrint[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void **)&pVtxBuff);

			//�ŏ������S�������
			D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

			g_aBPrint[nCntModel].vtxMax = vtx;
			g_aBPrint[nCntModel].vtxMin = vtx;

			pVtxBuff += dwSizeFVF;

			for (int nCntVtx = 1; nCntVtx < nNumVtx; nCntVtx++, pVtxBuff += dwSizeFVF)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

				if (g_aBPrint[nCntModel].vtxMax.x < vtx.x)
				{
					g_aBPrint[nCntModel].vtxMax.x = vtx.x;
				}
				if (g_aBPrint[nCntModel].vtxMax.z < vtx.z)
				{
					g_aBPrint[nCntModel].vtxMax.z = vtx.z;
				}
				if (g_aBPrint[nCntModel].vtxMin.x > vtx.x)
				{
					g_aBPrint[nCntModel].vtxMin.x = vtx.x;
				}
				if (g_aBPrint[nCntModel].vtxMin.z > vtx.z)
				{
					g_aBPrint[nCntModel].vtxMin.z = vtx.z;
				}
			}

			//���_�o�b�t�@�A�����b�N
			g_aBPrint[nCntModel].pMesh->UnlockVertexBuffer();

			//�e�N�X�`���ǂݍ���
			//�}�e���A�����ɑ΂���|�C���^�擾
			pMat = (D3DXMATERIAL *)g_aBPrint[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntTex = 0; nCntTex < (int)g_aBPrint[nCntModel].dwNumMat; nCntTex++)
			{
				if (pMat[nCntTex].pTextureFilename != NULL)
				{
					//�e�N�X�`���ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntTex].pTextureFilename,
						&g_aBPrint[nCntModel].apTexture[nCntTex]);
				}
			}
		}
		else
		{
			break;
		}
	}

	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		g_aObject[nCntObj].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntObj].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntObj].state = OBJSTATE_MAX;
		g_aObject[nCntObj].nLife = 5;
		g_aObject[nCntObj].nCounterState = 0;
		g_aObject[nCntObj].nIdxShadow = -1;
		g_aObject[nCntObj].bUse = false;
	}
	
	//�I�u�W�F�N�g�g�p����0��
	g_nNumObj = 0;
}

//========================
//�I������
//========================
void UninitObject(void)
{
	for (int nCount = 0; nCount < BLUEPRINTIDX_MAX; nCount++)
	{
		//�e�N�X�`���j��
		for (int nCntUniniTex = 0; nCntUniniTex < OBJ_MAX_TEXTURE; nCntUniniTex++)
		{
			if (g_aBPrint[nCount].apTexture[nCntUniniTex] != NULL)
			{
				g_aBPrint[nCount].apTexture[nCntUniniTex]->Release();
				g_aBPrint[nCount].apTexture[nCntUniniTex] = NULL;
			}
		}
		//���b�V���̔j��
		if (g_aBPrint[nCount].pMesh != NULL)
		{
			g_aBPrint[nCount].pMesh->Release();
			g_aBPrint[nCount].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_aBPrint[nCount].pBuffMat != NULL)
		{
			g_aBPrint[nCount].pBuffMat->Release();
			g_aBPrint[nCount].pBuffMat = NULL;
		}
	}
}

//========================
//�X�V����
//========================
void UpdateObject(void)
{
	//�I�u�W�F�N�g����
	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		if (g_aObject[nCount].bUse == true)
		{
			//��Ԃɉ����ď���
			switch (g_aObject[nCount].state)
			{
			case OBJSTATE_NONE:
				break;
			case OBJSTATE_DAMAGE:
				g_aObject[nCount].nCounterState--;
				if (g_aObject[nCount].nCounterState <= 0)
				{
					g_aObject[nCount].state = OBJSTATE_NONE;
				}
				break;
			case OBJSTATE_BROKEN:
				break;
			}

			//�e�ʒu�ݒ�
			SetPositionShadow(g_aObject[nCount].nIdxShadow, g_aObject[nCount].pos);
		}
	}

	//����
	if (GetKeyboardTrigger(DIK_F5) == true && g_nNumObj == 0)
	{
		//�I�u�W�F�N�g����
		//���͉������Ȃ�
	}
}

//========================
//�`�揈��
//========================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		if (g_aObject[nCount].bUse == true)
		{
			//���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aObject[nCount].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObject[nCount].rot.y, g_aObject[nCount].rot.x, g_aObject[nCount].rot.z);
			D3DXMatrixMultiply(&g_aObject[nCount].mtxWorld, &g_aObject[nCount].mtxWorld, &mtxRot);

			//�ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aObject[nCount].pos.x, g_aObject[nCount].pos.y, g_aObject[nCount].pos.z);
			D3DXMatrixMultiply(&g_aObject[nCount].mtxWorld, &g_aObject[nCount].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aObject[nCount].mtxWorld);

			//�}�e���A���f�[�^�ւ̃|�C���^�擾
			pMat = (D3DXMATERIAL*)g_aBPrint[g_aObject[nCount].bpidx].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBPrint[g_aObject[nCount].bpidx].dwNumMat; nCntMat++)
			{
				//�}�e���A���ݒ�
				D3DMATERIAL9 changeMat = pMat[nCntMat].MatD3D;
				//�_���[�W��ԂȂ�Ԓǉ�
				if (g_aObject[nCount].state == OBJSTATE_DAMAGE)
				{
					changeMat.Diffuse.r = 1.0f * OBJ_RED_ALPHA + pMat[nCntMat].MatD3D.Diffuse.r * (1.0f - OBJ_RED_ALPHA);
					changeMat.Diffuse.g = 0.0f * OBJ_RED_ALPHA + pMat[nCntMat].MatD3D.Diffuse.g * (1.0f - OBJ_RED_ALPHA);
					changeMat.Diffuse.b = 0.0f * OBJ_RED_ALPHA + pMat[nCntMat].MatD3D.Diffuse.b * (1.0f - OBJ_RED_ALPHA);
				}
				pDevice->SetMaterial(&changeMat);

				//�e�N�X�`���ݒ�
				pDevice->SetTexture(0, g_aBPrint[g_aObject[nCount].bpidx].apTexture[nCntMat]);

				//���f���`��
				g_aBPrint[g_aObject[nCount].bpidx].pMesh->DrawSubset(nCntMat);
			}
		}
	}
	
	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================
//�\������
//========================
void SetObject(BLUEPRINTIDX bpidx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bLifeUse, int nLife)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		if (g_aObject[nCntObj].bUse == false)
		{
			//�����̏���ǉ�
			g_aObject[nCntObj].bpidx = bpidx;
			g_aObject[nCntObj].pos = pos;
			g_aObject[nCntObj].rot = rot;
			g_aObject[nCntObj].bLifeUse = bLifeUse;
			g_aObject[nCntObj].nLife = nLife;

			//�̗͂��g�p����ꍇ�̂݉e�ݒ�
			if (g_aObject[nCntObj].bLifeUse == true)
			{
				//�e�ݒ�
				g_aObject[nCntObj].nIdxShadow = SetShadow();
			}

			//�g�p���Ă��邱�Ƃɂ���
			g_aObject[nCntObj].bUse = true;

			//�I�u�W�F�N�g�����₷
			g_nNumObj++;

			//������
			break;
		}
	}
}

//========================
//�I�u�W�F�N�g�擾����
//========================
Object *GetObj(void)
{
	return &g_aObject[0];
}

//========================
//�݌v�}�擾����
//========================
BluePrint *GetBluePrint(void)
{
	return &g_aBPrint[0];
}

//========================
//�����������̏���
//========================
void HitObj(int nNumObj)
{
	//�̗͂̍��ڂ��g�p����Ȃ�_���[�W
	if (g_aObject[nNumObj].bLifeUse == true)
	{
		g_aObject[nNumObj].nLife--;

		if (g_aObject[nNumObj].nLife <= 0)
		{//�Ԃ�����[������
			DestroyObj(nNumObj);
			ReleaseIdxShadow(g_aObject[nNumObj].nIdxShadow);
		}
		else
		{
			g_aObject[nNumObj].state = OBJSTATE_DAMAGE;
			g_aObject[nNumObj].nCounterState = OBJ_DAMAGE_TIME;
		}
	}
}

//========================
//�Ԃ�����[������
//========================
void DestroyObj(int nNumObj)
{
	g_aObject[nNumObj].bUse = false;
	g_nNumObj--;
}