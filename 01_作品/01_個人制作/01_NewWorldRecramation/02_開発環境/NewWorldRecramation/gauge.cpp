//==========================================
//
//ゲージ表示プログラム[gauge.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "gauge.h"
#include "player.h"

//マクロ
#define GAUGETEX_PAT_NUM		(5)
#define HPGAUGETEX_PATTERN		(5)
#define ENEGAUGETEX_PATTERN		(3)
#define GAUGETEX_SIZE_WIDTH		(224.0f)
#define GAUGETEX_SIZE_HEIGHT	(40.0f)
#define GAUGEX_MAG	(1.3f)
#define GAUGEY_MAG	(1.2f)
#define ADD_POLY	(2)
#define HPGAUGE_POS		D3DXVECTOR3(936.0f, 500.0f, 0.0f);
#define ENEGAUGE_POS	D3DXVECTOR3(936.0f, 600.0f, 0.0f);

//テクスチャパス
//HP
#define HPGAUGE_MAXHP_PATH		"data\\TEXTURE\\Parameter_Max_Enpty.png"	//消費最大体力（不変）0
																			//残存最大体力（徐々に減らす,可変）1
#define HPGAUGE_ENPTY_PATH		"data\\TEXTURE\\Parameter_HP_02.png"		//残存最大体力（可変）2
																			//残存体力（徐々に減らす,可変）3
#define HPGAUGE_REMAIN_PATH		"data\\TEXTURE\\Parameter_HP_01.png"		//残存体力（可変）4

//Energy
#define ENEGAUGE_ENPTY_PATH		"data\\TEXTURE\\Parameter_Energy_Enpty.png"	//消費エネルギー（不変）5
																			//残存エネルギー（徐々に減らす,可変）6
#define ENEGAUGE_REMAIN_PATH	"data\\TEXTURE\\Parameter_Energy.png"		//残存エネルギー（可変）7

LPDIRECT3DTEXTURE9 g_apTextureGauge[GAUGETEX_PAT_NUM] = {};			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffGauge;						//ゲージ頂点バッファポインタ
D3DXVECTOR3 g_posHPGauge;										//体力ゲージ座標
D3DXVECTOR3 g_posEnergyGauge;									//エネルギーゲージ座標
int g_nOldHP;	//減らしている最中のHP
int g_nOldMHP;	//減らしている最中の最大HP
int g_nOldEne;	//減らしている最中のエネルギー
int g_aUseTex[HPGAUGETEX_PATTERN + ENEGAUGETEX_PATTERN] = { 0,1,1,2,2,3,4,4 };
D3DXCOLOR g_aUseAlpha[HPGAUGETEX_PATTERN + ENEGAUGETEX_PATTERN] = {
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//0
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),	//1
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//2
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),	//3
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//4
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//5
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),	//6
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//7
};

