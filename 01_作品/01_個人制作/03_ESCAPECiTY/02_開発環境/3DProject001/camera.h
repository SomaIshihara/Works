//==========================================
//
//�J�����v���O�����̃w�b�_[camera.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//�J�����\����
typedef struct
{
	D3DXVECTOR3 posV;		//���ݎ��_
	D3DXVECTOR3 posVDest;	//�ڕW���_
	D3DXVECTOR3 posR;		//���ݒ����_
	D3DXVECTOR3 posRDest;	//�ڕW�����_
	D3DXVECTOR3 vecU;		//������x�N�g��
	D3DXVECTOR3 rot;		//���݌���
	D3DXVECTOR3 rotDest;	//�ڕW����
	float fLength;			//����
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
} Camera;

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);
void ResetCamera(float fLength, D3DXVECTOR2 posV, D3DXVECTOR3 posR, D3DXVECTOR3 rot);

#endif // !_CAMERA_H_
