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
#define MAP_PATH	"data\\CSV\\Map.csv"
#define HSCORE_PATH	"data\\HScore.bin"

//�Z�[�u�f�[�^
//�ق��ق�

//�R�[�h�֌W
#define CODE_LENGTH	(1024)

//�O���[�o��
MapData g_ReadMap;
bool g_bSkipCr;

//========================
//�t�@�C������������
//========================
void InitFile()
{
	g_ReadMap = {};
	LoadMapFile();
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
void LoadMapFile(void)
{
	FILE *pFile;
	int nCntInit = 0;	//�������J�E���^
	int nCntReadX, nCntReadY;		//�ǂݍ��݃J�E���^
	char aCode[CODE_LENGTH], aClone[CODE_LENGTH];
	char *pSprit;

	//�ǂݍ��݃t�@�C���ݒ�
	pFile = fopen(MAP_PATH, "r");

	//�G�z�u�����擾
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
						//1�s�ǂݎ��
						fscanf(pFile, "%s", &aCode[0]);
						strcpy(&aClone[0], &aCode[0]);	//�N���[������
						pSprit = strtok(&aClone[0], ",");

						//EndBlock��������I��
						if (strcmp(pSprit, CODE_ENDBLOCK) == 0)
						{
							g_ReadMap.blockData.nMapHeight = nCntReadY;
							break;
						}
						else
						{
							//1��ڎ擾
							pSprit = strtok(&aCode[0], ",");
							if (pSprit == NULL)
							{//�������Ȃ��Ȃ�����1�s�I��
								if (nCntReadY == 0)
								{//�ŏ��̍s�Ȃ�
									g_ReadMap.blockData.nMapWidth = 0;
								}
								break;
							}

							//���
							g_ReadMap.blockData.blockType[nCntReadY][0] = (BLOCKTYPE)atoi(pSprit);

							//2��ڈȍ~�擾�E���
							for (nCntReadX = 1; nCntReadX < MAP_WIDTH; nCntReadX++)
							{
								pSprit = strtok(NULL, ",");
								if (pSprit == NULL)
								{//�������Ȃ��Ȃ�����1�s�I��
									if (nCntReadY == 0)
									{//�ŏ��̍s�Ȃ�
										g_ReadMap.blockData.nMapWidth = nCntReadX;
									}
									break;
								}
								g_ReadMap.blockData.blockType[nCntReadY][nCntReadX] = (BLOCKTYPE)atoi(pSprit);
							}
							if (nCntReadY == 0 && nCntReadX == MAP_WIDTH)
							{//�ŏ��̍s�ŗ�S���g�����Ȃ�
								g_ReadMap.blockData.nMapWidth = nCntReadX;
							}
						}
					}
					if (nCntReadY == MAP_HEIGHT)
					{//�s�S���g����
						g_ReadMap.blockData.nMapHeight = nCntReadY;
					}
				}
				else if (strcmp(pSprit, CODE_STARTENEMY) == 0)
				{
					for (nCntReadY = 0; nCntReadY < MAX_ENEMY; nCntReadY++)
					{
						//1�s�ǂݎ��
						fscanf(pFile, "%s", &aCode[0]);
						strcpy(&aClone[0], &aCode[0]);	//�N���[������
						pSprit = strtok(&aClone[0], ",");

						//�I���`�F�b�N
						if (strcmp(pSprit, CODE_ENDENEMY) == 0)
						{
							break;
						}

						//�ǂݎ��
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
						g_ReadMap.EnemyData[nCntReadY].fWidth = (float)atof(pSprit);//�ǂݎ��
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.EnemyData[nCntReadY].fHeight = (float)atof(pSprit);//�ǂݎ��
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.EnemyData[nCntReadY].Type = (ENEMYTYPE)atoi(pSprit);//�ǂݎ��
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.EnemyData[nCntReadY].nLife = atoi(pSprit);//�ǂݎ��
						g_ReadMap.EnemyData[nCntReadY].state = ENEMYSTATE_NORMAL;
						g_ReadMap.EnemyData[nCntReadY].nCounterState = 0;
						g_ReadMap.EnemyData[nCntReadY].nCounterCT = ENEMYLANDSTATE_FRAME;
						g_ReadMap.EnemyData[nCntReadY].nCounterJumpTime = 0;
						pSprit = strtok(NULL, ",");
						assert(pSprit != NULL);
						g_ReadMap.EnemyData[nCntReadY].nAddScore = atoi(pSprit);//�ǂݎ��
						g_ReadMap.EnemyData[nCntReadY].bUse = true;

						//�G�ʒu����
						g_ReadMap.EnemyData[nCntReadY].pos.x = g_ReadMap.EnemyData[nCntReadY].pos.x * BLOCK_WIDTH;
						g_ReadMap.EnemyData[nCntReadY].pos.y = g_ReadMap.EnemyData[nCntReadY].pos.y * BLOCK_HEIGHT;
					}
					g_ReadMap.nEnemyNum = nCntReadY;
				}
				else if (strcmp(pSprit, CODE_STARTITEM) == 0)
				{
					for (nCntReadY = 0; nCntReadY < MAX_ITEM; nCntReadY++)
					{
						//1�s�ǂݎ��
						fscanf(pFile, "%s", &aCode[0]);
						strcpy(&aClone[0], &aCode[0]);	//�N���[������
						pSprit = strtok(&aClone[0], ",");

						if (strcmp(pSprit, CODE_ENDITEM) == 0)
						{
							break;
						}

						//�ǂݎ��
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
//�G�z�u�擾
//========================
MapData *GetMapData(void)
{
	return &g_ReadMap;
}

//========================
//�n�C�X�R�A�ǂݍ��ݏ����ibin�j
//========================
int LoadHScoreFile(void)
{
	int nHScore = 0;		//�ǂݍ��񂾃n�C�X�R�A
	FILE *pFile;			//�t�@�C���|�C���^

	//�ǂݍ���
	pFile = fopen(HSCORE_PATH, "rb");

	if (pFile != NULL)
	{
		fread(&nHScore, sizeof(int), 1, pFile);
		fclose(pFile);
	}

	//�l��Ԃ�
	return nHScore;
}

//========================
//�n�C�X�R�A�������ݏ����ibin�j
//========================
void SaveHScoreFile(int nHScore)
{
	FILE *pFile;			//�t�@�C���|�C���^

	//��������
	pFile = fopen(HSCORE_PATH, "wb");

	if (pFile != NULL)
	{
		fwrite(&nHScore, sizeof(int), 1, pFile);
		fclose(pFile);
	}
}