//========================
//初期化処理
//========================
void InitGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	Player *pPlayer = GetPlayer();
	int nCntGauge;				//カウンタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		HPGAUGE_MAXHP_PATH,
		&g_apTextureGauge[0]);
	D3DXCreateTextureFromFile(pDevice,
		HPGAUGE_ENPTY_PATH,
		&g_apTextureGauge[1]);
	D3DXCreateTextureFromFile(pDevice,
		HPGAUGE_REMAIN_PATH,
		&g_apTextureGauge[2]);
	D3DXCreateTextureFromFile(pDevice,
		ENEGAUGE_ENPTY_PATH,
		&g_apTextureGauge[3]);
	D3DXCreateTextureFromFile(pDevice,
		ENEGAUGE_REMAIN_PATH,
		&g_apTextureGauge[4]);


	//スコア位置・値・種類初期化
	g_posHPGauge = HPGAUGE_POS;
	g_posEnergyGauge = ENEGAUGE_POS;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (HPGAUGETEX_PATTERN + ENEGAUGETEX_PATTERN),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffGauge,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffGauge->Lock(0, 0, (void **)&pVtx, 0);

	//HPゲージの頂点情報設定
	for (nCntGauge = 0; nCntGauge < HPGAUGETEX_PATTERN; nCntGauge++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = g_posHPGauge;
		pVtx[1].pos.x = g_posHPGauge.x + GAUGETEX_SIZE_WIDTH * GAUGEX_MAG;
		pVtx[1].pos.y = g_posHPGauge.y;
		pVtx[2].pos.x = g_posHPGauge.x;
		pVtx[2].pos.y = g_posHPGauge.y + GAUGETEX_SIZE_HEIGHT * GAUGEY_MAG;
		pVtx[3].pos.x = g_posHPGauge.x + GAUGETEX_SIZE_WIDTH * GAUGEX_MAG;
		pVtx[3].pos.y = g_posHPGauge.y + GAUGETEX_SIZE_HEIGHT * GAUGEY_MAG;

		//座標変換用係数設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = g_aUseAlpha[nCntGauge];
		pVtx[1].col = g_aUseAlpha[nCntGauge];
		pVtx[2].col = g_aUseAlpha[nCntGauge];
		pVtx[3].col = g_aUseAlpha[nCntGauge];

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//エネルギーゲージの頂点情報設定
	for (; nCntGauge < HPGAUGETEX_PATTERN + ENEGAUGETEX_PATTERN; nCntGauge++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = g_posEnergyGauge;
		pVtx[1].pos.x = g_posEnergyGauge.x + GAUGETEX_SIZE_WIDTH * GAUGEX_MAG;
		pVtx[1].pos.y = g_posEnergyGauge.y;
		pVtx[2].pos.x = g_posEnergyGauge.x;
		pVtx[2].pos.y = g_posEnergyGauge.y + GAUGETEX_SIZE_HEIGHT * GAUGEY_MAG;
		pVtx[3].pos.x = g_posEnergyGauge.x + GAUGETEX_SIZE_WIDTH * GAUGEX_MAG;
		pVtx[3].pos.y = g_posEnergyGauge.y + GAUGETEX_SIZE_HEIGHT * GAUGEY_MAG;

		//座標変換用係数設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = g_aUseAlpha[nCntGauge];
		pVtx[1].col = g_aUseAlpha[nCntGauge];
		pVtx[2].col = g_aUseAlpha[nCntGauge];
		pVtx[3].col = g_aUseAlpha[nCntGauge];

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffGauge->Unlock();

	//プレイヤー情報をゲージに反映
	g_nOldHP = pPlayer->nLife;
	g_nOldMHP = pPlayer->nLife;
	g_nOldEne = pPlayer->nEnergy;
}

//========================
//終了処理
//========================
void UninitGauge(void)
{
	int nCntTexUnini;		//テクスチャ破棄カウンタ

	//テクスチャの破棄
	for (nCntTexUnini = 0; nCntTexUnini < GAUGETEX_PAT_NUM; nCntTexUnini++)
	{
		if (g_apTextureGauge[nCntTexUnini] != NULL)
		{
			g_apTextureGauge[nCntTexUnini]->Release();
			g_apTextureGauge[nCntTexUnini] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxbuffGauge != NULL)
	{
		g_pVtxbuffGauge->Release();
		g_pVtxbuffGauge = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateGauge(void)
{
#if 1
	Player *pPlayer = GetPlayer();	//プレイヤーポインタ

	//現在のステータスと減らしているステータスが違えば減らす
	//体力
	if (pPlayer->nLife > g_nOldHP)
	{
		g_nOldHP = pPlayer->nLife;
	}
	else if (pPlayer->nLife < g_nOldHP)
	{
		g_nOldHP--;
	}

	//最大体力
	if (pPlayer->nMaxLife < g_nOldMHP)
	{
		g_nOldMHP--;
	}

	//エネルギー
	if (pPlayer->nEnergy > g_nOldEne)
	{
		g_nOldEne = pPlayer->nEnergy;
	}
	else if (pPlayer->nEnergy < g_nOldEne)
	{
		g_nOldEne--;
	}

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffGauge->Lock(0, 0, (void **)&pVtx, 0);


	pVtx += 4;//徐々に減らす最大体力ゲージの頂点バッファに移動1

	//ポリゴンのサイズ変更
	pVtx[1].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldMHP / PLAYER_LIFE)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldMHP / PLAYER_LIFE)) * GAUGEX_MAG;

	//テクスチャサイズ変更
	pVtx[1].tex.x = 1.0f * ((float)g_nOldMHP / PLAYER_LIFE);
	pVtx[3].tex.x = 1.0f * ((float)g_nOldMHP / PLAYER_LIFE);


	pVtx += 4;//最大体力ゲージの頂点バッファに移動2

	//ポリゴンのサイズ変更
	pVtx[1].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nMaxLife / PLAYER_LIFE)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nMaxLife / PLAYER_LIFE)) * GAUGEX_MAG;

	//テクスチャサイズ変更
	pVtx[1].tex.x = 1.0f * ((float)pPlayer->nMaxLife / PLAYER_LIFE);
	pVtx[3].tex.x = 1.0f * ((float)pPlayer->nMaxLife / PLAYER_LIFE);


	pVtx += 4;//徐々に減らす体力ゲージの頂点バッファに移動3
	//ポリゴンのサイズ変更
	pVtx[1].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldHP / PLAYER_LIFE)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldHP / PLAYER_LIFE)) * GAUGEX_MAG;

	//テクスチャサイズ変更
	pVtx[1].tex.x = 1.0f * ((float)g_nOldHP / PLAYER_LIFE);
	pVtx[3].tex.x = 1.0f * ((float)g_nOldHP / PLAYER_LIFE);


	pVtx += 4;//体力ゲージの頂点バッファに移動4
	//ポリゴンのサイズ変更
	pVtx[1].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nLife / PLAYER_LIFE)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nLife / PLAYER_LIFE)) * GAUGEX_MAG;

	//テクスチャサイズ変更
	pVtx[1].tex.x = 1.0f * ((float)pPlayer->nLife / PLAYER_LIFE);
	pVtx[3].tex.x = 1.0f * ((float)pPlayer->nLife / PLAYER_LIFE);


	pVtx += 8;//エネルギーゲージの頂点バッファに移動6
	//ポリゴンのサイズ変更
	pVtx[1].pos.x = g_posEnergyGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldEne / PLAYER_ENERGY)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posEnergyGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldEne / PLAYER_ENERGY)) * GAUGEX_MAG;

	//テクスチャサイズ変更
	pVtx[1].tex.x = 1.0f * ((float)g_nOldEne / PLAYER_ENERGY);
	pVtx[3].tex.x = 1.0f * ((float)g_nOldEne / PLAYER_ENERGY);


	pVtx += 4;//エネルギーゲージの頂点バッファに移動7
	//ポリゴンのサイズ変更
	pVtx[1].pos.x = g_posEnergyGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nEnergy / PLAYER_ENERGY)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posEnergyGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nEnergy / PLAYER_ENERGY)) * GAUGEX_MAG;

	//テクスチャサイズ変更
	pVtx[1].tex.x = 1.0f * ((float)pPlayer->nEnergy / PLAYER_ENERGY);
	pVtx[3].tex.x = 1.0f * ((float)pPlayer->nEnergy / PLAYER_ENERGY);

	//頂点バッファをアンロック
	g_pVtxbuffGauge->Unlock();
#endif
}

//========================
//描画処理
//========================
void DrawGauge(void)
{
	int nCntGauge;				//カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffGauge, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntGauge = 0; nCntGauge < HPGAUGETEX_PATTERN + ENEGAUGETEX_PATTERN; nCntGauge++)
	{
		//テクスチャ設定・ポリゴン描画
		pDevice->SetTexture(0, g_apTextureGauge[g_aUseTex[nCntGauge]]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGauge * 4, 2);
	}
}