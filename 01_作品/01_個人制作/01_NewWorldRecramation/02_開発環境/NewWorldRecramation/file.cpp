//==========================================
//
//�t�@�C���ǂݍ��݃v���O����[file.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "file.h"
#include <stdio.h>
#include <assert.h>

//�}�N��
//�}�b�v
#define MAP_TIMEATTACK_PATH	"data\\CSV\\EnemyData_TA.csv"
#define MAP_STG1_PATH		"data\\CSV\\EnemyData_STG1.csv"
#define MAP_STG2_PATH		"data\\CSV\\EnemyData_STG2.csv"
#define MAP_STG3_PATH		"data\\CSV\\EnemyData_STG3.csv"
#define MAP_STG4_PATH		"data\\CSV\\EnemyData_STG4.csv"
#define MAP_STGL_PATH		"data\\CSV\\EnemyData_STGLast.csv"

//�G���
#define ENEMYSTAT_PATH		"data\\CSV\\EnemyStat.csv"

//�Z�[�u�f�[�^
#define STORYSCORE_PATH		"data\\SAVES\\StoryScore.bin"
#define RANKSCORE_PATH		"data\\SAVES\\RankScore.bin"

//�R�[�h�֌W
#define CODE_LENGTH	(128)

//�X�L�b�v�p�X
#define SKIP_PASS	(321)

//�O���[�o��
MapData g_ReadMap[READMAP_CODENUM];
EnemyStat g_enemyStatData[ENEMY_TYPE];
bool g_bSkipCr;

