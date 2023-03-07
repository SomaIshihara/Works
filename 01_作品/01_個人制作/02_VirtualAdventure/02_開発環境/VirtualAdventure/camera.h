//==========================================
//
//マッププログラムのヘッダ[camera.h]
//Author:石原颯馬
//
//==========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "player.h"

//マクロ
#define CAMERA_MOVEX		(320)	//カメラ移動の最低値

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
D3DXVECTOR3 GetCameraPos(void);

#endif // !_CAMERA_H_
