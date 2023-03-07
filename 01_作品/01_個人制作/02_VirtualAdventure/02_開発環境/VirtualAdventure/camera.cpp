//==========================================
//
//�}�b�v�v���O����[camera.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "camera.h"
#include "file.h"
#include "block.h"

//�}�N��
//�ق��ق�

//�O���[�o��
D3DXVECTOR3 g_posCamera;	//�J�����ʒu

//========================
//����������
//========================
void InitCamera(void)
{
	//�ϐ�������
	g_posCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================
//�I������
//========================
void UninitCamera(void)
{
	//�ϐ�������
	g_posCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================
//�X�V����
//========================
void UpdateCamera(void)
{
	Player *pPlayer = GetPlayer();	//�v���C���[�̏��擾

	if (pPlayer->pos.x - g_posCamera.x <= CAMERA_MOVEX || pPlayer->pos.x - g_posCamera.x >= SCREEN_WIDTH - CAMERA_MOVEX)
	{
		g_posCamera.x += pPlayer->pos.x - pPlayer->posOld.x;
		if (pPlayer->pos.x <= CAMERA_MOVEX)
		{
			g_posCamera.x = 0.0f;
		}
		else if (pPlayer->pos.x >= GetMapData()->blockData.nMapWidth * BLOCK_WIDTH - CAMERA_MOVEX)
		{
			g_posCamera.x = (float)GetMapData()->blockData.nMapWidth * BLOCK_WIDTH - SCREEN_WIDTH;
		}
	}
}

//========================
//�J�����ʒu�擾����
//========================
D3DXVECTOR3 GetCameraPos(void)
{
	return g_posCamera;
}