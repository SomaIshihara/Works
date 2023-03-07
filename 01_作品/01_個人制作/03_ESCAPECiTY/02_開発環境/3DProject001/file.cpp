//==========================================
//
//�t�@�C���ǂݍ��݃v���O����[file.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "file.h"
#include "object.h"
#include "enemy.h"
#include <stdio.h>
#include <assert.h>

//�}�N��
//�}�b�v
#define MODELVIEWERDATA_PATH	"data\\model.txt"	//���f���r���[���[�̃f�[�^�̃p�X
#define SETDATA_PATH			"data\\setdata.txt"	//�z�u���Ȃǂ̃f�[�^�̃p�X
#define MOTIONVIEWERDATA_PATH	"data\\motion_exithuman.txt"	//���[�V�����r���[���[�̃f�[�^�̃p�X

//�Z�[�u�f�[�^
//�ق��ق�

//�R�[�h�֌W
#define CODE_LENGTH	(128)

//�ǂݎ���ԗ�
typedef enum
{
	//����
	READSTAT_NONE = 0,	//�������ĂȂ�

	//-���f���r���[���[-----------------------
	READSTAT_CAMERASET,
	READSTAT_LIGHTSET,
	READSTAT_SKYSET,
	READSTAT_MOUNTAINSET,
	READSTAT_FIELDSET,
	READSTAT_WALLSET,
	READSTAT_MODELSET,
	READSTAT_BILLBOARDSET,
	READSTAT_PLAYERSET,
	//----------------------------------------

	//-�z�u���-------------------------------
	READSTAT_SETENEMY,
	//----------------------------------------

	//--���[�V�����r���[���[------------------
	READSTAT_CHARACTERSET,
	READSTAT_PARTSSET,
	READSTAT_MOTIONSET,
	READSTAT_KEYSET,
	READSTAT_KEY,
	//----------------------------------------
	READSTAT_MAX
} READSTAT;

//�O���[�o��
READSTAT g_readStat = READSTAT_NONE;

//�擾��������
int g_nType = 0;
D3DXVECTOR3 g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int g_nState = 0;
bool g_bUseCollision = true;	//�f�t�H���g��true
bool g_bUseShadow = true;		//�f�t�H���g��true
int g_nLife = 0;
MODELNAME g_name = MODELNAME_EXITHUMAN;
MOTION_INFO g_motionInfo[MOTIONTYPE_MAX];
int g_counterKey;
int g_counterKeyInfo;
int g_counterMotionInfo;

