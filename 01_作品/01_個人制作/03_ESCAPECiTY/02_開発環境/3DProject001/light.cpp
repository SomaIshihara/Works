//==========================================
//
//ライト関係プログラム[light.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "light.h"

//マクロ
#define MAX_LIGHT	(3)	//ライト数

//プロト
D3DLIGHT9 g_light[MAX_LIGHT];	//ライト情報

//========================
//初期化処理
//========================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXVECTOR3 vecDir;	//設定用

	//ライト情報クリア
	ZeroMemory(&g_light[0], sizeof(D3DLIGHT9));
	ZeroMemory(&g_light[1], sizeof(D3DLIGHT9));
	ZeroMemory(&g_light[2], sizeof(D3DLIGHT9));

	//ライト種類設定
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;

	//ライト拡散光設定
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向
	//0
	vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);

	g_light[0].Direction = vecDir;

	//1
	vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);

	g_light[1].Direction = vecDir;

	//2
	vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);

	g_light[2].Direction = vecDir;

	//ライト設定
	pDevice->SetLight(0, &g_light[0]);
	pDevice->SetLight(1, &g_light[1]);
	pDevice->SetLight(2, &g_light[2]);

	//ライト有効化
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
}

//========================
//終了処理
//========================
void UninitLight(void)
{
	//無
}

//========================
//更新処理
//========================
void UpdateLight(void)
{
	//無
}