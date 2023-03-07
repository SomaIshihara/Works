//==========================================
//
//�G�v���O����[enemy.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "enemy.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "wall.h"
#include "object.h"
#include "debugproc.h"
#include <assert.h>

//�}�N��
#define ENEMY_MOVE_SPEED	(5.0f)	//�v���C���[�ړ����x
#define DUMP_COEF			(0.4f)	//�����W��

//�v���g
void CollisionWallEnemy(int nNumber);
void CollisionObjEnemy(int nNumber);

//�O���[�o���ϐ�
Enemy g_aEnemy[MAX_ENEMY];

//========================
//����������
//========================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�G�ɏ���ǉ�
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�ϐ�������
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nIdxShadow = -1;
		g_aEnemy[nCntEnemy].bUse = false;

		for (int nCntParts = 0; nCntParts < EXITHUMAN_MODEL_NUM; nCntParts++)
		{
			//���f��������
			g_aEnemy[nCntEnemy].aModel[nCntParts] = {};
		}

		//�Ίp���̒����E�p�x
		g_aEnemy[nCntEnemy].fLength = sqrtf(EXITHUMAN_WIDTH * EXITHUMAN_WIDTH + EXITHUMAN_HEIGHT * EXITHUMAN_HEIGHT) * 0.5f;
		g_aEnemy[nCntEnemy].fAngle = atan2f(EXITHUMAN_WIDTH, EXITHUMAN_HEIGHT);

		//�e�ݒ�
		g_aEnemy[nCntEnemy].nIdxShadow = -1;
	}
}

//========================
//�I������
//========================
void UninitEnemy(void)
{
	for (int nCntModel = 0; nCntModel < MAX_ENEMY; nCntModel++)
	{
		for (int nCntParts = 0; nCntParts < EXITHUMAN_MODEL_NUM; nCntParts++)
		{
			//model.cpp�̕���Release���邩�炱������NULL����邾���ł�����
			g_aEnemy[nCntModel].aModel[nCntParts].pMesh = NULL;
			g_aEnemy[nCntModel].aModel[nCntParts].pBuffMat = NULL;
#if 0
			//���b�V���̔j��
			if (g_aEnemy[nCntModel].aModel[nCntParts].pMesh != NULL)
			{
				g_aEnemy[nCntModel].aModel[nCntParts].pMesh->Release();
				g_aEnemy[nCntModel].aModel[nCntParts].pMesh = NULL;
			}

			//�}�e���A���̔j��
			if (g_aEnemy[nCntModel].aModel[nCntParts].pBuffMat != NULL)
			{
				g_aEnemy[nCntModel].aModel[nCntParts].pBuffMat->Release();
				g_aEnemy[nCntModel].aModel[nCntParts].pBuffMat = NULL;
			}
#endif
		}
	}
}

//========================
//�X�V����
//========================
void UpdateEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//���݂̈ʒu��O��̈ʒu�ɂ���
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;

			//��Ԃɉ����ď���
			switch (g_aEnemy[nCntEnemy].state)
			{
			case OBJSTATE_NONE:
				break;
			case OBJSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = OBJSTATE_NONE;
				}
				break;
			case OBJSTATE_BROKEN:
				break;
			}

			//�����B���͂��Ȃ��ŉɂȂƂ������
