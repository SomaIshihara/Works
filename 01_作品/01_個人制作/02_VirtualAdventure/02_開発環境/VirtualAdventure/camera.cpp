//==========================================
//
//マッププログラム[camera.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "camera.h"
#include "file.h"
#include "block.h"

//マクロ
//ほげほげ

//グローバル
D3DXVECTOR3 g_posCamera;	//カメラ位置

//========================
//初期化処理
//========================
void InitCamera(void)
{
	//変数初期化
	g_posCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================
//終了処理
//========================
void UninitCamera(void)
{
	//変数初期化
	g_posCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================
//更新処理
//========================
void UpdateCamera(void)
{
	Player *pPlayer = GetPlayer();	//プレイヤーの情報取得

	if (pPlayer->pos.x - g_posCamera.x <= CAMERA_MOVEX || pPlayer->pos.x - g_posCamera.x >= SCREEN_WIDTH - CAMERA_MOVEX)
	{
		g_posCamera.x += pPlayer->pos.x - pPlayer->posOld.x;
		if (pPlayer->pos.x <= CAMERA_MOVEX)
		{
			g_posCamera.x = 0.0f;
		}
		else if (pPlayer->pos.x >= GetMapData()->blockData.nMapWidth * BLOCK_WIDTH - CAMERA_MOVEX)
		{
			g_posCamera.x = (float)GetMapData()->blockData.nMapWidth * BLOCK_WIDTH - SCREEN_WIDTH;
		}
	}
}

//========================
//カメラ位置取得処理
//========================
D3DXVECTOR3 GetCameraPos(void)
{
	return g_posCamera;
}