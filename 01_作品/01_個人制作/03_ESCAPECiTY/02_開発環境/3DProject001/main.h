//==========================================
//
//ゲーム全般を管理するプログラムのヘッダ[main.h]
//Author:石原颯馬
//
//==========================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <XInput.h>
#include <string.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	//ビルド時の警告対処
#include "dinput.h"
#include "xaudio2.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//画面モード
typedef enum
{
	MODE_TITLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
} MODE;

//マクロ定義
#define CLASS_NAME			"WindowClass"
#define SCREEN_WIDTH		(1280)		//クライアント領域の幅
#define SCREEN_HEIGHT		(720)		//クライアント領域の高さ
#define MAX_FPS				(60)		//最大フレームレート
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//2D
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//3D
#define FIX_ROT(x)			((float)fmod(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//角度を-PI~PIに修正
#define TASUKIGAKE(ax,az,bx,bz)	((az * bx) - (ax * bz))
#define PLAYER_POS			D3DXVECTOR3(0.0f, 0.0f, -960.0f)
#define OBJ_RED_ALPHA		(0.5f)	//赤さんの不透明度
#define CHAR_TEX_WIDTH		(256)	//文字テクスチャの幅
#define CHAR_TEX_HEIGHT		(320)	//文字テクスチャの高さ
#define CHAR_PATT_WIDTH		(8)		//文字テクスチャのパターン幅
#define CHAR_PATT_HEIGHT	(5)		//文字テクスチャのパターン高さ
#define NUMDATA(x)			(x)		//文字表示に使用。単に数字を入れただけ
#define CHARDATA(x)			(x - 0x37)	//文字表示に使用。文字を上のやつを考慮した数字に変換する
#define CHAR_SPACE			(36)	//スペース
#define CHAR_COLON			(37)	//コロン

//頂点情報[2D]
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変換係数（1.0fで固定）
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;

//頂点情報[3D]
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//カラー
	D3DXVECTOR2 tex;	//テクスチャ
} VERTEX_3D;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void SetShowCursor(bool bDisp);
void SetMode(MODE mode);
MODE GetMode(void);

#endif // !_MAIN_H_
