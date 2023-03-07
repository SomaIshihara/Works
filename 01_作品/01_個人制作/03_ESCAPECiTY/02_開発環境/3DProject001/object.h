//==========================================
//
//モデルプログラムのヘッダ[object.h]
//Author:石原颯馬
//
//==========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//マクロ
#define MAX_OBJECT				(512)
#define OBJ_MAX_TEXTURE			(16)
#define OBJ_DAMAGE_TIME		(5)		//ダメージ状態にする時間(F)

//オブジェクト状態列挙
typedef enum
{
	OBJSTATE_NONE = 0,
	OBJSTATE_DAMAGE,
	OBJSTATE_BROKEN,
	OBJSTATE_MAX
} OBJSTATE;

//設計図の名前
typedef enum
{
	BLUEPRINTIDX_JOBI = 0,			//情ビ（スタート
	BLUEPRINTIDX_SUBWAYENTRANCE,	//地下鉄入口（ゴール
	BLUEPRINTIDX_ROCK_01,			//石01
	BLUEPRINTIDX_ROCK_02,			//石02
	BLUEPRINTIDX_ROCK_03,			//石03
	BLUEPRINTIDX_ROCK_04,			//石04
	BLUEPRINTIDX_ROCK_05,			//石05
	BLUEPRINTIDX_ROCK_06,			//石06
	BLUEPRINTIDX_ROCK_07,			//石07
	BLUEPRINTIDX_ROCK_08,			//石09
	BLUEPRINTIDX_ROCK_09,			//石09
	BLUEPRINTIDX_ROCK_10,			//石10
	BLUEPRINTIDX_ROCK_11,			//石11
	BLUEPRINTIDX_BUILDING_01,		//
	BLUEPRINTIDX_BUILDING_02,
	BLUEPRINTIDX_BUILDING_03,
	BLUEPRINTIDX_BUILDING_04,
	BLUEPRINTIDX_BUILDING_05,
	BLUEPRINTIDX_BUILDING_06,
	BLUEPRINTIDX_MAX
} BLUEPRINTIDX;

//オブジェクト構造体
typedef struct
{
	//オブジェクト見た目関係
	LPD3DXMESH pMesh = NULL;				//メッシュへのポインタ
	LPD3DXBUFFER pBuffMat = NULL;			//マテリアルへのポインタ
	DWORD dwNumMat;							//マテリアル数
	LPDIRECT3DTEXTURE9 apTexture[OBJ_MAX_TEXTURE] = {};	//テクスチャポインタ
	D3DXVECTOR3 vtxMin, vtxMax;				//小さい頂点・大きい頂点
} BluePrint;

//表示オブジェクト構造体
typedef struct
{
	//設計図名
	BLUEPRINTIDX bpidx;

	//位置関係
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス

	//ステータス関係
	bool bLifeUse;			//体力の項目を使用するか
	int nLife;				//体力
	OBJSTATE state;			//状態
	int nCounterState;		//状態遷移までの時間

	//表示関係
	int nIdxShadow = -1;	//影番号

	//使用の有無
	bool bUse;				//使用の有無
} Object;

//プロトタイプ宣言
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
void SetObject(BLUEPRINTIDX bpidx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bLifeUse, int nLife);
Object *GetObj(void);
BluePrint *GetBluePrint(void);
void HitObj(int nNumObj);
void DestroyObj(int nNumObj);

#endif // !_OBJECT_H_
