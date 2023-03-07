//==========================================
//
//ダメージゾーンプログラムのヘッダ[damagezone.h]
//Author:石原颯馬
//
//==========================================
#ifndef _DZ_H_
#define _DZ_H_

#include "main.h"
#include "file.h"

//マクロ
#define DZ_COL_DEFAULT_LIGHT		D3DXCOLOR(1.0f,0.945f,0.0f,1.0f)		//ダメージゾーンの色（黄色）
#define DZ_COL_DEFAULT_DARK			D3DXCOLOR(0.447f,0.094f,0.631f,1.0f)	//ダメージゾーンの色（紫）
#define DZ_COL_DEFAULT_RED			D3DXCOLOR(1.0f,0.0f,0.0f,0.42f)			//ダメージゾーンの色（赤）

//プロトタイプ宣言
void InitDamageZone(void);
void UninitDamageZone(void);
void UpdateDamageZone(void);
void DrawDamageZone(void);
void SetDamageZone(MapData setDZData, D3DXCOLOR col);

#endif // !_BG_H_
