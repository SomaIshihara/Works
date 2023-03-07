//==========================================
//
//カメラプログラムのヘッダ[camera.h]
//Author:石原颯馬
//
//==========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//カメラ構造体
typedef struct
{
	D3DXVECTOR3 posV;		//現在視点
	D3DXVECTOR3 posVDest;	//目標視点
	D3DXVECTOR3 posR;		//現在注視点
	D3DXVECTOR3 posRDest;	//目標注視点
	D3DXVECTOR3 vecU;		//上方向ベクトル
	D3DXVECTOR3 rot;		//現在向き
	D3DXVECTOR3 rotDest;	//目標向き
	float fLength;			//距離
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
} Camera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);
void ResetCamera(float fLength, D3DXVECTOR2 posV, D3DXVECTOR3 posR, D3DXVECTOR3 rot);

#endif // !_CAMERA_H_