//========================
//�t�@�C������������
//========================
void InitFile()
{
	int nCntInit;	//�������J�E���^

	//������
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
//�t�@�C���I������
//========================
void UninitFile(void)
{
	//��U�Ȃ�
}

//========================
//�t�@�C���X�V����
//========================
void UpdateFile(void)
{
	//��U�Ȃ�
}

//========================
//�}�b�v�E�G�ǂݍ��ݏ����iCSV�j
//========================
void LoadMapEnemyFile(void)
{
	FILE *pFile;
	int nCntInit = 0;	//�������J�E���^
	char aCode[CODE_LENGTH];
	char *pSprit;
	char aFilePath[128] = "hoge";	//�t�@�C���p�X�i�[

	//�ǂݍ��݃t�@�C���ݒ�
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

	//�G�z�u�����擾
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
					g_ReadMap[nCntInit].startPos.x = (float)atof(pSprit);		//�N���ʒu
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].startPos.y = (float)atof(pSprit);		//�N���ʒu
					g_ReadMap[nCntInit].startPos.z = 0.0f;
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nButtlePosTime = atoi(pSprit);	//�퓬�ʒu�ړ�����
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].buttlePos.x = (float)atof(pSprit);		//�퓬�ʒu
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].buttlePos.y = (float)atof(pSprit);
					g_ReadMap[nCntInit].buttlePos.z = 0.0f;
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nButtleTime = atoi(pSprit);		//�퓬����
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].returnPos.x = (float)atof(pSprit);		//�A��ꏊ
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].returnPos.y = (float)atof(pSprit);
					g_ReadMap[nCntInit].returnPos.z = 0.0f;
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nReturnPosTime = atoi(pSprit);	//�A���
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nType = atoi(pSprit);			//���
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].moveType = (MOVETYPE)atoi(pSprit);			//�ړ��^�C�v
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
					g_ReadMap[nCntInit].DZPos.x = (float)atof(pSprit);		//�_���[�W�]�[�����S���WX
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].DZPos.y = (float)atof(pSprit);		//�_���[�W�]�[�����S���WY
					g_ReadMap[nCntInit].DZPos.z = 0.0f;
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].fWidth = (float)atof(pSprit);		//�_���[�W�]�[����
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].fHeight = (float)atof(pSprit);		//�_���[�W�]�[������
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
					g_ReadMap[nCntInit].nBGMNumber = atoi(pSprit);		//BGM�ԍ�
				}
				else if (strcmp(&aCode[0], CODE_SETSPEED) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nSpeed = atoi(pSprit);			//�X�s�[�h
				}
				else if (strcmp(&aCode[0], CODE_SWITCHSKIP) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);	//�v�f�Ȃ��̂��߃R�[�h�̂ݑ��
				}
				else if (strcmp(&aCode[0], CODE_SETITEM) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nItemtype = atoi(pSprit);			//�A�C�e���̎��
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].startPos.x = (float)atof(pSprit);		//�N���ʒuX
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].startPos.y = (float)atof(pSprit);		//�N���ʒuY
					g_ReadMap[nCntInit].startPos.z = 0.0f;
				}
				else if (strcmp(&aCode[0], CODE_DEFBGMTIME) == 0)
				{
					strcpy(&g_ReadMap[nCntInit].aCode[0], &aCode[0]);
					pSprit = strtok(NULL, ",");
					assert(pSprit != NULL);
					g_ReadMap[nCntInit].nBGMTime = atoi(pSprit) * 60;			//BGM����
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

	//�G�X�e�[�^�X�ǂݎ��
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
					g_enemyStatData[nCntInit].nEnemyNum = atoi(pSprit);		//�G�ԍ�
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
//�X�g�[���[�X�R�A�ǂݍ��ݏ����ibin�j
//========================
void LoadStoryScoreFile(int *pScore, int *nOpenStage)
{
	FILE *pFile;	//�t�@�C���|�C���^

	//�ǂݍ���
	pFile = fopen(STORYSCORE_PATH, "rb");

	if (pFile != NULL)
	{
		fread(pScore, sizeof(int), STAGE_NUM, pFile);
		fread(nOpenStage, sizeof(int), 1, pFile);
		fclose(pFile);
	}
}

//========================
//�X�g�[���[�X�R�A�������ݏ����ibin�j
//========================
void SaveStoryScoreFile(int *pScore, int nOpenStage)
{
	FILE *pFile;	//�t�@�C���|�C���^

	//��������
	pFile = fopen(STORYSCORE_PATH, "wb");

	if (pFile != NULL)
	{
		fwrite(pScore, sizeof(int), STAGE_NUM, pFile);
		fwrite(&nOpenStage, sizeof(int), 1, pFile);
		fclose(pFile);
	}
}

//========================
//�����L���O�ǂݍ��ݏ����ibin�j
//========================
void LoadRankingFile(Ranking *rank)
{
	int nCntScore;			//�J�E���^
	int aScore[MAX_RANK];	//rank�̃X�R�A�����̂ݒ��o�������̂��i�[
	FILE *pFile;			//�t�@�C���|�C���^

	//�ǂݍ���
	pFile = fopen(RANKSCORE_PATH, "rb");

	if (pFile != NULL)
	{
		fread(&aScore[0], sizeof(int), MAX_RANK, pFile);
		fclose(pFile);

		//���
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
//�����L���O�������ݏ����ibin�j
//========================
void SaveRankingFile(Ranking *rank)
{
	int nCntScore;			//�J�E���^
	int aScore[MAX_RANK];	//rank�̃X�R�A�����̂ݒ��o�������̂��i�[
	FILE *pFile;			//�t�@�C���|�C���^

	//���o
	for (nCntScore = 0; nCntScore < MAX_RANK; nCntScore++, rank++)
	{
		aScore[nCntScore] = rank->nScore;
	}

	//��������
	pFile = fopen(RANKSCORE_PATH, "wb");

	if (pFile != NULL)
	{
		fwrite(&aScore[0], sizeof(int), MAX_RANK, pFile);
		fclose(pFile);
	}
}

//========================
//�G�z�u�擾
//========================
int GetMapData(MapData *pMapData)
{
	int nCntSetData = 0;
	int nCounterTotalEnemy = 0;
	while(1)
	{
		//�}�b�v�f�[�^�i�[
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

		//�A�h���X�ړ�
		pMapData++;

		if (strcmp(&g_ReadMap[nCntSetData].aCode[0], CODE_END) == 0)
		{//�I���R�[�h
			break;
		}
		else if (strcmp(&g_ReadMap[nCntSetData].aCode[0], CODE_SETENEMY) == 0)
		{//�G�ݒ�R�[�h
			nCounterTotalEnemy++;
		}
		nCntSetData++;
	}

	return nCounterTotalEnemy;
}

//========================
//�G���擾
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
//�G�ԍ��ɉ����ă^�C�v��Ԃ�
//========================
int RefEnemyType(int nEnemyNum)
{
	return g_enemyStatData[nEnemyNum].nEnemyType;
}

//========================
//�X�L�b�v���邩�ۂ���Ԃ�
//========================
bool GetSkip(void)
{
	FILE *pFile;	//�t�@�C���|�C���^

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