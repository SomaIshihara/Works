//==========================================
//
//�}�b�v�v���O����[map.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "map.h"
#include "file.h"
#include "block.h"
#include "camera.h"
#include "item.h"
#include "spot.h"

//========================
//�}�b�v����������
//========================
void InitMap(void)
{
	//�u���b�N�E�A�C�e���E�G������
	InitBlock();
	InitItem();
	InitSpot();
	InitEnemy();

	//�}�b�v�z�u
	SetMap();
}

//========================
//�}�b�v�I������
//========================
void UninitMap(void)
{
	UninitEnemy();
	UninitSpot();
	UninitItem();
	UninitBlock();
}

//========================
//�}�b�v�X�V����
//========================
void UpdateMap(void)
{
	//Prev UpdateKeyboard();
	//�G
	UpdateEnemy();

	//�u���b�N
	UpdateBlock();

	//�A�C�e��
	UpdateItem();

	//�n�_
	UpdateSpot();
	//Next UpdatePlayer();
}

//========================
//�}�b�v�̗ޕ`�揈��
//========================
void DrawMap(void)
{
	//Prev None
	DrawSpot();
	DrawEnemy();
	DrawBlock();
	DrawItem();
	//Next DrawPlayer();
}

//========================
//�}�b�v�̗ސݒ菈��
//========================
void SetMap(void)
{
	Spot StartSpot = { SPOTTYPE_START,D3DXVECTOR3(1.5f * BLOCK_WIDTH,12.0f * BLOCK_HEIGHT,0.0f),0.0f,0.0f,false };
	Spot GoalSpot = { SPOTTYPE_GOAL,D3DXVECTOR3(198.0f * BLOCK_WIDTH,13.0f * BLOCK_HEIGHT,0.0f),96.0f,96.0f,true };
	int nCntSetX, nCntSetY;	//�z�u�J�E���^

	//�}�b�v�ǂݎ��
	MapData *pMapData = GetMapData();

	//�u���b�N�z�u
	for (nCntSetY = 0; nCntSetY < pMapData->blockData.nMapHeight; nCntSetY++)
	{
		for (nCntSetX = 0; nCntSetX < pMapData->blockData.nMapWidth; nCntSetX++)
		{
			SetBlock(D3DXVECTOR3((float)BLOCK_WIDTH / 2 + BLOCK_WIDTH * nCntSetX, (float)BLOCK_HEIGHT / 2 + BLOCK_HEIGHT * nCntSetY, 0.0f) + GetCameraPos(),
				pMapData->blockData.blockType[nCntSetY][nCntSetX], PLACEBLOCK_SYS);
		}
	}

	//�A�C�e���z�u
	for (nCntSetY = 0; nCntSetY < pMapData->nItemNum; nCntSetY++)
	{
		SetItem(pMapData->itemData[nCntSetY].pos, pMapData->itemData[nCntSetY].nType);
	}

	//�G�z�u
	for (nCntSetY = 0; nCntSetY < pMapData->nItemNum; nCntSetY++)
	{
		SetEnemy(pMapData->EnemyData[nCntSetY].pos, pMapData->EnemyData[nCntSetY].fWidth, pMapData->EnemyData[nCntSetY].fHeight,
			pMapData->EnemyData[nCntSetY].Type, pMapData->EnemyData[nCntSetY].nLife, pMapData->EnemyData[nCntSetY].nAddScore);
	}
	SetSpot(StartSpot);
	SetSpot(GoalSpot);
}

//========================
//�}�b�v�̗ރ��Z�b�g����
//========================
void ResetMap(void)
{
	ResetBlock();
	ResetItem();
	ResetSpot();
	ResetEnemy();
}