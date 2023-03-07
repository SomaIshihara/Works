//==========================================
//
//�t�@�C���ǂݍ��݃v���O�����̃w�b�_[file.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _FILE_H_
#define _FILE_H_

#include "main.h"
#include "model.h"

//�}�N��
//�Ȃ�

//�R�[�h��
//����
//�ǂݍ��݊J�n�E�I��
#define CODE_SCRIPT				"SCRIPT"			//�X�N���v�g�J�n
#define CODE_END_SCRIPT			"END_SCRIPT"		//�X�N���v�g�I��

//�I���W�i��
//�G�z�u
#define CODE_SETENEMY			"SETENEMY"			//�G�z�u(�g�p�p�����[�^:pos,rot,nameIdx,life)
#define CODE_END_SETENEMY		"END_SETENEMY"		//�G�z�u�I��

//�p�����[�^
#define CODE_NAMEIDX			"NAMEIDX"			//���O�̔ԍ�
#define CODE_LIFE				"LIFE"				//�̗�

//���f���r���[���[�E���[�V�����r���[���[�p
//���f���r���[��
//�e�N�X�`����
#define CODE_NUM_TEXTURE		"NUM_TEXTURE"		//�e�N�X�`�����ǂݎ��
//�e�N�X�`���t�@�C����
#define CODE_TEXTURE_FILENAME	"TEXTURE_FILENAME"	//�e�N�X�`���t�@�C���p�X�ǂݎ��
//���f����
#define CODE_NUM_MODEL			"NUM_MODEL"			//���f�����ǂݎ��
//���f���t�@�C����
#define CODE_MODEL_FILENAME		"MODEL_FILENAME"	//���f���t�@�C���p�X�ǂݎ��
//�J�������
#define CODE_CAMERASET			"CAMERASET"			//�J�����̐ݒ�J�n
#define CODE_END_CAMERASET		"END_CAMERASET"		//�J�����̐ݒ�I��
//���C�g���
#define CODE_LIGHTSET			"LIGHTSET"			//���C�g�ݒ�J�n
#define CODE_END_LIGHTSET		"END_LIGHTSET"		//���C�g�ݒ�I��
//����
#define CODE_SKYSET				"SKYSET"			//��ݒ�J�n
#define CODE_END_SKYSET			"END_SKYSET"		//��ݒ�I��
//�R���
#define CODE_MOUNTAINSET		"MOUNTAINSET"		//�R�ݒ�J�n
#define CODE_END_MOUNTAINSET	"END_MOUNTAINSET"	//�R�ݒ�I��
//�n�ʏ��
#define CODE_FIELDSET			"FIELDSET"			//�n�ʐݒ�J�n
#define CODE_END_FIELDSET		"END_FIELDSET"		//�n�ʐݒ�I��
//�Ǐ��
#define CODE_WALLSET			"WALLSET"			//�ǐݒ�J�n
#define CODE_END_WALLSET		"END_WALLSET"		//�ǐݒ�I��
//���f�����
#define CODE_MODELSET			"MODELSET"			//���f���z�u�J�n
#define CODE_END_MODELSET		"END_MODELSET"		//���f���z�u�I��
//�r���{�[�h���
#define CODE_BILLBOARDSET		"BILLBOARDSET"		//�r���{�[�h�z�u�J�n
#define CODE_END_BILLBOARDSET	"END_BILLBOARDSET"	//�r���{�[�h�z�u�I��
//�v���C���[���
#define CODE_PLAYERSET			"PLAYERSET"			//�v���C���[�z�u�J�n
#define CODE_END_PLAYERSET		"END_PLAYERSET"		//�v���C���[�z�u�I��

//���[�V�����r���[���[
//����
#define CODE_NUM_MODEL			"NUM_MODEL"			//���f����
#define CODE_MODEL_FILENAME		"MODEL_FILENAME"	//���f���̃t�@�C���p�X
#define CODE_CHARACTERSET		"CHARACTERSET"		//�L�����N�^�[���
#define CODE_END_CHARACTERSET	"END_CHARACTERSET"

//�p�[�c�ݒ�
#define CODE_PARTSSET			"PARTSSET"			//�p�[�c�ݒ�J�n
#define CODE_END_PARTSSET		"END_PARTSSET"		//�p�[�c�ݒ�I��

//���[�V�����ݒ�
#define CODE_MOTIONSET			"MOTIONSET"			//���[�V�����ݒ�J�n
#define CODE_END_MOTIONSET		"END_MOTIONSET"		//���[�V�����ݒ�I��
//�L�[�Z�b�g�ݒ�
#define CODE_KEYSET				"KEYSET"			//�L�[�Z�b�g�ݒ�J�n
#define CODE_END_KEYSET			"END_KEYSET"		//�L�[�Z�b�g�ݒ�I��
//�L�[�ݒ�
#define CODE_KEY				"KEY"				//�L�[�ݒ�J�n
#define CODE_END_KEY			"END_KEY"			//�L�[�ݒ�I��

//�p�����[�^�ށi�I���W�i���EMV���ʕ�������j
//���f���E���[�V��������
#define CODE_POS				"POS"				//�ʒu
#define CODE_ROT				"ROT"				//����
//���f���r���[���[�p
#define CODE_REF				"REF"				//�����_
#define CODE_DIRECTION			"DIRECTION"			//����
#define CODE_DIFFUSE			"DIFFUSE"			//�g�U��
#define CODE_TEXTYPE			"TEXTYPE"			//�e�N�X�`�����
#define CODE_MOVE				"MOVE"				//�ړ���
#define CODE_BLOCK				"BLOCK"				//�}�X��
#define CODE_SIZE				"SIZE"				//1�}�X������̑傫��
#define CODE_TYPE				"TYPE"				//���f���ރ^�C�v
#define CODE_STATE				"STATE"				//��ԁi���Ɏg�����Y�ꂽ
#define CODE_COLLISION			"COLLISION"			//�����蔻��i���Ɏg�����Y�ꂽ
#define CODE_SHADOW				"SHADOW"			//�e�ݒ�
#define CODE_ORIGIN				"ORIGIN"			//�Ȃɂ���
#define CODE_BLEND				"BLEND"				//�����̐ݒ肶��Ȃ�����
#define CODE_MOTION_FILENAME	"MOTION_FILENAME"	//���[�V�����̃t�@�C���p�X
//���[�V�����r���[���[�p
#define CODE_MOVE				"MOVE"				//�ړ���
#define CODE_JUMP				"JUMP"				//�W�����v��
#define CODE_RADIUS				"RADIUS"			//���a
#define CODE_NUM_PARTS			"NUM_PARTS"			//�p�[�c��
#define CODE_INDEX				"INDEX"				//�ԍ�
#define CODE_PARENT				"PARENT"			//�e���f���̔ԍ�
#define CODE_LOOP				"LOOP"				//���[�v���邩�̐ݒ�
#define CODE_NUM_KEY			"NUM_KEY"			//�L�[��
#define CODE_FRAME				"FRAME"				//�t���[����

//�v���g
void InitFile(void);
void UninitFile(void);
void UpdateFile(void);
void LoadMapFile(void);
void LoadMotionFile(void);
void GetMotionInfo(MOTION_INFO *pMotionInfo);

#endif