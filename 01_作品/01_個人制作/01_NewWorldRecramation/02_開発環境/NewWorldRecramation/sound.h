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
	SOUND_LABEL_BGM_2ATK = 0,	// BGM（2分間TA: Be Happy - Ucchii0）
	SOUND_LABEL_BGM_STG1,		// BGM（STG1: Tomorrow Land - 龍崎一）
	SOUND_LABEL_BGM_STG2,		// BGM（STG2: Flower - 龍崎一）
	SOUND_LABEL_BGM_STG3,		// BGM（STG3: ハレルヤ・ネットワーク - 龍崎一）
	SOUND_LABEL_BGM_STG4,		// BGM（STG4: Trick style - まんぼう二等兵）
	SOUND_LABEL_BGM_STGL,		// BGM（STGL: Empathy - Ucchii0 feat.Haruna（ファイル名は読み込みエラー防止のためTrick styleの状態））
	SOUND_LABEL_SE_TOPSTART,	// 起動時の画面でEnter
	SOUND_LABEL_SE_ALART,		// 警告
	SOUND_LABEL_SE_MESSAGE,		// メッセージ
	SOUND_LABEL_SE_HEALHP,		// HP回復
	SOUND_LABEL_SE_HEALENE,		// エネルギー回復
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_HIT,			// ヒット音
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_PRSENTER,	// Enterキーを押した
	SOUND_LABEL_SE_CLEAR,		// ミッションクリア
	SOUND_LABEL_SE_OVER,		// ミッション失敗
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
