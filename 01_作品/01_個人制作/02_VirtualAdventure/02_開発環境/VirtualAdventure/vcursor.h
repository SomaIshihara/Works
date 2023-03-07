//==========================================
//
//仮想カーソルプログラムのヘッダ[vcursor.h]
//Author:石原颯馬
//
//==========================================
#ifndef _VCURSOR_H_
#define _VCURSOR_H_

#include "main.h"

//マクロ
#define VCURSOR_WIDTH		(21)		//幅
#define VCURSOR_HEIGHT		(28)		//高さ

//プロトタイプ宣言
void InitVCursor(void);
void UninitVCursor(void);
void UpdateVCursor(void);
void DrawVCursor(void);
void SetDispVCursor(bool bDisp);
bool GetDispVCursor(void);
D3DXVECTOR3 *GetpCursorPos(void);

#endif // !_VCURSOR_H_
