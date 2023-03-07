//==========================================
//
//�e�\���v���O����[bullet.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "bullet.h"
#include "shadow.h"
#include "wall.h"
#include "player.h"
#include "enemy.h"
#include "object.h"
#include "debugproc.h"
#include <assert.h>

//�}�N��
#define MAX_BULLET				(128)	//�e�̍ő吔
#define BULLET_TEXSIZE_WIDTH	(12)	//�e�̃T�C�Y�i���j
#define BULLET_TEXSIZE_HEIGHT	(12)	//�e�̃T�C�Y�i�����j
#define BULLET_ATTENUATION_COEF	(0.01f)	//�e�̈ړ����x�����W��
#define BULLET_SLOW_SPEED		(4.0f)	//�e���x���Ƃ݂Ȃ����x

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�O��̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�e�̐F
	int nLife;			//����
	int nIdxShadow;		//�e�ԍ�
	bool bUse;			//�g���Ă��邩�ǂ���
} Bullet;

void CollisionWallBullet(int nCount);
void CollisionObjBullet(int nCount);
void CollisionEnemyBullet(int nCount);

LPDIRECT3DTEXTURE9 g_pTextureBullet;	//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBullet;	//���_�o�b�t�@�|�C���^
D3DXMATRIX g_mtxWorldBullet[MAX_BULLET];	//���[���h�}�g���b�N�X
Bullet g_aBullet[MAX_BULLET];			//�e�\����

//========================
//�e����������
//========================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntBullet;				//�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//�e�\���̂̒��g������
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].nIdxShadow = -1;
		g_aBullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBullet,
		NULL);

	VERTEX_3D *pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++,pVtx += 4)
	{
		//���_���W�i���΍��W�j
		pVtx[0].pos = D3DXVECTOR3(-2.0f, 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(2.0f, 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);

		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffBullet->Unlock();
}

//========================
//�e�I������
//========================
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffBullet != NULL)
	{
		g_pVtxbuffBullet->Release();
		g_pVtxbuffBullet = NULL;
	}
}

//========================
//�e�X�V����
//========================
void UpdateBullet(void)
{
	int nCntBullet;		//�J�E���^
	VERTEX_3D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
	{
		if (g_aBullet[nCntBullet].bUse)
		{//�e���g�p����Ă���
			//������ʒu��O��̈ʒu�ɂ���
			g_aBullet[nCntBullet].posOld = g_aBullet[nCntBullet].pos;

			//�ʒu�X�V
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//����
			g_aBullet[nCntBullet].move.x += (0 - g_aBullet[nCntBullet].move.x) * BULLET_ATTENUATION_COEF;
			g_aBullet[nCntBullet].move.z += (0 - g_aBullet[nCntBullet].move.z) * BULLET_ATTENUATION_COEF;

			//�����蔻��
			CollisionWallBullet(nCntBullet);
			CollisionObjBullet(nCntBullet);
			CollisionEnemyBullet(nCntBullet);

			//�e�ʒu�ݒ�
			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, g_aBullet[nCntBullet].pos);

			//�e���x������
			if (fabsf(g_aBullet[nCntBullet].move.x) <= BULLET_SLOW_SPEED && fabsf(g_aBullet[nCntBullet].move.z) <= BULLET_SLOW_SPEED)
			{
				g_aBullet[nCntBullet].bUse = false;
				ReleaseIdxShadow(g_aBullet[nCntBullet].nIdxShadow);
			}

			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{//�����s����
				g_aBullet[nCntBullet].bUse = false;
				ReleaseIdxShadow(g_aBullet[nCntBullet].nIdxShadow);
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffBullet->Unlock();
}

//========================
//�e�`�揈��
//========================
void DrawBullet(void)
{
	int nCntBullet;				//�J�E���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxTrans;	//�v�Z�p
	D3DXMATRIX mtxView;		//�r���[�}�g���擾�p

	//Z�e�X�g������
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	//Z�e�X�g���s��Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		//Z�o�b�t�@�̗L���E�����ݒ�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffBullet, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse)
		{
			//���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&g_mtxWorldBullet[nCntBullet]);

			//�r���[�}�g���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_mtxWorldBullet[nCntBullet], NULL, &mtxView);
			//�C��
			g_mtxWorldBullet[nCntBullet]._41 = 0.0f;
			g_mtxWorldBullet[nCntBullet]._42 = 0.0f;
			g_mtxWorldBullet[nCntBullet]._43 = 0.0f;

			//�ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet[nCntBullet], &g_mtxWorldBullet[nCntBullet], &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet[nCntBullet]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);
		}
	}

	//Z�e�X�g�L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	//Z�e�X�g���s��Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	//Z�o�b�t�@�̗L���E�����ݒ�
}

//========================
//�e�ݒ菈��
//========================
void SetBullet(D3DXVECTOR3 pos, float fSpeed,float fRot, D3DXCOLOR col)
{
	int nCntBullet;		//�J�E���^

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (!g_aBullet[nCntBullet].bUse)
		{
			//���W�i���S�j�ݒ�
			g_aBullet[nCntBullet].pos = pos;

			//�F�ݒ�
			g_aBullet[nCntBullet].col = col;

			//�ړ��ʌv�Z
			g_aBullet[nCntBullet].move.x = -sinf(fRot) * fSpeed;
			g_aBullet[nCntBullet].move.z = -cosf(fRot) * fSpeed;

			//�����ݒ�
			g_aBullet[nCntBullet].nLife = 1000;

			//�e�ԍ��ݒ�
			g_aBullet[nCntBullet].nIdxShadow = SetShadow();

			//�e�ʒu�ݒ�
			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, g_aBullet[nCntBullet].pos);

			//�g�p���Ă��邱�Ƃɂ���
			g_aBullet[nCntBullet].bUse = true;

			//������
			break;
		}
	}
}

