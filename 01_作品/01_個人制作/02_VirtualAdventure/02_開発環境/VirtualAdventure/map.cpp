//==========================================
//
//マッププログラム[map.cpp]
//Author:石原颯馬
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
//マップ初期化処理
//========================
void InitMap(void)
{
	//ブロック・アイテム・敵初期化
	InitBlock();
	InitItem();
	InitSpot();
	InitEnemy();

	//マップ配置
	SetMap();
}

//========================
//マップ終了処理
//========================
void UninitMap(void)
{
	UninitEnemy();
	UninitSpot();
	UninitItem();
	UninitBlock();
}

//========================
//マップ更新処理
//========================
void UpdateMap(void)
{
	//Prev UpdateKeyboard();
	//敵
	UpdateEnemy();

	//ブロック
	UpdateBlock();

	//アイテム
	UpdateItem();

	//地点
	UpdateSpot();
	//Next UpdatePlayer();
}

//========================
//マップの類描画処理
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
//マップの類設定処理
//========================
void SetMap(void)
{
	Spot StartSpot = { SPOTTYPE_START,D3DXVECTOR3(1.5f * BLOCK_WIDTH,12.0f * BLOCK_HEIGHT,0.0f),0.0f,0.0f,false };
	Spot GoalSpot = { SPOTTYPE_GOAL,D3DXVECTOR3(198.0f * BLOCK_WIDTH,13.0f * BLOCK_HEIGHT,0.0f),96.0f,96.0f,true };
	int nCntSetX, nCntSetY;	//配置カウンタ

	//マップ読み取り
	MapData *pMapData = GetMapData();

	//ブロック配置
	for (nCntSetY = 0; nCntSetY < pMapData->blockData.nMapHeight; nCntSetY++)
	{
		for (nCntSetX = 0; nCntSetX < pMapData->blockData.nMapWidth; nCntSetX++)
		{
			SetBlock(D3DXVECTOR3((float)BLOCK_WIDTH / 2 + BLOCK_WIDTH * nCntSetX, (float)BLOCK_HEIGHT / 2 + BLOCK_HEIGHT * nCntSetY, 0.0f) + GetCameraPos(),
				pMapData->blockData.blockType[nCntSetY][nCntSetX], PLACEBLOCK_SYS);
		}
	}

	//アイテム配置
	for (nCntSetY = 0; nCntSetY < pMapData->nItemNum; nCntSetY++)
	{
		SetItem(pMapData->itemData[nCntSetY].pos, pMapData->itemData[nCntSetY].nType);
	}

	//敵配置
	for (nCntSetY = 0; nCntSetY < pMapData->nItemNum; nCntSetY++)
	{
		SetEnemy(pMapData->EnemyData[nCntSetY].pos, pMapData->EnemyData[nCntSetY].fWidth, pMapData->EnemyData[nCntSetY].fHeight,
			pMapData->EnemyData[nCntSetY].Type, pMapData->EnemyData[nCntSetY].nLife, pMapData->EnemyData[nCntSetY].nAddScore);
	}
	SetSpot(StartSpot);
	SetSpot(GoalSpot);
}

//========================
//マップの類リセット処理
//========================
void ResetMap(void)
{
	ResetBlock();
	ResetItem();
	ResetSpot();
	ResetEnemy();
}