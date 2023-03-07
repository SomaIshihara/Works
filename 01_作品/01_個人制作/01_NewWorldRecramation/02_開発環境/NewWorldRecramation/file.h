//==========================================
//
//ファイル読み込みプログラムのヘッダ[file.h]
//Author:石原颯馬
//
//==========================================
#ifndef _FILE_H_
#define _FILE_H_

#include "main.h"
#include "game.h"
#include "ranking.h"

//マクロ
#define ENEMY_TYPE	(8)
#define MAX_ENEMY	(128)	//敵の最大数
#define READMAP_CODENUM	(512)

//コード名
#define CODE_START		"Start"			//スクリプト開始
#define CODE_SETENEMY	"SetEnemy"		//敵配置
#define CODE_SETDZ		"SetDZ"			//ダメージゾーン配置
#define CODE_KILL		"Kill"			//プレイヤーの体力を0にする
#define CODE_WAIT		"Wait"			//待機
#define CODE_SETBGM		"SetBGM"		//BGM設定
#define CODE_SETSPEED	"SetSpeed"		//BG・ダメージゾーンの流れる速度設定（100 = x1.0
#define CODE_SWITCHSKIP	"SwitchSkip"	//敵出現スキップの有効・無効化
#define CODE_SETITEM	"SetItem"		//アイテム配置
#define CODE_DEFBGMTIME	"DefBGMTime"	//BGM時間設定
#define CODE_END		"End"			//スクリプト終了
#define CODE_DEFENEMYSTAT "DefEnemyStat"	//敵情報定義

//移動タイプ
typedef enum
{
	MOVETYPE_SIN = 0,	//サイン移動をする敵（実際はサインの波形をしない作るのめんどい）
	MOVETYPE_SPATK,		//特攻する敵
	MOVETYPE_CUSTOM,	//自由設定
	MOVETYPE_BOSS,		//ボス専用挙動
	MOVETYPE_MAX
} MOVETYPE;

//敵基本情報構造体
typedef struct
{
	int nEnemyNum;	//種類番号
	int nEnemyType;	//敵の種類（雑魚かボスかなど）
	int nWidth;		//敵のポリゴンサイズ（幅）
	int nHeight;	//敵のポリゴンサイズ（高さ）
	int nFiringCT;	//弾発射CT
	int nLife;		//体力
	int nAddScore;	//スコア
} EnemyStat;

//敵呼び出し用構造体定義
typedef struct
{
	//コード
	char aCode[16];			//実行コード
	//メモ：SwitchSkipはaCodeを使用

	//敵配置
	MOVETYPE moveType;		//移動タイプ
	D3DXVECTOR3 startPos;	//湧き位置
	int nButtlePosTime;		//戦闘位置につくまでの時間
	D3DXVECTOR3 buttlePos;	//戦闘位置
	int nButtleTime;		//戦闘時間
	D3DXVECTOR3 returnPos;	//帰宅場所
	int nReturnPosTime;		//帰宅にかかる時間
	int nType;				//種類

	//待機
	int nWaitTime;			//待機時間

	//ダメージゾーン配置
	D3DXVECTOR3 DZPos;		//ダメージゾーンの位置
	float fWidth;			//幅
	float fHeight;			//高さ

	//レーザー配置
	float fRazerPosX;		//レーザーの位置（X座標のみ Yは0から）
	int nRazerChargeTime;	//レーザーチャージ時間

	//BGM設定
	int nBGMNumber;			//BGMの番号（並び順 数値をSOUND_LABELでキャスト）

	//スピード設定
	int nSpeed;				//BG・ダメージゾーンの流れる速度

	//アイテム設定（湧き位置は敵配置の湧き位置を使用）
	int nItemtype;			//アイテムタイプ（0がHP・1がエネルギー）

	//BGM時間
	int nBGMTime;			//BGM時間（file.cppでフレーム単位に換算済み）
} MapData;

void InitFile(void);
void UninitFile(void);
void UpdateFile(void);
void LoadMapEnemyFile(void);							//マップ・敵情報読み込み
void LoadStoryScoreFile(int *pScore, int *nOpenStage);	//ストーリースコア読み込み
void SaveStoryScoreFile(int *pScore, int nOpenStage);	//ストーリースコア書き込み
void LoadRankingFile(Ranking *rank);					//ランキング読み込み
void SaveRankingFile(Ranking *rank);					//ランキング書き込み
int GetMapData(MapData *pEnemy);						//敵配置取得
void GetEnemyStat(EnemyStat *pEnemyStat);				//敵情報取得
int RefEnemyType(int nEnemyNum);						//敵番号に応じてタイプを返す
bool GetSkip(void);

#endif