//========================
//�t�@�C������������
//========================
void InitFile()
{
	//�ϐ�������
	g_readStat = READSTAT_NONE;
	g_nType = 0;
	g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nState = 0;
	g_bUseCollision = true;		//�f�t�H���g��true
	g_bUseShadow = true;		//�f�t�H���g��true
	g_nLife = 0;
	g_name = MODELNAME_EXITHUMAN;
	g_counterKey = 0;
	g_counterKeyInfo = 0;
	g_counterMotionInfo = 0;
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
//�}�b�v�E�G�ǂݍ��ݏ���
//========================
void LoadMapFile(void)
{
	FILE *pFile;
	char aCode[CODE_LENGTH];
	char *pSprit;
	bool bRead = false;
	int nCntInit = 0;	//�������J�E���^

	//�ǂݍ��݃t�@�C���ݒ�
	pFile = fopen(MODELVIEWERDATA_PATH, "r");

	//�G�z�u�����擾
	if (pFile != NULL)
	{
		while (1)
		{
			fgets(&aCode[0], CODE_LENGTH, pFile);

			//�R�����g�A�E�g�`�F�b�N
			char *pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
				*pCharPos = '\0';
			}

			//�^�u����
			while (aCode[0] == '\t')
			{
				char aCodeBackup[CODE_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//������`�F�b�N
			if (strncmp(&aCode[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��J�n
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��I��
				bRead = false;
				break;
			}
			else if (aCode[0] == EOF)
			{//EOF��������Ȃ�
				if (feof(pFile))
				{//����A�����EOF��
					bRead = false;
					break;
				}
			}
			else if (bRead == true)
			{//�ǂݎ��
				switch (g_readStat)
				{
				case READSTAT_NONE:	//�����擾
					if (strncmp(&aCode[0], CODE_CAMERASET, sizeof CODE_CAMERASET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_CAMERASET;
					}
					if (strncmp(&aCode[0], CODE_LIGHTSET, sizeof CODE_LIGHTSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_LIGHTSET;
					}
					if (strncmp(&aCode[0], CODE_SKYSET, sizeof CODE_SKYSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_SKYSET;
					}
					if (strncmp(&aCode[0], CODE_MOUNTAINSET, sizeof CODE_MOUNTAINSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_MOUNTAINSET;
					}
					if (strncmp(&aCode[0], CODE_FIELDSET, sizeof CODE_FIELDSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_FIELDSET;
					}
					if (strncmp(&aCode[0], CODE_WALLSET, sizeof CODE_WALLSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_WALLSET;
					}
					if (strncmp(&aCode[0], CODE_MODELSET, sizeof CODE_MODELSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_MODELSET;
					}
					if (strncmp(&aCode[0], CODE_BILLBOARDSET, sizeof CODE_BILLBOARDSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_BILLBOARDSET;
					}
					if (strncmp(&aCode[0], CODE_PLAYERSET, sizeof CODE_PLAYERSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_PLAYERSET;
					}
					break;
				case READSTAT_CAMERASET:	//�J�������擾
					if (strncmp(&aCode[0], CODE_END_CAMERASET, sizeof CODE_END_CAMERASET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						
					}
					else if (strncmp(&aCode[0], CODE_REF, sizeof CODE_REF / sizeof(char) - 1) == 0)
					{

					}
					break;
				case READSTAT_LIGHTSET:		//���C�g���擾
					if (strncmp(&aCode[0], CODE_END_LIGHTSET, sizeof CODE_END_LIGHTSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_DIRECTION, sizeof CODE_DIRECTION / sizeof(char) - 1) == 0)
					{
						
					}
					else if (strncmp(&aCode[0], CODE_DIFFUSE, sizeof CODE_DIFFUSE / sizeof(char) - 1) == 0)
					{

					}
					break;
				case READSTAT_SKYSET:		//����擾
					if (strncmp(&aCode[0], CODE_END_SKYSET, sizeof CODE_END_SKYSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{
						
					}
					else if (strncmp(&aCode[0], CODE_MOVE, sizeof CODE_MOVE / sizeof(char) - 1) == 0)
					{

					}
					break;
				case READSTAT_MOUNTAINSET:	//�R���擾
					if (strncmp(&aCode[0], CODE_END_MOUNTAINSET, sizeof CODE_END_MOUNTAINSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{

					}
					break;
				case READSTAT_FIELDSET:		//�����擾
					if (strncmp(&aCode[0], CODE_END_FIELDSET, sizeof CODE_END_FIELDSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_BLOCK, sizeof CODE_BLOCK / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_SIZE, sizeof CODE_SIZE / sizeof(char) - 1) == 0)
					{

					}
					break;
				case READSTAT_WALLSET:		//�Ǐ��擾
					if (strncmp(&aCode[0], CODE_END_WALLSET, sizeof CODE_END_WALLSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_BLOCK, sizeof CODE_BLOCK / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_SIZE, sizeof CODE_SIZE / sizeof(char) - 1) == 0)
					{

					}
					break;
				case READSTAT_MODELSET:		//���f�����擾
					if (strncmp(&aCode[0], CODE_END_MODELSET, sizeof CODE_END_MODELSET / sizeof(char) - 1) == 0)
					{
						SetObject((BLUEPRINTIDX)g_nType, g_pos, g_rot, false, 5);
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TYPE, sizeof CODE_TYPE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//��ޓǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_nType = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_pos.x = (float)atof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_pos.y = (float)atof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_pos.z = (float)atof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_rot.x = ((float)atof(pSprit) / 180) * D3DX_PI;

						//Y���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_rot.y = ((float)atof(pSprit) / 180) * D3DX_PI;

						//Z���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_rot.z = ((float)atof(pSprit) / 180) * D3DX_PI;
					}
					else if (strncmp(&aCode[0], CODE_STATE, sizeof CODE_STATE / sizeof(char) - 1) == 0)
					{//��Ԏw��

					}
					else if (strncmp(&aCode[0], CODE_COLLISION, sizeof CODE_COLLISION / sizeof(char) - 1) == 0)
					{//0�Ȃ瓖���蔻�薳��
						
					}
					else if (strncmp(&aCode[0], CODE_SHADOW, sizeof CODE_SHADOW / sizeof(char) - 1) == 0)
					{//0�Ȃ�e���g�p���Ȃ�

					}
					break;
				case READSTAT_BILLBOARDSET:	//�r���{�[�h���擾
					if (strncmp(&aCode[0], CODE_END_BILLBOARDSET, sizeof CODE_END_BILLBOARDSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_SIZE, sizeof CODE_SIZE / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_ORIGIN, sizeof CODE_ORIGIN / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_BLEND, sizeof CODE_BLEND / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_SHADOW, sizeof CODE_SHADOW / sizeof(char) - 1) == 0)
					{

					}
					break;
				case READSTAT_PLAYERSET:	//�v���C���[���f�����擾
					if (strncmp(&aCode[0], CODE_END_PLAYERSET, sizeof CODE_END_PLAYERSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_MOTION_FILENAME, sizeof CODE_MOTION_FILENAME / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{

					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{

					}
					break;
				}
			}
		}
		
		//�t�@�C������
		fclose(pFile);
	}
	else
	{
		assert(pFile != NULL);
	}

	//�z�u���
	//�ǂݍ��݃t�@�C���ݒ�
	pFile = fopen(SETDATA_PATH, "r");

	//�G�z�u�����擾
	if (pFile != NULL)
	{
		while (1)
		{
			fgets(&aCode[0], CODE_LENGTH, pFile);

			//�R�����g�A�E�g�`�F�b�N
			char *pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
				*pCharPos = '\0';
			}

			//�^�u����
			while (aCode[0] == '\t')
			{
				char aCodeBackup[CODE_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//������`�F�b�N
			if (strncmp(&aCode[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��J�n
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��I��
				bRead = false;
				break;
			}
			else if (aCode[0] == EOF)
			{//EOF��������Ȃ�
				if (feof(pFile))
				{//����A�����EOF��
					bRead = false;
					break;
				}
			}
			else if (bRead == true)
			{//�ǂݎ��
				switch (g_readStat)
				{
				case READSTAT_NONE:	//�����擾
					if (strncmp(&aCode[0], CODE_SETENEMY, sizeof CODE_SETENEMY / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_SETENEMY;
					}
					break;
				case READSTAT_SETENEMY:		//���f�����擾
					if (strncmp(&aCode[0], CODE_END_SETENEMY, sizeof CODE_END_SETENEMY / sizeof(char) - 1) == 0)
					{
						SetEnemy(g_pos, g_rot, g_name, g_nLife);
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_pos.x = (float)atof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_pos.y = (float)atof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_pos.z = (float)atof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

															//X���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_rot.x = ((float)atof(pSprit) / 180) * D3DX_PI;

						//Y���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_rot.y = ((float)atof(pSprit) / 180) * D3DX_PI;

						//Z���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_rot.z = ((float)atof(pSprit) / 180) * D3DX_PI;
					}
					else if (strncmp(&aCode[0], CODE_NAMEIDX, sizeof CODE_NAMEIDX / sizeof(char) - 1) == 0)
					{//���f���ԍ��ݒ�
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_name = (MODELNAME)atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_LIFE, sizeof CODE_LIFE / sizeof(char) - 1) == 0)
					{//�̗͐ݒ�
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

					 //�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_nLife = atoi(pSprit);
					}
					break;
				}
			}
		}

		//�t�@�C������
		fclose(pFile);
	}
	else
	{
		assert(pFile != NULL);
	}
}

//========================
//���[�V�����ǂݍ��ݏ���
//========================
void LoadMotionFile(void)
{
	FILE *pFile;
	char aCode[CODE_LENGTH];
	char *pSprit;
	bool bRead = false;

	//���[�V�������
	//�ǂݍ��݃t�@�C���ݒ�
	pFile = fopen(MOTIONVIEWERDATA_PATH, "r");

	//�G�z�u�����擾
	if (pFile != NULL)
	{
		while (1)
		{
			fgets(&aCode[0], CODE_LENGTH, pFile);

			//�R�����g�A�E�g�`�F�b�N
			char *pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
				*pCharPos = '\0';
			}

			//�^�u����
			while (aCode[0] == '\t')
			{
				char aCodeBackup[CODE_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//������`�F�b�N
			if (strncmp(&aCode[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��J�n
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��I��
				bRead = false;
				break;
			}
			else if (aCode[0] == EOF)
			{//EOF��������Ȃ�
				if (feof(pFile))
				{//����A�����EOF��
					bRead = false;
					break;
				}
			}
			else if (bRead == true)
			{//�ǂݎ��
				switch (g_readStat)
				{
				case READSTAT_NONE:	//�����擾
					if (strncmp(&aCode[0], CODE_CHARACTERSET, sizeof CODE_CHARACTERSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_CHARACTERSET;
					}
					if (strncmp(&aCode[0], CODE_MOTIONSET, sizeof CODE_MOTIONSET / sizeof(char) - 1) == 0)
					{
						if (g_counterMotionInfo < MOTIONTYPE_MAX)
						{
							g_readStat = READSTAT_MOTIONSET;
						}
					}
					break;
				case READSTAT_CHARACTERSET:		//���f�����擾
					g_readStat = READSTAT_NONE;	//���g�p�̂��ߑ��I��
					break;
				case READSTAT_MOTIONSET:
					if (strncmp(&aCode[0], CODE_KEYSET, sizeof CODE_KEYSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_KEYSET;
					}
					else if (strncmp(&aCode[0], CODE_END_MOTIONSET, sizeof CODE_END_MOTIONSET / sizeof(char) - 1) == 0)
					{
						g_counterMotionInfo++;
						g_counterKeyInfo = 0;
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_LOOP, sizeof CODE_LOOP / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

															//���[�v�ۓǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_motionInfo[g_counterMotionInfo].mLoop = atoi(pSprit) ? true : false;
					}
					else if (strncmp(&aCode[0], CODE_NUM_KEY, sizeof CODE_NUM_KEY / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

															//�L�[���ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_motionInfo[g_counterMotionInfo].mNumKey = atoi(pSprit);
					}
					break;
				case READSTAT_KEYSET:
					if (strncmp(&aCode[0], CODE_KEY, sizeof CODE_KEY / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_KEY;
					}
					else if (strncmp(&aCode[0], CODE_END_KEYSET, sizeof CODE_END_KEYSET / sizeof(char) - 1) == 0)
					{
						g_counterKeyInfo++;
						g_counterKey = 0;
						g_readStat = READSTAT_MOTIONSET;
					}
					else if (strncmp(&aCode[0], CODE_FRAME, sizeof CODE_FRAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�t���[�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_motionInfo[g_counterMotionInfo].aKeyInfo[g_counterKeyInfo].mFrame = atoi(pSprit);
					}
					break;
				case READSTAT_KEY:
					if (strncmp(&aCode[0], CODE_END_KEY, sizeof CODE_END_KEY / sizeof(char) - 1) == 0)
					{
						g_counterKey++;
						g_readStat = READSTAT_KEYSET;
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_motionInfo[g_counterMotionInfo].aKeyInfo[g_counterKeyInfo].aKey[g_counterKey].mPosX = (float)atof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_motionInfo[g_counterMotionInfo].aKeyInfo[g_counterKeyInfo].aKey[g_counterKey].mPosY = (float)atof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_motionInfo[g_counterMotionInfo].aKeyInfo[g_counterKeyInfo].aKey[g_counterKey].mPosZ = (float)atof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_motionInfo[g_counterMotionInfo].aKeyInfo[g_counterKeyInfo].aKey[g_counterKey].mRotX = (float)atof(pSprit);

						//Y�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_motionInfo[g_counterMotionInfo].aKeyInfo[g_counterKeyInfo].aKey[g_counterKey].mRotY = (float)atof(pSprit);

						//Z�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						g_motionInfo[g_counterMotionInfo].aKeyInfo[g_counterKeyInfo].aKey[g_counterKey].mRotZ = (float)atof(pSprit);
					}
					break;
				}
			}
		}

		//�t�@�C������
		fclose(pFile);
	}
	else
	{
		assert(pFile != NULL);
	}
}

//========================
//���[�V�����擾����
//========================
void GetMotionInfo(MOTION_INFO *pMotionInfo)
{
	for (int nCntMotion = 0; nCntMotion < MOTIONTYPE_MAX; nCntMotion++)
	{
		*(pMotionInfo + nCntMotion) = g_motionInfo[nCntMotion];
	}
}