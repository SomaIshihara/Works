//==========================================
//
//ファイル読み込みプログラム[file.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "file.h"
#include <stdio.h>
#include <assert.h>

//マクロ
//マップ
#define MAP_PATH	"data\\CSV\\Map.csv"
#define HSCORE_PATH	"data\\HScore.bin"

//セーブデータ
//ほげほげ

//コード関係
#define CODE_LENGTH	(1024)

//グローバル
MapData g_ReadMap;
bool g_bSkipCr;

//========================
//ファイル初期化処理
//========================
void InitFile()
{
	g_ReadMap = {};
	LoadMapFile();
}

//========================
//ファイル終了処理
//========================
void UninitFile(void)
{
	//一旦なし
}

//========================
//ファイル更新処理
//========================
void UpdateFile(void)
{
	//一旦なし
}

//========================
//マップ・敵読み込み処理（CSV）
//========================
void LoadMapFile(void)
{
	FILE *pFile;
	int nCntInit = 0;	//初期化カウンタ
	int nCntReadX, nCntReadY;		//読み込みカウンタ
	char aCode[CODE_LENGTH], aClone[CODE_LENGTH];
	char *pSprit;

	//読み込みファイル設定
	pFile = fopen(MAP_PATH, "r");

	//敵配置情報を取得
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &aCode[0]);
		pSprit = strtok(&aCode[0], ",");
		assert(pSprit != NULL);
		if (strcmp(&aCode[0], CODE_START) == 0)
		{
			nCntInit++;
			while (1)
			{
				fscanf(pFile, "%s", &aCode[0]);
				pSprit = strtok(&aCode[0], ",");
				assert(pSprit != NULL);
				if (strcmp(pSprit, CODE_END) == 0)
				{
					break;
				}
				else if (strcmp(pSprit, CODE_STARTBLOCK) == 0)
				{
					for (nCntReadY = 0; nCntReadY < MAP_HEIGHT; nCntReadY++)
					{
						//1行読み取り
						fscanf(pFile, "%s", &aCode[0]);
						strcpy(&aClone[0], &aCode[0]);	//クローン生成
						pSprit = strtok(&aClone[0], ",");

						//EndBlockが来たら終了
						if (strcmp(pSprit, CODE_ENDBLOCK) == 0)
						{
							g_ReadMap.blockData.nMapHeight = nCntReadY;
							break;
						}
						else
						{
							//1列目取得
							pSprit = strtok(&aCode[0], ",");
							if (pSprit == NULL)
							{//文字がなくなったら1行終了
								if (nCntReadY == 0)
								{//最初の行なら
									g_ReadMap.blockData.nMapWidth = 0;
								}
								break;
							}

							//代入
							g_ReadMap.blockData.blockType[nCntReadY][0] = (BLOCKTYPE)atoi(pSprit);

							//2列目以降取得・代入
							for (nCntReadX = 1; nCntReadX < MAP_WIDTH; nCntReadX++)
							{
								pSprit = strtok(NULL, ",");
								if (pSprit == NULL)
								{//文字がなくなったら1行終了
									if (nCntReadY == 0)
									{//最初の行なら
										g_ReadMap.blockData.nMapWidth = nCntReadX;
									}
									break;
								}
								g_ReadMap.blockData.blockType[nCntReadY][nCntReadX] = (BLOCKTYPE)atoi(pSprit);
							}
							if (nCntReadY == 0 && nCntReadX == MAP_WIDTH)
							{//最初の行で列全部使ったなら
								g_ReadMap.blockData.nMapWidth = nCntReadX;
							}
						}
					}
					if (nCntReadY == MAP_HEIGHT)
					{//行全部使った
						g_ReadMap.blockData.nMapHeight = nCntReadY;
					}
				}
				else if (strcmp(pSprit, CODE_STARTENEMY) == 0)
				{
					for (nCntReadY = 0; nCntReadY < MAX_ENEMY; nCntReadY++)
					{
						//1行読み取り
						fscanf(pFile, "%s", &aCode[0]);
						strcpy(&aClone[0], &aCode[0]);	//クローン生成
						pSprit = strtok(&aClone[0], ",");

						//終了チェック
						if (strcmp(pSprit, CODE_ENDENEMY) == 0)
						{
							break;
						}

						//読み取り
						pSprit = strtok(&aCode[0], ",");
						assert(pSprit != NULL);
						g_ReadMap.EnemyData[nCntReadY].pos.x = (float)atof(pSprit);
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.EnemyData[nCntReadY].pos.y = (float)atof(pSprit);
						g_ReadMap.EnemyData[nCntReadY].pos.z = 0.0f;
						g_ReadMap.EnemyData[nCntReadY].posOld = g_ReadMap.EnemyData[nCntReadY].pos;
						g_ReadMap.EnemyData[nCntReadY].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						g_ReadMap.EnemyData[nCntReadY].nDirectionMove = 1;
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.EnemyData[nCntReadY].fWidth = (float)atof(pSprit);//読み取り
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.EnemyData[nCntReadY].fHeight = (float)atof(pSprit);//読み取り
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.EnemyData[nCntReadY].Type = (ENEMYTYPE)atoi(pSprit);//読み取り
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.EnemyData[nCntReadY].nLife = atoi(pSprit);//読み取り
						g_ReadMap.EnemyData[nCntReadY].state = ENEMYSTATE_NORMAL;
						g_ReadMap.EnemyData[nCntReadY].nCounterState = 0;
						g_ReadMap.EnemyData[nCntReadY].nCounterCT = ENEMYLANDSTATE_FRAME;
						g_ReadMap.EnemyData[nCntReadY].nCounterJumpTime = 0;
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.EnemyData[nCntReadY].nAddScore = atoi(pSprit);//読み取り
						g_ReadMap.EnemyData[nCntReadY].bUse = true;

						//敵位置調整
						g_ReadMap.EnemyData[nCntReadY].pos.x = g_ReadMap.EnemyData[nCntReadY].pos.x * BLOCK_WIDTH;
						g_ReadMap.EnemyData[nCntReadY].pos.y = g_ReadMap.EnemyData[nCntReadY].pos.y * BLOCK_HEIGHT;
					}
					g_ReadMap.nEnemyNum = nCntReadY;
				}
				else if (strcmp(pSprit, CODE_STARTITEM) == 0)
				{
					for (nCntReadY = 0; nCntReadY < MAX_ITEM; nCntReadY++)
					{
						//1行読み取り
						fscanf(pFile, "%s", &aCode[0]);
						strcpy(&aClone[0], &aCode[0]);	//クローン生成
						pSprit = strtok(&aClone[0], ",");

						if (strcmp(pSprit, CODE_ENDITEM) == 0)
						{
							break;
						}

						//読み取り
						pSprit = strtok(&aCode[0], ",");
						assert(pSprit != NULL);
						g_ReadMap.itemData[nCntReadY].pos.x = (float)atof(pSprit) * BLOCK_WIDTH + BLOCK_WIDTH / 2;
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.itemData[nCntReadY].pos.y = (float)atof(pSprit) * BLOCK_HEIGHT + BLOCK_HEIGHT / 2;
						g_ReadMap.itemData[nCntReadY].pos.z = 0.0f;
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.itemData[nCntReadY].nType = (ITEMTYPE)atoi(pSprit);
					}
					g_ReadMap.nItemNum = nCntReadY;
				}
				nCntInit++;
			}
		}
		fclose(pFile);
	}
	else
	{
		assert(pFile != NULL);
	}
}

//========================
//敵配置取得
//========================
MapData *GetMapData(void)
{
	return &g_ReadMap;
}

//========================
//ハイスコア読み込み処理（bin）
//========================
int LoadHScoreFile(void)
{
	int nHScore = 0;		//読み込んだハイスコア
	FILE *pFile;			//ファイルポインタ

	//読み込み
	pFile = fopen(HSCORE_PATH, "rb");

	if (pFile != NULL)
	{
		fread(&nHScore, sizeof(int), 1, pFile);
		fclose(pFile);
	}

	//値を返す
	return nHScore;
}

//========================
//ハイスコア書き込み処理（bin）
//========================
void SaveHScoreFile(int nHScore)
{
	FILE *pFile;			//ファイルポインタ

	//書き込み
	pFile = fopen(HSCORE_PATH, "wb");

	if (pFile != NULL)
	{
		fwrite(&nHScore, sizeof(int), 1, pFile);
		fclose(pFile);
	}
}