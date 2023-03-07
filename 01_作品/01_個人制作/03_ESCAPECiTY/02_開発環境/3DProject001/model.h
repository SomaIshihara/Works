//==========================================
//
//���f���v���O�����̃w�b�_[model.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _MODEL_H_
#define _MODEL_H_

//�}�N��
#define EXITHUMAN_MODEL_NUM	(10)	//�����̐l�Ɏg���Ă��郂�f����
#define PUSHING_BACK		(1.0f)	//�I�u�W�F�N�g�ɓ����������̉����߂�

//�����̐l�̕�����
#define EXITHUMAN_WIDTH		(30.0f)
#define EXITHUMAN_HEIGHT	(30.0f)

//���f������
typedef enum
{
	MODELNAME_EXITHUMAN = 0,
	MODELNAME_MAX
} MODELNAME;

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	//�j���[�g����
	MOTIONTYPE_MOVE,		//�ړ�
	MOTIONTYPE_ACTION,		//�A�N�V�����iEC���g�p�E�s�N�g���񖢎����j
	MOTIONTYPE_JUMP,		//�W�����v�iEC���g�p�E�s�N�g���񖢎����j
	MOTIONTYPE_LANDING,		//���n�iEC���g�p�E�s�N�g���񖢎����j
	MOTIONTYPE_MAX
} MOTIONTYPE;

//�L�[�\����
typedef struct
{
	float mPosX;	//�ʒuX
	float mPosY;	//�ʒuY
	float mPosZ;	//�ʒuZ
	float mRotX;	//����X
	float mRotY;	//����Y
	float mRotZ;	//����Z
} KEY;

//�L�[���̍\����
typedef struct
{
	int mFrame;	//�Đ��t���[��
	KEY aKey[EXITHUMAN_MODEL_NUM];	//���f���̃L�[�v�f
} KEY_INFO;

//���[�V������ԍ\����
typedef struct
{
	bool mLoop;	//���[�v���邩
	int mNumKey;//�L�[����
	KEY_INFO aKeyInfo[16];	//�L�[�̏��i16�͓K�X�ς��āj
} MOTION_INFO;

//���[�V�����\����
typedef struct
{
	//�A�j���[�V�����֌W
	MOTION_INFO aMotionInfo[MOTIONTYPE_MAX];	//���[�V�������
	int mNumMotion;								//���[�V�����̑���
	MOTIONTYPE motionType;						//���[�V�������
	bool mLoopMotion;							//���[�v���邩
	int mNumKey;								//�L�[����
	int mKey;									//���݂̃L�[No.
	int mCounterMotion;							//���[�V�����J�E���^�[
} Motion;

//���f���\����
typedef struct
{
	//�`��֌W
	LPD3DXMESH pMesh;		//���b�V��
	LPD3DXBUFFER pBuffMat;	//�}�e���A���|�C���^
	DWORD dwNumMatModel;	//�}�e��
	D3DXVECTOR3 posOffset;	//�ʒu�i�I�t�Z�b�g�j
	D3DXVECTOR3 pos;		//���[�V�����ݒ肵���ʒu
	D3DXVECTOR3 rotOffset;	//����
	D3DXVECTOR3 rot;		//���[�V�����ݒ肵������
	D3DXMATRIX mtxWorld;	//���[���h�}�g��
	LPDIRECT3DTEXTURE9 apTexture[16];	//�e�N�X�`���|�C���^
	int mIdxModelParent;	//�e���f���C���f�b�N�X
} Model;

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model *GetModel(MODELNAME name);

#endif // !_MODEL_H_
