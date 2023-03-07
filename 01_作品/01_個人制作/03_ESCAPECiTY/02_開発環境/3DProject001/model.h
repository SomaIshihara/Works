//==========================================
//
//モデルプログラムのヘッダ[model.h]
//Author:石原颯馬
//
//==========================================
#ifndef _MODEL_H_
#define _MODEL_H_

//マクロ
#define EXITHUMAN_MODEL_NUM	(10)	//非常口の人に使われているモデル数
#define PUSHING_BACK		(1.0f)	//オブジェクトに当たった時の押し戻し

//非常口の人の幅高さ
#define EXITHUMAN_WIDTH		(30.0f)
#define EXITHUMAN_HEIGHT	(30.0f)

//モデル名列挙
typedef enum
{
	MODELNAME_EXITHUMAN = 0,
	MODELNAME_MAX
} MODELNAME;

//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	//ニュートラル
	MOTIONTYPE_MOVE,		//移動
	MOTIONTYPE_ACTION,		//アクション（EC未使用・ピクトさん未実装）
	MOTIONTYPE_JUMP,		//ジャンプ（EC未使用・ピクトさん未実装）
	MOTIONTYPE_LANDING,		//着地（EC未使用・ピクトさん未実装）
	MOTIONTYPE_MAX
} MOTIONTYPE;

//キー構造体
typedef struct
{
	float mPosX;	//位置X
	float mPosY;	//位置Y
	float mPosZ;	//位置Z
	float mRotX;	//向きX
	float mRotY;	//向きY
	float mRotZ;	//向きZ
} KEY;

//キー情報の構造体
typedef struct
{
	int mFrame;	//再生フレーム
	KEY aKey[EXITHUMAN_MODEL_NUM];	//モデルのキー要素
} KEY_INFO;

//モーション状態構造体
typedef struct
{
	bool mLoop;	//ループするか
	int mNumKey;//キー総数
	KEY_INFO aKeyInfo[16];	//キーの情報（16は適宜変えて）
} MOTION_INFO;

//モーション構造体
typedef struct
{
	//アニメーション関係
	MOTION_INFO aMotionInfo[MOTIONTYPE_MAX];	//モーション情報
	int mNumMotion;								//モーションの総数
	MOTIONTYPE motionType;						//モーション種類
	bool mLoopMotion;							//ループするか
	int mNumKey;								//キー総数
	int mKey;									//現在のキーNo.
	int mCounterMotion;							//モーションカウンター
} Motion;

//モデル構造体
typedef struct
{
	//描画関係
	LPD3DXMESH pMesh;		//メッシュ
	LPD3DXBUFFER pBuffMat;	//マテリアルポインタ
	DWORD dwNumMatModel;	//マテ数
	D3DXVECTOR3 posOffset;	//位置（オフセット）
	D3DXVECTOR3 pos;		//モーション設定した位置
	D3DXVECTOR3 rotOffset;	//向き
	D3DXVECTOR3 rot;		//モーション設定した向き
	D3DXMATRIX mtxWorld;	//ワールドマトリ
	LPDIRECT3DTEXTURE9 apTexture[16];	//テクスチャポインタ
	int mIdxModelParent;	//親モデルインデックス
} Model;

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model *GetModel(MODELNAME name);

#endif // !_MODEL_H_
