//==========================================
//
//メッシュフィールドプログラムのヘッダ[meshfield.h]
//Author:石原颯馬
//
//==========================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//マクロ
#define MESHFIELD_LENGTH	(160.0f)	//1枚当たりの長さ
#define MESHFIELD_WIDTH		(17)		//横の分割数
#define MESHFIELD_HEIGHT	(14)		//縦の分割数

//プロトタイプ宣言
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

#endif // !_MESHFIELD_H_
