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
#define MAP_TIMEATTACK_PATH	"data\\CSV\\EnemyData_TA.csv"
#define MAP_STG1_PATH		"data\\CSV\\EnemyData_STG1.csv"
#define MAP_STG2_PATH		"data\\CSV\\EnemyData_STG2.csv"
#define MAP_STG3_PATH		"data\\CSV\\EnemyData_STG3.csv"
#define MAP_STG4_PATH		"data\\CSV\\EnemyData_STG4.csv"
#define MAP_STGL_PATH		"data\\CSV\\EnemyData_STGLast.csv"

//敵情報
#define ENEMYSTAT_PATH		"data\\CSV\\EnemyStat.csv"

//セーブデータ
#define STORYSCORE_PATH		"data\\SAVES\\StoryScore.bin"
#define RANKSCORE_PATH		"data\\SAVES\\RankScore.bin"

//コード関係
#define CODE_LENGTH	(128)

//スキップパス
#define SKIP_PASS	(321)

//グローバル
MapData g_ReadMap[READMAP_CODENUM];
EnemyStat g_enemyStatData[ENEMY_TYPE];
bool g_bSkipCr;

//========================
//ファイル初期化処理
//========================
void InitFile()
{
	int nCntInit;	//初期化カウンタ

	//初期化
	for (nCntInit = 0; nCntInit < MAX_ENEMY; nCntInit++)
	{
		g_ReadMap[nCntInit] = {};
	}
	for (nCntInit = 0; nCntInit < ENEMY_TYPE; nCntInit++)
	{
		g_enemyStatData[nCntInit] = {};
	}
	nCntInit = 0;
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
void LoadMapEnemyFile(void)
{
	FILE *pFile;
	int nCntInit = 0;	//初期化カウンタ
	char aCode[CODE_LENGTH];
	char *pSprit;
	char aFilePath[128] = "hoge";	//ファイルパス格納

	//読み込みファイル設定
	switch (GetStage())
	{
	case STAGE_TIMEATTACK:
		strcpy(&aFilePath[0], MAP_TIMEATTACK_PATH);
		break;

	case STAGE_1:
		strcpy(&aFilePath[0], MAP_STG1_PATH);
		break;
	case STAGE_2:
		strcpy(&aFilePath[0], MAP_STG2_PATH);
		break;
	case STAGE_3:
		strcpy(&aFilePath[0], MAP_STG3_PATH);
		break;
	case STAGE_4:
		strcpy(&aFilePath[0], MAP_STG4_PATH);
		break;
	case STAGE_LAST:
		strcpy(&aFilePath[0], MAP_STGL_PATH);
		break;
	}
	pFile = fopen(aFilePath, "r");

	//敵配置情報を取得
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &aCode[0]);
		pSprit = strtok(&aCode[0], ",");
		assert(pSprit != NULL);
		if (strcmp(&aCode[0], CODE_START) == 0)
		{
			strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
			nCntInit++;
			while (1)
			{
				fscanf(pFile, "%s", &aCode[0]);
				pSprit = strtok(&aCode[0], ",");
				assert(pSprit != NULL);
				if (strcmp(&aCode[0], CODE_END) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
					break;
				}
				else if (strcmp(&aCode[0], CODE_SETENEMY) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].startPos.x = (float)atof(pSprit);		//湧き位置
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].startPos.y = (float)atof(pSprit);		//湧き位置
					g_ReadMap[nCntInit].startPos.z = 0.0f;
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nButtlePosTime = atoi(pSprit);	//戦闘位置移動時間
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].buttlePos.x = (float)atof(pSprit);		//戦闘位置
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].buttlePos.y = (float)atof(pSprit);
					g_ReadMap[nCntInit].buttlePos.z = 0.0f;
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nButtleTime = atoi(pSprit);		//戦闘時間
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].returnPos.x = (float)atof(pSprit);		//帰宅場所
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].returnPos.y = (float)atof(pSprit);
					g_ReadMap[nCntInit].returnPos.z = 0.0f;
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nReturnPosTime = atoi(pSprit);	//帰宅時間
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nType = atoi(pSprit);			//種類
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].moveType = (MOVETYPE)atoi(pSprit);			//移動タイプ
				}
				else if (strcmp(&aCode[0], CODE_WAIT) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nWaitTime = atoi(pSprit);
				}
				else if (strcmp(&aCode[0], CODE_SETDZ) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].DZPos.x = (float)atof(pSprit);		//ダメージゾーン中心座標X
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].DZPos.y = (float)atof(pSprit);		//ダメージゾーン中心座標Y
					g_ReadMap[nCntInit].DZPos.z = 0.0f;
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].fWidth = (float)atof(pSprit);		//ダメージゾーン幅
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].fHeight = (float)atof(pSprit);		//ダメージゾーン高さ
				}
				else if (strcmp(&aCode[0], CODE_KILL) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
				}
				else if (strcmp(&aCode[0], CODE_SETBGM) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nBGMNumber = atoi(pSprit);		//BGM番号
				}
				else if (strcmp(&aCode[0], CODE_SETSPEED) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nSpeed = atoi(pSprit);			//スピード
				}
				else if (strcmp(&aCode[0], CODE_SWITCHSKIP) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);	//要素なしのためコードのみ代入
				}
				else if (strcmp(&aCode[0], CODE_SETITEM) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nItemtype = atoi(pSprit);			//アイテムの種類
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].startPos.x = (float)atof(pSprit);		//湧き位置X
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].startPos.y = (float)atof(pSprit);		//湧き位置Y
					g_ReadMap[nCntInit].startPos.z = 0.0f;
				}
				else if (strcmp(&aCode[0], CODE_DEFBGMTIME) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nBGMTime = atoi(pSprit) * 60;			//BGM時間
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

	//敵ステータス読み取り
	nCntInit = 0;
	pFile = fopen(ENEMYSTAT_PATH, "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &aCode[0]);
		pSprit = strtok(&aCode[0], ",");
		assert(pSprit != NULL);
		if (strcmp(&aCode[0], CODE_START) == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aCode[0]);
				pSprit = strtok(&aCode[0], ",");
				assert(pSprit != NULL);
				if (strcmp(&aCode[0], CODE_END) == 0)
				{
					break;
				}
				else if (strcmp(pSprit, CODE_DEFENEMYSTAT) == 0)
				{
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_enemyStatData[nCntInit].nEnemyNum = atoi(pSprit);		//敵番号
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_enemyStatData[nCntInit].nEnemyType = atoi(pSprit);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_enemyStatData[nCntInit].nWidth = atoi(pSprit);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_enemyStatData[nCntInit].nHeight = atoi(pSprit);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_enemyStatData[nCntInit].nFiringCT = atoi(pSprit);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_enemyStatData[nCntInit].nLife = atoi(pSprit);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_enemyStatData[nCntInit].nAddScore = atoi(pSprit);
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
//ストーリースコア読み込み処理（bin）
//========================
void LoadStoryScoreFile(int *pScore, int *nOpenStage)
{
	FILE *pFile;	//ファイルポインタ

	//読み込み
	pFile = fopen(STORYSCORE_PATH, "rb");

	if (pFile != NULL)
	{
		fread(pScore, sizeof(int), STAGE_NUM, pFile);
		fread(nOpenStage, sizeof(int), 1, pFile);
		fclose(pFile);
	}
}

//========================
//ストーリースコア書き込み処理（bin）
//========================
void SaveStoryScoreFile(int *pScore, int nOpenStage)
{
	FILE *pFile;	//ファイルポインタ

	//書き込み
	pFile = fopen(STORYSCORE_PATH, "wb");

	if (pFile != NULL)
	{
		fwrite(pScore, sizeof(int), STAGE_NUM, pFile);
		fwrite(&nOpenStage, sizeof(int), 1, pFile);
		fclose(pFile);
	}
}

//========================
//ランキング読み込み処理（bin）
//========================
void LoadRankingFile(Ranking *rank)
{
	int nCntScore;			//カウンタ
	int aScore[MAX_RANK];	//rankのスコア部分のみ抽出したものを格納
	FILE *pFile;			//ファイルポインタ

	//読み込み
	pFile = fopen(RANKSCORE_PATH, "rb");

	if (pFile != NULL)
	{
		fread(&aScore[0], sizeof(int), MAX_RANK, pFile);
		fclose(pFile);

		//代入
		for (nCntScore = 0; nCntScore < MAX_RANK; nCntScore++, rank++)
		{
			rank->nScore = aScore[nCntScore];
		}
	}
	else
	{
		SaveRankingFile(rank);
	}
}

//========================
//ランキング書き込み処理（bin）
//========================
void SaveRankingFile(Ranking *rank)
{
	int nCntScore;			//カウンタ
	int aScore[MAX_RANK];	//rankのスコア部分のみ抽出したものを格納
	FILE *pFile;			//ファイルポインタ

	//抽出
	for (nCntScore = 0; nCntScore < MAX_RANK; nCntScore++, rank++)
	{
		aScore[nCntScore] = rank->nScore;
	}

	//書き込み
	pFile = fopen(RANKSCORE_PATH, "wb");

	if (pFile != NULL)
	{
		fwrite(&aScore[0], sizeof(int), MAX_RANK, pFile);
		fclose(pFile);
	}
}

//========================
//敵配置取得
//========================
int GetMapData(MapData *pMapData)
{
	int nCntSetData = 0;
	int nCounterTotalEnemy = 0;
	while(1)
	{
		//マップデータ格納
		strcpy(&pMapData->aCode[0], &g_ReadMap[nCntSetData].aCode[0]);
		pMapData->startPos = g_ReadMap[nCntSetData].startPos;
		pMapData->nButtlePosTime = g_ReadMap[nCntSetData].nButtlePosTime;
		pMapData->buttlePos = g_ReadMap[nCntSetData].buttlePos;
		pMapData->nButtleTime = g_ReadMap[nCntSetData].nButtleTime;
		pMapData->returnPos = g_ReadMap[nCntSetData].returnPos;
		pMapData->nReturnPosTime = g_ReadMap[nCntSetData].nReturnPosTime;
		pMapData->nType = g_ReadMap[nCntSetData].nType;
		pMapData->moveType = g_ReadMap[nCntSetData].moveType;
		pMapData->nWaitTime = g_ReadMap[nCntSetData].nWaitTime;
		pMapData->DZPos = g_ReadMap[nCntSetData].DZPos;
		pMapData->fWidth = g_ReadMap[nCntSetData].fWidth;
		pMapData->fHeight = g_ReadMap[nCntSetData].fHeight;
		pMapData->fRazerPosX = g_ReadMap[nCntSetData].fRazerPosX;
		pMapData->nRazerChargeTime = g_ReadMap[nCntSetData].nRazerChargeTime;
		pMapData->nBGMNumber = g_ReadMap[nCntSetData].nBGMNumber;
		pMapData->nSpeed = g_ReadMap[nCntSetData].nSpeed;
		pMapData->nItemtype = g_ReadMap[nCntSetData].nItemtype;
		pMapData->nBGMTime = g_ReadMap[nCntSetData].nBGMTime;

		//アドレス移動
		pMapData++;

		if (strcmp(&g_ReadMap[nCntSetData].aCode[0], CODE_END) == 0)
		{//終了コード
			break;
		}
		else if (strcmp(&g_ReadMap[nCntSetData].aCode[0], CODE_SETENEMY) == 0)
		{//敵設定コード
			nCounterTotalEnemy++;
		}
		nCntSetData++;
	}

	return nCounterTotalEnemy;
}

//========================
//敵情報取得
//========================
void GetEnemyStat(EnemyStat *pEnemyStat)
{
	int nCntEnemyStat;
	for (nCntEnemyStat = 0; nCntEnemyStat < ENEMY_TYPE; nCntEnemyStat++, pEnemyStat++)
	{
		pEnemyStat->nEnemyNum = g_enemyStatData[nCntEnemyStat].nEnemyNum;
		pEnemyStat->nEnemyType = g_enemyStatData[nCntEnemyStat].nEnemyType;
		pEnemyStat->nWidth = g_enemyStatData[nCntEnemyStat].nWidth;
		pEnemyStat->nHeight = g_enemyStatData[nCntEnemyStat].nHeight;
		pEnemyStat->nFiringCT = g_enemyStatData[nCntEnemyStat].nFiringCT;
		pEnemyStat->nLife = g_enemyStatData[nCntEnemyStat].nLife;
		pEnemyStat->nAddScore = g_enemyStatData[nCntEnemyStat].nAddScore;
	}
}

//========================
//敵番号に応じてタイプを返す
//========================
int RefEnemyType(int nEnemyNum)
{
	return g_enemyStatData[nEnemyNum].nEnemyType;
}

//========================
//スキップするか否かを返す
//========================
bool GetSkip(void)
{
	FILE *pFile;	//ファイルポインタ

	g_bSkipCr = false;

	pFile = fopen("data\\SAVES\\Config.bin", "rb");

	if (pFile != NULL)
	{
		int nCheck;
		fread(&nCheck, sizeof(int), 1, pFile);

		fclose(pFile);

		if (nCheck == SKIP_PASS)
		{
			g_bSkipCr = true;
		}
	}

	return g_bSkipCr;
}