//========================
//�e�����蔻�菈��
//========================
void CollisionWallBullet(int nCount)
{
	Wall *wall = GetWall();
	D3DXVECTOR3 pos0, pos1;
	D3DXVECTOR3 vecMove;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecToPos, vecToPosOld;
	float fAreaA, fAreaB;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, wall++)
	{
		//�g���Ă���Ƃ���������
		if (wall->bUse == true && wall->bAdult == false)
		{
			//�ړ��x�N�g��
			vecMove = g_aBullet[nCount].pos - g_aBullet[nCount].posOld;

			//�ʒu�v�Z
			pos0.x = wall->pos.x - (wall->fWidth / 2) * cosf(wall->rot.y);
			pos0.y = 0.0f;
			pos0.z = wall->pos.z + (wall->fWidth / 2) * sinf(wall->rot.y);

			pos1.x = wall->pos.x + (wall->fWidth / 2) * cosf(wall->rot.y);
			pos1.y = 0.0f;
			pos1.z = wall->pos.z - (wall->fWidth / 2) * sinf(wall->rot.y);

			vecLine = pos1 - pos0;	//���E���x�N�g��
			vecToPos = g_aBullet[nCount].pos - pos0;
			vecToPosOld = g_aBullet[nCount].posOld - pos0;

			//�ʐϋ��߂�
			fAreaA = TASUKIGAKE(vecToPos.x, vecToPos.z, vecMove.x, vecMove.z);
			fAreaB = TASUKIGAKE(vecLine.x, vecLine.z, vecMove.x, vecMove.z);

			if ((vecLine.z * vecToPosOld.x) - (vecLine.x * vecToPosOld.z) >= 0.0f && (vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) < 0.0f)
			{
				if (fAreaA / fAreaB >= 0.0f && fAreaA / fAreaB <= 1.0f)
				{//������
					g_aBullet[nCount].bUse = false;
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
		}
	}
}

//========================
//�e�����蔻�菈��
//========================
void CollisionObjBullet(int nCount)
{
	//=pos0~pos3�̐���==================
	// pos3		pos2
	//	�E<-----�E		���:vecLine
	//	�b		��
	//	�b		�b
	//	��		�b
	//	�E----->�E
	// pos0		pos1
	//==================================

	BluePrint *pbprint = GetBluePrint();
	Object *pObject = GetObj();
	D3DXVECTOR3 pos0, pos1, pos2, pos3;
	D3DXVECTOR3 vecLineRight, vecToPosRight, vecToPosOldRight;
	D3DXVECTOR3 vecLineLeft, vecToPosLeft, vecToPosOldLeft;
	D3DXVECTOR3 vecLineUp, vecToPosUp, vecToPosOldUp;
	D3DXVECTOR3 vecLineDown, vecToPosDown, vecToPosOldDown;
	D3DXVECTOR3 vecMove;
	float fAreaARight, fAreaALeft, fAreaBRight, fAreaBLeft;
	float fAreaAUp, fAreaADown, fAreaBUp, fAreaBDown;


	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++, pObject++)
	{
		if (pObject->bUse == true)
		{
			//�e���_���߂�
			float fLengthX, fLengthZ;
			float fLength;
			float fAngle;
			float rot;

			//-pos0---------------------------------------------------------------------------------------------------------------------------
			//���_�ƒ��S�̋�����X��Z�ʁX�Ōv�Z����
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMin.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMin.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//���_�ƒ��S�̋��������߂�
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//���_�ƒ��S�̊p�x�����߂�
			//0 - �v�Z�ŏo�����p�x + �I�u�W�F�N�g�̊p�x�� -PI ~ PI�ɏC��
			rot = FIX_ROT(-fAngle - pObject->rot.y);
			
			//�p�x�ɉ����Ē��_�̈ʒu�����炷
			pos0.x = pObject->pos.x + sinf(rot) * fLength;
			pos0.y = 0.0f;
			pos0.z = pObject->pos.z - cosf(rot) * fLength;
			//-pos0---------------------------------------------------------------------------------------------------------------------------

			//-pos1---------------------------------------------------------------------------------------------------------------------------
			//���_�ƒ��S�̋�����X��Z�ʁX�Ōv�Z����
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMax.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMin.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//���_�ƒ��S�̋��������߂�
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//���_�ƒ��S�̊p�x�����߂�
			//0 + �v�Z�ŏo�����p�x + �I�u�W�F�N�g�̊p�x�� -PI ~ PI�ɏC��
			rot = FIX_ROT(-fAngle - pObject->rot.y);
			
			//�p�x�ɉ����Ē��_�̈ʒu�����炷
			pos1.x = pObject->pos.x + sinf(rot) * fLength;
			pos1.y = 0.0f;
			pos1.z = pObject->pos.z - cosf(rot) * fLength;
			//-pos1---------------------------------------------------------------------------------------------------------------------------

			//-pos2---------------------------------------------------------------------------------------------------------------------------
			//���_�ƒ��S�̋�����X��Z�ʁX�Ōv�Z����
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMax.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMax.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//���_�ƒ��S�̋��������߂�
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//���_�ƒ��S�̊p�x�����߂�
			//PI - �v�Z�ŏo�����p�x + �I�u�W�F�N�g�̊p�x�� -PI ~ PI�ɏC��
			rot = FIX_ROT(D3DX_PI - fAngle - pObject->rot.y);
			
			//�p�x�ɉ����Ē��_�̈ʒu�����炷
			pos2.x = pObject->pos.x - sinf(rot) * fLength;
			pos2.y = 0.0f;
			pos2.z = pObject->pos.z + cosf(rot) * fLength;
			//-pos2---------------------------------------------------------------------------------------------------------------------------

			//-pos3---------------------------------------------------------------------------------------------------------------------------
			//���_�ƒ��S�̋�����X��Z�ʁX�Ōv�Z����
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMin.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMax.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//���_�ƒ��S�̋��������߂�
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//���_�ƒ��S�̊p�x�����߂�
			//-PI + �v�Z�ŏo�����p�x + �I�u�W�F�N�g�̊p�x�� -PI ~ PI�ɏC��
			rot = FIX_ROT(-D3DX_PI - fAngle - pObject->rot.y);

			//�p�x�ɉ����Ē��_�̈ʒu�����炷
			pos3.x = pObject->pos.x - sinf(rot) * fLength;
			pos3.y = 0.0f;
			pos3.z = pObject->pos.z + cosf(rot) * fLength;
			//-pos3---------------------------------------------------------------------------------------------------------------------------

			//�x�N�g�����߂�
			//move
			vecMove = g_aBullet[nCount].pos - g_aBullet[nCount].posOld;

			//X
			//�E�����̌v�Z
			vecLineRight = pos1 - pos0;
			vecToPosRight = g_aBullet[nCount].pos - pos0;
			vecToPosOldRight = g_aBullet[nCount].posOld - pos0;

			//�������̌v�Z
			vecLineLeft = pos3 - pos2;
			vecToPosLeft = g_aBullet[nCount].pos - pos2;
			vecToPosOldLeft = g_aBullet[nCount].posOld - pos2;

			//Z
			//������̌v�Z
			vecLineUp = pos2 - pos1;
			vecToPosUp = g_aBullet[nCount].pos - pos1;
			vecToPosOldUp = g_aBullet[nCount].posOld - pos1;
			//�������̌v�Z
			vecLineDown = pos0 - pos3;
			vecToPosDown = g_aBullet[nCount].pos - pos3;
			vecToPosOldDown = g_aBullet[nCount].posOld - pos3;

			//�����蔻��{��
			//X
			//�ʐϋ��߂�
			fAreaARight = TASUKIGAKE(vecToPosRight.x, vecToPosRight.z, vecMove.x, vecMove.z);
			fAreaALeft = TASUKIGAKE(vecToPosLeft.x, vecToPosLeft.z, vecMove.x, vecMove.z);
			fAreaBRight = TASUKIGAKE(vecLineRight.x, vecLineRight.z, vecMove.x, vecMove.z);
			fAreaBLeft = TASUKIGAKE(vecLineLeft.x, vecLineLeft.z, vecMove.x, vecMove.z);

			//����AND�͈͓�vecToPosOldOps
			if ((vecLineRight.z * vecToPosRight.x) - (vecLineRight.x * vecToPosRight.z) <= 0.0f && (vecLineRight.z * vecToPosOldRight.x) - (vecLineRight.x * vecToPosOldRight.z) >= 0.0f)
			{
 				if (fAreaARight / fAreaBRight >= 0.0f && fAreaARight / fAreaBRight <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitObj(nCntObj);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
			else if ((vecLineLeft.z * vecToPosLeft.x) - (vecLineLeft.x * vecToPosLeft.z) <= 0.0f && (vecLineLeft.z * vecToPosOldLeft.x) - (vecLineLeft.x * vecToPosOldLeft.z) >= 0.0f)
			{
				if (fAreaALeft / fAreaBLeft >= 0.0f && fAreaALeft / fAreaBLeft <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitObj(nCntObj);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}

			//Z
			//�ʐϋ��߂�
			fAreaAUp = TASUKIGAKE(vecToPosUp.x, vecToPosUp.z, vecMove.x, vecMove.z);
			fAreaADown = TASUKIGAKE(vecToPosDown.x, vecToPosDown.z, vecMove.x, vecMove.z);
			fAreaBUp = TASUKIGAKE(vecLineUp.x, vecLineUp.z, vecMove.x, vecMove.z);
			fAreaBDown = TASUKIGAKE(vecLineDown.x, vecLineDown.z, vecMove.x, vecMove.z);

			//����AND�͈͓�vecToPosOldOps
			if ((vecLineUp.z * vecToPosUp.x) - (vecLineUp.x * vecToPosUp.z) <= 0.0f && (vecLineUp.z * vecToPosOldUp.x) - (vecLineUp.x * vecToPosOldUp.z) >= 0.0f)
			{
				if (fAreaAUp / fAreaBUp >= 0.0f && fAreaAUp / fAreaBUp <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitObj(nCntObj);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
			else if ((vecLineDown.z * vecToPosDown.x) - (vecLineDown.x * vecToPosDown.z) <= 0.0f && (vecLineDown.z * vecToPosOldDown.x) - (vecLineDown.x * vecToPosOldDown.z) >= 0.0f)
			{
				if (fAreaADown / fAreaBDown >= 0.0f && fAreaADown / fAreaBDown <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitObj(nCntObj);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
		}
	}
}

//========================
//�e�����蔻�菈��
//========================
void CollisionEnemyBullet(int nCount)
{
	//=pos0~pos3�̐���==================
	// pos3		pos2
	//	�E<-----�E		���:vecLine
	//	�b		��
	//	�b		�b
	//	��		�b
	//	�E----->�E
	// pos0		pos1
	//==================================

	BluePrint *pbprint = GetBluePrint();
	Enemy *pEnemy = GetEnemy();
	D3DXVECTOR3 pos0, pos1, pos2, pos3;
	D3DXVECTOR3 vecLineRight, vecToPosRight, vecToPosOldRight;
	D3DXVECTOR3 vecLineLeft, vecToPosLeft, vecToPosOldLeft;
	D3DXVECTOR3 vecLineUp, vecToPosUp, vecToPosOldUp;
	D3DXVECTOR3 vecLineDown, vecToPosDown, vecToPosOldDown;
	D3DXVECTOR3 vecMove;
	float fAreaARight, fAreaALeft, fAreaBRight, fAreaBLeft;
	float fAreaAUp, fAreaADown, fAreaBUp, fAreaBDown;


	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			//�e���_���߂�
			float fLengthX, fLengthZ;
			float fLength;
			float fAngle;
			float rot;

			//-pos0---------------------------------------------------------------------------------------------------------------------------
			//���_�ƒ��S�̋�����X��Z�ʁX�Ōv�Z����
			fLengthX = -EXITHUMAN_WIDTH / 2;
			fLengthZ = -EXITHUMAN_HEIGHT / 2;

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//���_�ƒ��S�̋��������߂�
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//���_�ƒ��S�̊p�x�����߂�
																	//0 - �v�Z�ŏo�����p�x + �I�u�W�F�N�g�̊p�x�� -PI ~ PI�ɏC��
			rot = FIX_ROT(-fAngle - pEnemy->rot.y);

			//�p�x�ɉ����Ē��_�̈ʒu�����炷
			pos0.x = pEnemy->pos.x + sinf(rot) * fLength;
			pos0.y = 0.0f;
			pos0.z = pEnemy->pos.z - cosf(rot) * fLength;
			//-pos0---------------------------------------------------------------------------------------------------------------------------

			//-pos1---------------------------------------------------------------------------------------------------------------------------
			//���_�ƒ��S�̋�����X��Z�ʁX�Ōv�Z����
			fLengthX = EXITHUMAN_WIDTH / 2;
			fLengthZ = -EXITHUMAN_HEIGHT / 2;

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//���_�ƒ��S�̋��������߂�
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//���_�ƒ��S�̊p�x�����߂�
																	//0 + �v�Z�ŏo�����p�x + �I�u�W�F�N�g�̊p�x�� -PI ~ PI�ɏC��
			rot = FIX_ROT(-fAngle - pEnemy->rot.y);

			//�p�x�ɉ����Ē��_�̈ʒu�����炷
			pos1.x = pEnemy->pos.x + sinf(rot) * fLength;
			pos1.y = 0.0f;
			pos1.z = pEnemy->pos.z - cosf(rot) * fLength;
			//-pos1---------------------------------------------------------------------------------------------------------------------------

			//-pos2---------------------------------------------------------------------------------------------------------------------------
			//���_�ƒ��S�̋�����X��Z�ʁX�Ōv�Z����
			fLengthX = -EXITHUMAN_WIDTH / 2;
			fLengthZ = EXITHUMAN_HEIGHT / 2;

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//���_�ƒ��S�̋��������߂�
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//���_�ƒ��S�̊p�x�����߂�
																	//PI - �v�Z�ŏo�����p�x + �I�u�W�F�N�g�̊p�x�� -PI ~ PI�ɏC��
			rot = FIX_ROT(D3DX_PI - fAngle - pEnemy->rot.y);

			//�p�x�ɉ����Ē��_�̈ʒu�����炷
			pos2.x = pEnemy->pos.x - sinf(rot) * fLength;
			pos2.y = 0.0f;
			pos2.z = pEnemy->pos.z + cosf(rot) * fLength;
			//-pos2---------------------------------------------------------------------------------------------------------------------------

			//-pos3---------------------------------------------------------------------------------------------------------------------------
			//���_�ƒ��S�̋�����X��Z�ʁX�Ōv�Z����
			fLengthX = EXITHUMAN_WIDTH / 2;
			fLengthZ = EXITHUMAN_HEIGHT / 2;

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//���_�ƒ��S�̋��������߂�
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//���_�ƒ��S�̊p�x�����߂�
																	//-PI + �v�Z�ŏo�����p�x + �I�u�W�F�N�g�̊p�x�� -PI ~ PI�ɏC��
			rot = FIX_ROT(-D3DX_PI - fAngle - pEnemy->rot.y);

			//�p�x�ɉ����Ē��_�̈ʒu�����炷
			pos3.x = pEnemy->pos.x - sinf(rot) * fLength;
			pos3.y = 0.0f;
			pos3.z = pEnemy->pos.z + cosf(rot) * fLength;
			//-pos3---------------------------------------------------------------------------------------------------------------------------

			//�x�N�g�����߂�
			//move
			vecMove = g_aBullet[nCount].pos - g_aBullet[nCount].posOld;

			//X
			//�E�����̌v�Z
			vecLineRight = pos1 - pos0;
			vecToPosRight = g_aBullet[nCount].pos - pos0;
			vecToPosOldRight = g_aBullet[nCount].posOld - pos0;

			//�������̌v�Z
			vecLineLeft = pos3 - pos2;
			vecToPosLeft = g_aBullet[nCount].pos - pos2;
			vecToPosOldLeft = g_aBullet[nCount].posOld - pos2;

			//Z
			//������̌v�Z
			vecLineUp = pos2 - pos1;
			vecToPosUp = g_aBullet[nCount].pos - pos1;
			vecToPosOldUp = g_aBullet[nCount].posOld - pos1;
			//�������̌v�Z
			vecLineDown = pos0 - pos3;
			vecToPosDown = g_aBullet[nCount].pos - pos3;
			vecToPosOldDown = g_aBullet[nCount].posOld - pos3;

			//�����蔻��{��
			//X
			//�ʐϋ��߂�
			fAreaARight = TASUKIGAKE(vecToPosRight.x, vecToPosRight.z, vecMove.x, vecMove.z);
			fAreaALeft = TASUKIGAKE(vecToPosLeft.x, vecToPosLeft.z, vecMove.x, vecMove.z);
			fAreaBRight = TASUKIGAKE(vecLineRight.x, vecLineRight.z, vecMove.x, vecMove.z);
			fAreaBLeft = TASUKIGAKE(vecLineLeft.x, vecLineLeft.z, vecMove.x, vecMove.z);

			//����AND�͈͓�vecToPosOldOps
			if ((vecLineRight.z * vecToPosRight.x) - (vecLineRight.x * vecToPosRight.z) <= 0.0f && (vecLineRight.z * vecToPosOldRight.x) - (vecLineRight.x * vecToPosOldRight.z) >= 0.0f)
			{
				if (fAreaARight / fAreaBRight >= 0.0f && fAreaARight / fAreaBRight <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitEnemy(nCntEnemy);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
			else if ((vecLineLeft.z * vecToPosLeft.x) - (vecLineLeft.x * vecToPosLeft.z) <= 0.0f && (vecLineLeft.z * vecToPosOldLeft.x) - (vecLineLeft.x * vecToPosOldLeft.z) >= 0.0f)
			{
				if (fAreaALeft / fAreaBLeft >= 0.0f && fAreaALeft / fAreaBLeft <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitEnemy(nCntEnemy);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}

			//Z
			//�ʐϋ��߂�
			fAreaAUp = TASUKIGAKE(vecToPosUp.x, vecToPosUp.z, vecMove.x, vecMove.z);
			fAreaADown = TASUKIGAKE(vecToPosDown.x, vecToPosDown.z, vecMove.x, vecMove.z);
			fAreaBUp = TASUKIGAKE(vecLineUp.x, vecLineUp.z, vecMove.x, vecMove.z);
			fAreaBDown = TASUKIGAKE(vecLineDown.x, vecLineDown.z, vecMove.x, vecMove.z);

			//����AND�͈͓�vecToPosOldOps
			if ((vecLineUp.z * vecToPosUp.x) - (vecLineUp.x * vecToPosUp.z) <= 0.0f && (vecLineUp.z * vecToPosOldUp.x) - (vecLineUp.x * vecToPosOldUp.z) >= 0.0f)
			{
				if (fAreaAUp / fAreaBUp >= 0.0f && fAreaAUp / fAreaBUp <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitEnemy(nCntEnemy);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
			else if ((vecLineDown.z * vecToPosDown.x) - (vecLineDown.x * vecToPosDown.z) <= 0.0f && (vecLineDown.z * vecToPosOldDown.x) - (vecLineDown.x * vecToPosOldDown.z) >= 0.0f)
			{
				if (fAreaADown / fAreaBDown >= 0.0f && fAreaADown / fAreaBDown <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitEnemy(nCntEnemy);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
		}
	}
}