#if 0
			//�J���������ɉ����ăv���C���[�̌�������
			if (GetMouseClickPress(MOUSE_CLICK_LEFT) == true)
			{
				g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + 1.0f * D3DX_PI + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			}

			//���f���ړ�
			//�J��������݂�
			if (GetKeyboardPress(DIK_W) == true)
			{
				if (false)
				{//���O
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_WA + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
				else if (false)
				{//�E�O
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_WD + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
				else
				{//�O
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_W + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{
				if (false)
				{//����
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_SA + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
				else if (false)
				{//�E��
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_SD + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
				else
				{//���
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_S + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
			}
			else if (false)
			{//��
				g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_A + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
				g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
			}
			else if (false)
			{//�E
				g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_D + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
				g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
			}

			//�{�^������ɉ����ăv���C���[�ړ�
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.z += g_aEnemy[nCntEnemy].move.z;

			//�Ǔ����蔻��
			CollisionWallEnemy(nCntEnemy);

			//�I�u�W�F�N�g�����蔻��
			CollisionObjEnemy(nCntEnemy);

			//�ړ��ʌ���
			g_aEnemy[nCntEnemy].move.x += (0 - g_aEnemy[nCntEnemy].move.x) * DUMP_COEF;
			g_aEnemy[nCntEnemy].move.z += (0 - g_aEnemy[nCntEnemy].move.z) * DUMP_COEF;
#endif
			//�e�ʒu�ݒ�
			SetPositionShadow(g_aEnemy[nCntEnemy].nIdxShadow, g_aEnemy[nCntEnemy].pos);
		}
	}
}

//========================
//�`�揈��
//========================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//"�v���C���[��"���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//�ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//"�v���C���[��"���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			for (int nCntModel = 0; nCntModel < EXITHUMAN_MODEL_NUM; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	//�v�Z�p
				D3DXMATRIX mtxParent;					//�e�̃}�g��

														//"���f����"���[���h�}�g���b�N�X������
				D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCntEnemy].aModel[nCntModel].rotOffset.y, g_aEnemy[nCntEnemy].aModel[nCntModel].rotOffset.x, g_aEnemy[nCntEnemy].aModel[nCntModel].rotOffset.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//�ʒu���f
				D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCntEnemy].aModel[nCntModel].posOffset.x, g_aEnemy[nCntEnemy].aModel[nCntModel].posOffset.y, g_aEnemy[nCntEnemy].aModel[nCntModel].posOffset.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//�p�[�c�̐e�}�g���ݒ�
				if (g_aEnemy[nCntEnemy].aModel[nCntModel].mIdxModelParent != -1)
				{
					mtxParent = g_aEnemy[nCntEnemy].aModel[g_aEnemy[nCntEnemy].aModel[nCntModel].mIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_aEnemy[nCntEnemy].mtxWorld;
				}

				//�p�[�c�̃}�g���Ɛe�}�g�����������킹��
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxParent);

				//"�v���C���[��"���[���h�}�g���b�N�X�ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//�}�e���A���f�[�^�ւ̃|�C���^�擾
				pMat = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].dwNumMatModel; nCntMat++)
				{
					//�]������͗�
					//�}�e���A���ݒ�
					D3DMATERIAL9 changeMat = pMat[nCntMat].MatD3D;
					//�_���[�W��ԂȂ�Ԓǉ�
					changeMat.Diffuse = D3DXCOLOR(0.0f, 0.45f, 0.13f, 1.0f);

					if (g_aEnemy[nCntEnemy].state == OBJSTATE_DAMAGE)
					{
						changeMat.Diffuse.r = 1.0f * OBJ_RED_ALPHA + changeMat.Diffuse.r * (1.0f - OBJ_RED_ALPHA);
						changeMat.Diffuse.g = 0.0f * OBJ_RED_ALPHA + changeMat.Diffuse.g * (1.0f - OBJ_RED_ALPHA);
						changeMat.Diffuse.b = 0.0f * OBJ_RED_ALPHA + changeMat.Diffuse.b * (1.0f - OBJ_RED_ALPHA);
					}

					//�}�e���A���ݒ�
					pDevice->SetMaterial(&changeMat);

					//�e�N�X�`���ݒ�
					pDevice->SetTexture(0, g_aEnemy[nCntEnemy].aModel[nCntModel].apTexture[nCntMat]);

					//���f���`��
					g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}
			}
		}
	}

	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================
//�ݒ菈��
//========================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELNAME name, int nLife)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			Model *pModel = GetModel(name);
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].rot = rot;
			g_aEnemy[nCntEnemy].nLife = nLife;
			for (int nCntParts = 0; nCntParts < EXITHUMAN_MODEL_NUM; nCntParts++)
			{
				g_aEnemy[nCntEnemy].aModel[nCntParts] = *(pModel + nCntParts);
			}

			//�����ݒ�
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[nCntEnemy].nIdxShadow = SetShadow();
			g_aEnemy[nCntEnemy].bUse = true;

			break;
		}
	}
}

