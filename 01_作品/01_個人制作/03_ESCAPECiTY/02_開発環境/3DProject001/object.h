//==========================================
//
//���f���v���O�����̃w�b�_[object.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//�}�N��
#define MAX_OBJECT				(512)
#define OBJ_MAX_TEXTURE			(16)
#define OBJ_DAMAGE_TIME		(5)		//�_���[�W��Ԃɂ��鎞��(F)

//�I�u�W�F�N�g��ԗ�
typedef enum
{
	OBJSTATE_NONE = 0,
	OBJSTATE_DAMAGE,
	OBJSTATE_BROKEN,
	OBJSTATE_MAX
} OBJSTATE;

//�݌v�}�̖��O
typedef enum
{
	BLUEPRINTIDX_JOBI = 0,			//��r�i�X�^�[�g
	BLUEPRINTIDX_SUBWAYENTRANCE,	//�n���S�����i�S�[��
	BLUEPRINTIDX_ROCK_01,			//��01
	BLUEPRINTIDX_ROCK_02,			//��02
	BLUEPRINTIDX_ROCK_03,			//��03
	BLUEPRINTIDX_ROCK_04,			//��04
	BLUEPRINTIDX_ROCK_05,			//��05
	BLUEPRINTIDX_ROCK_06,			//��06
	BLUEPRINTIDX_ROCK_07,			//��07
	BLUEPRINTIDX_ROCK_08,			//��09
	BLUEPRINTIDX_ROCK_09,			//��09
	BLUEPRINTIDX_ROCK_10,			//��10
	BLUEPRINTIDX_ROCK_11,			//��11
	BLUEPRINTIDX_BUILDING_01,		//
	BLUEPRINTIDX_BUILDING_02,
	BLUEPRINTIDX_BUILDING_03,
	BLUEPRINTIDX_BUILDING_04,
	BLUEPRINTIDX_BUILDING_05,
	BLUEPRINTIDX_BUILDING_06,
	BLUEPRINTIDX_MAX
} BLUEPRINTIDX;

//�I�u�W�F�N�g�\����
typedef struct
{
	//�I�u�W�F�N�g�����ڊ֌W
	LPD3DXMESH pMesh = NULL;				//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat = NULL;			//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;							//�}�e���A����
	LPDIRECT3DTEXTURE9 apTexture[OBJ_MAX_TEXTURE] = {};	//�e�N�X�`���|�C���^
	D3DXVECTOR3 vtxMin, vtxMax;				//���������_�E�傫�����_
} BluePrint;

//�\���I�u�W�F�N�g�\����
typedef struct
{
	//�݌v�}��
	BLUEPRINTIDX bpidx;

	//�ʒu�֌W
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X

	//�X�e�[�^�X�֌W
	bool bLifeUse;			//�̗͂̍��ڂ��g�p���邩
	int nLife;				//�̗�
	OBJSTATE state;			//���
	int nCounterState;		//��ԑJ�ڂ܂ł̎���

	//�\���֌W
	int nIdxShadow = -1;	//�e�ԍ�

	//�g�p�̗L��
	bool bUse;				//�g�p�̗L��
} Object;

//�v���g�^�C�v�錾
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
void SetObject(BLUEPRINTIDX bpidx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bLifeUse, int nLife);
Object *GetObj(void);
BluePrint *GetBluePrint(void);
void HitObj(int nNumObj);
void DestroyObj(int nNumObj);

#endif // !_OBJECT_H_
