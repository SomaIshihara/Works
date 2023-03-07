//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 石原颯馬
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,	// タイトルBGM
	SOUND_LABEL_BGM_GAME,		// ゲームBGM
	SOUND_LABEL_BGM_RESULT,		// 結果
	SOUND_LABEL_SE_START,		// スタート
	SOUND_LABEL_SE_SHOT,		// 弾発射
	SOUND_LABEL_SE_CLEAR,		// クリア
	SOUND_LABEL_SE_OVER,		// 失敗
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
void PauseSound(SOUND_LABEL label);
void RestartSound(SOUND_LABEL label);

#endif