//========================
//�Ǔ����蔻�菈��
//========================
void CollisionWallEnemy(int nNumber)
{
	Wall *wall = GetWall();
	D3DXVECTOR3 pos0, pos1;
	D3DXVECTOR3 vecMove, vecLine;
	D3DXVECTOR3 vecToPos, vecToPosOld;
	float fAreaA, fAreaB;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, wall++)
	{
		//�g���Ă���Ƃ���������
		if (wall->bUse == true)
		{
			//�ړ��x�N�g��
			vecMove = g_aEnemy[nNumber].pos - g_aEnemy[nNumber].posOld;

			//�ʒu�v�Z
			pos0.x = wall->pos.x - (wall->fWidth / 2) * cosf(wall->rot.y);
			pos0.y = 0.0f;
			pos0.z = wall->pos.z + (wall->fWidth / 2) * sinf(wall->rot.y);

			pos1.x = wall->pos.x + (wall->fWidth / 2) * cosf(wall->rot.y);
			pos1.y = 0.0f;
			pos1.z = wall->pos.z - (wall->fWidth / 2) * sinf(wall->rot.y);

			vecLine = pos1 - pos0;	//���E���x�N�g��
			vecToPos = g_aEnemy[nNumber].pos - pos0;
			vecToPosOld = g_aEnemy[nNumber].posOld - pos0;

			//�ʐϋ��߂�
			fAreaA = (vecToPos.z * vecMove.x) - (vecToPos.x * vecMove.z);
			fAreaB = (vecLine.z * vecMove.x) - (vecLine.x * vecMove.z);

			if ((vecLine.z * vecToPosOld.x) - (vecLine.x * vecToPosOld.z) >= 0.0f && (vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) < 0.0f)
			{
				if (fAreaA / fAreaB >= 0.0f && fAreaA / fAreaB <= 1.0f)
				{//������
					float fRate = fAreaA / fAreaB;
					g_aEnemy[nNumber].pos.x = pos0.x + (vecLine.x * fRate) - sinf(wall->rot.y) / D3DX_PI * PUSHING_BACK;
					g_aEnemy[nNumber].pos.z = pos0.z + (vecLine.z * fRate) - cosf(wall->rot.y) / D3DX_PI * PUSHING_BACK;
					break;
				}
			}
		}
	}
}

