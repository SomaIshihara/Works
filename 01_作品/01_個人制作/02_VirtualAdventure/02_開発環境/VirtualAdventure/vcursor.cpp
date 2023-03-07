//==========================================
//
//仮想カーソルプログラム[vcursor.cpp]
//Author:石原颯馬
//
//=========================================

#include "main.h"
#include "vcursor.h"
#include "player.h"
#include "input.h"

//マクロ
//ほげほげ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureVCursor = NULL;		//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffVCursor;			//頂点バッファポインタ
D3DXVECTOR3 g_cursorPos;
bool g_bDispVCursor = false;						//仮想カーソル表示・非表示

//========================
//仮想カーソル初期化処理
//========================
void InitVCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\VA_VCursor.png",
		&g_pTextureVCursor);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffVCursor,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffVCursor->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//座標変換用係数設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxbuffVCursor->Unlock();

	//変数初期化
	g_cursorPos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_bDispVCursor = true;
}

//========================
//仮想カーソル終了処理
//========================
void UninitVCursor(void)
{
	//テクスチャの破棄
	if (g_pTextureVCursor != NULL)
	{
		g_pTextureVCursor->Release();
		g_pTextureVCursor = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffVCursor != NULL)
	{
		g_pVtxbuffVCursor->Release();
		g_pVtxbuffVCursor = NULL;
	}
}

//========================
//仮想カーソル更新処理
//========================
void UpdateVCursor(void)
{
	VERTEX_2D *pVtx;	//設定用ポインタ

	//カーソル位置取得
	if (GetUseGamepad() == false)
	{
		g_cursorPos = GetMousePos();
	}

	//頂点バッファロック
	g_pVtxbuffVCursor->Lock(0, 0, (void **)&pVtx, 0);

	if (g_bDispVCursor)
	{
		pVtx[0].pos.x = g_cursorPos.x;
		pVtx[0].pos.y = g_cursorPos.y;
		pVtx[1].pos.x = g_cursorPos.x + VCURSOR_WIDTH;
		pVtx[1].pos.y = g_cursorPos.y;
		pVtx[2].pos.x = g_cursorPos.x;
		pVtx[2].pos.y = g_cursorPos.y + VCURSOR_HEIGHT;
		pVtx[3].pos.x = g_cursorPos.x + VCURSOR_WIDTH;
		pVtx[3].pos.y = g_cursorPos.y + VCURSOR_HEIGHT;
	}

	g_pVtxbuffVCursor->Unlock();
}

//========================
//仮想カーソル描画処理
//========================
void DrawVCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffVCursor, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	if (g_bDispVCursor)
	{
		pDevice->SetTexture(0, g_pTextureVCursor);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//========================
//仮想カーソル表示・非表示設定処理
//========================
void SetDispVCursor(bool bDisp)
{
	g_bDispVCursor = bDisp;
}

//========================
//仮想カーソル表示・非表示取得処理
//========================
bool GetDispVCursor(void)
{
	return g_bDispVCursor;
}

//========================
//カーソルの取得
//========================
D3DXVECTOR3 *GetpCursorPos(void)
{
	return &g_cursorPos;
}