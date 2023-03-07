//==========================================
//
//ファイル読み込みプログラムのヘッダ[file.h]
//Author:石原颯馬
//
//==========================================
#ifndef _FILE_H_
#define _FILE_H_

#include "main.h"
#include "block.h"
#include "item.h"
#include "enemy.h"

//マクロ
#define ENEMY_TYPE		(8)
#define MAP_WIDTH		(512)
#define MAP_HEIGHT		(20)

//コード名
//読み込み開始・終了
#define CODE_START		"Start"			//スクリプト開始
#define CODE_END		"End"			//スクリプト終了

//ブロック
#define CODE_STARTBLOCK	"StartBlock"	//ブロック配置読み込み開始
#define CODE_ENDBLOCK	"EndBlock"		//ブロック配置読み込み終了

//敵
#define CODE_STARTENEMY	"StartEnemy"	//敵配置開始
#define CODE_ENDENEMY	"EndEnemy"		//敵配置終了

//アイテム
#define CODE_STARTITEM	"StartItem"		//アイテム配置開始
#define CODE_ENDITEM	"EndItem"		//アイテム配置終了

//地点
#define CODE_STARTSPOT	"StartSpot"		//地点配置開始
#define CODE_ENDSPOT	"EndSpot"		//地点配置終了

//ブロック配置構造体定義
typedef struct
{
	//ブロック配置
	int nMapWidth;	//実際のマップ幅
	int nMapHeight;	//実際のマップ高さ
	BLOCKTYPE blockType[MAP_HEIGHT][MAP_WIDTH];	//配置ブロック（読み込んだ数字をBlockでキャスト）
} BlockData;

//アイテム情報構造体定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	ITEMTYPE nType;		//アイテム種類
} ItemData;

//マップ全体の情報管理構造体定義
typedef struct
{
	//ブロック情報
	BlockData blockData;	//ブロック配置情報

	//敵配置
	Enemy EnemyData[MAX_ENEMY];
	int nEnemyNum;					//敵の数

	//アイテム設定
	ItemData itemData[MAX_ITEM];		//アイテム配置情報
	int nItemNum;						//アイテム個数

	//BGM設定
	int nBGMNumber;			//BGMの番号（並び順 数値をSOUND_LABELでキャスト）

} MapData;

void InitFile(void);
void UninitFile(void);
void UpdateFile(void);
void LoadMapFile(void);
int LoadHScoreFile(void);				//読み込み（同時にresultに代入）
void SaveHScoreFile(int nHScore);		//書き込み
MapData *GetMapData(void);				//敵配置取得

#endif