//========================
//�I�u�W�F�N�g�����蔻�菈��
//========================
void CollisionObjEnemy(int nNumber)
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
			vecMove = g_aEnemy[nNumber].pos - g_aEnemy[nNumber].posOld;

			//X
			//�E�����̌v�Z
			vecLineRight = pos1 - pos0;
			vecToPosRight = g_aEnemy[nNumber].pos - pos0;
			vecToPosOldRight = g_aEnemy[nNumber].posOld - pos0;

			//�������̌v�Z
			vecLineLeft = pos3 - pos2;
			vecToPosLeft = g_aEnemy[nNumber].pos - pos2;
			vecToPosOldLeft = g_aEnemy[nNumber].posOld - pos2;

			//Z
			//������̌v�Z
			vecLineUp = pos2 - pos1;
			vecToPosUp = g_aEnemy[nNumber].pos - pos1;
			vecToPosOldUp = g_aEnemy[nNumber].posOld - pos1;
			//�������̌v�Z
			vecLineDown = pos0 - pos3;
			vecToPosDown = g_aEnemy[nNumber].pos - pos3;
			vecToPosOldDown = g_aEnemy[nNumber].posOld - pos3;

			//�����蔻��{��
			//X
			//�ʐϋ��߂�
			fAreaARight = (vecToPosRight.z * vecMove.x) - (vecToPosRight.x * vecMove.z);
			fAreaALeft = (vecToPosLeft.z * vecMove.x) - (vecToPosLeft.x * vecMove.z);
			fAreaBRight = (vecLineRight.z * vecMove.x) - (vecLineRight.x * vecMove.z);
			fAreaBLeft = (vecLineLeft.z * vecMove.x) - (vecLineLeft.x * vecMove.z);

			//����AND�͈͓�vecToPosOldOps
			if ((vecLineRight.z * vecToPosOldRight.x) - (vecLineRight.x * vecToPosOldRight.z) >= 0.0f && (vecLineRight.z * vecToPosRight.x) - (vecLineRight.x * vecToPosRight.z) < 0.0f)
			{
				if (fAreaARight / fAreaBRight >= 0.0f && fAreaARight / fAreaBRight <= 1.0f)
				{//������
					float fRate = fAreaARight / fAreaBRight;
					g_aEnemy[nNumber].pos.x = pos0.x + (vecLineRight.x * fRate) - sinf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					g_aEnemy[nNumber].pos.z = pos0.z + (vecLineRight.z * fRate) - cosf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					break;
				}
			}
			else if ((vecLineLeft.z * vecToPosOldLeft.x) - (vecLineLeft.x * vecToPosOldLeft.z) >= 0.0f && (vecLineLeft.z * vecToPosLeft.x) - (vecLineLeft.x * vecToPosLeft.z) < 0.0f)
			{
				if (fAreaALeft / fAreaBLeft >= 0.0f && fAreaALeft / fAreaBLeft <= 1.0f)
				{//������
					float fRate = fAreaALeft / fAreaBLeft;
					g_aEnemy[nNumber].pos.x = pos2.x + (vecLineLeft.x * fRate) + sinf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					g_aEnemy[nNumber].pos.z = pos2.z + (vecLineLeft.z * fRate) + cosf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					break;
				}
			}

			//Z
			//�ʐϋ��߂�
			fAreaAUp = (vecToPosUp.z * vecMove.x) - (vecToPosUp.x * vecMove.z);
			fAreaADown = (vecToPosDown.z * vecMove.x) - (vecToPosDown.x * vecMove.z);
			fAreaBUp = (vecLineUp.z * vecMove.x) - (vecLineUp.x * vecMove.z);
			fAreaBDown = (vecLineDown.z * vecMove.x) - (vecLineDown.x * vecMove.z);

			//����AND�͈͓�vecToPosOldOps
			if ((vecLineUp.z * vecToPosOldUp.x) - (vecLineUp.x * vecToPosOldUp.z) >= 0.0f && (vecLineUp.z * vecToPosUp.x) - (vecLineUp.x * vecToPosUp.z) < 0.0f)
			{
				if (fAreaAUp / fAreaBUp >= 0.0f && fAreaAUp / fAreaBUp <= 1.0f)
				{//������
					float fRate = fAreaAUp / fAreaBUp;
					g_aEnemy[nNumber].pos.x = pos1.x + (vecLineUp.x * fRate) + cosf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					g_aEnemy[nNumber].pos.z = pos1.z + (vecLineUp.z * fRate) - sinf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					break;
				}
			}
			else if ((vecLineDown.z * vecToPosOldDown.x) - (vecLineDown.x * vecToPosOldDown.z) >= 0.0f && (vecLineDown.z * vecToPosDown.x) - (vecLineDown.x * vecToPosDown.z) < 0.0f)
			{
				if (fAreaADown / fAreaBDown >= 0.0f && fAreaADown / fAreaBDown <= 1.0f)
				{//������
					float fRate = fAreaADown / fAreaBDown;
					g_aEnemy[nNumber].pos.x = pos3.x + (vecLineDown.x * fRate) - cosf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					g_aEnemy[nNumber].pos.z = pos3.z + (vecLineDown.z * fRate) + sinf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					break;
				}
			}
		}
	}
}

//========================
//�擾����
//========================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//========================
//�����������̏���
//========================
void HitEnemy(int nNumber)
{
	g_aEnemy[nNumber].nLife--;

	if (g_aEnemy[nNumber].nLife <= 0)
	{//�Ԃ�����[������
		DestroyEnemy(nNumber);
	}
	else
	{
		g_aEnemy[nNumber].state = OBJSTATE_DAMAGE;
		g_aEnemy[nNumber].nCounterState = OBJ_DAMAGE_TIME;
	}
}

//========================
//�Ԃ�����[������
//========================
void DestroyEnemy(int nNumber)
{
	g_aEnemy[nNumber].bUse = false;
	ReleaseIdxShadow(g_aEnemy[nNumber].nIdxShadow);
}