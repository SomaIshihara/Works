//==========================================
//
//敵プログラム[enemy.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "enemy.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "wall.h"
#include "object.h"
#include "debugproc.h"
#include <assert.h>

//マクロ
#define ENEMY_MOVE_SPEED	(5.0f)	//プレイヤー移動速度
#define DUMP_COEF			(0.4f)	//減衰係数

//プロト
void CollisionWallEnemy(int nNumber);
void CollisionObjEnemy(int nNumber);

//グローバル変数
Enemy g_aEnemy[MAX_ENEMY];

//========================
//初期化処理
//========================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//敵に情報を追加
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//変数初期化
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nIdxShadow = -1;
		g_aEnemy[nCntEnemy].bUse = false;

		for (int nCntParts = 0; nCntParts < EXITHUMAN_MODEL_NUM; nCntParts++)
		{
			//モデル初期化
			g_aEnemy[nCntEnemy].aModel[nCntParts] = {};
		}

		//対角線の長さ・角度
		g_aEnemy[nCntEnemy].fLength = sqrtf(EXITHUMAN_WIDTH * EXITHUMAN_WIDTH + EXITHUMAN_HEIGHT * EXITHUMAN_HEIGHT) * 0.5f;
		g_aEnemy[nCntEnemy].fAngle = atan2f(EXITHUMAN_WIDTH, EXITHUMAN_HEIGHT);

		//影設定
		g_aEnemy[nCntEnemy].nIdxShadow = -1;
	}
}

//========================
//終了処理
//========================
void UninitEnemy(void)
{
	for (int nCntModel = 0; nCntModel < MAX_ENEMY; nCntModel++)
	{
		for (int nCntParts = 0; nCntParts < EXITHUMAN_MODEL_NUM; nCntParts++)
		{
			//model.cppの方でReleaseするからこっちはNULL入れるだけでいいよ
			g_aEnemy[nCntModel].aModel[nCntParts].pMesh = NULL;
			g_aEnemy[nCntModel].aModel[nCntParts].pBuffMat = NULL;
#if 0
			//メッシュの破棄
			if (g_aEnemy[nCntModel].aModel[nCntParts].pMesh != NULL)
			{
				g_aEnemy[nCntModel].aModel[nCntParts].pMesh->Release();
				g_aEnemy[nCntModel].aModel[nCntParts].pMesh = NULL;
			}

			//マテリアルの破棄
			if (g_aEnemy[nCntModel].aModel[nCntParts].pBuffMat != NULL)
			{
				g_aEnemy[nCntModel].aModel[nCntParts].pBuffMat->Release();
				g_aEnemy[nCntModel].aModel[nCntParts].pBuffMat = NULL;
			}
#endif
		}
	}
}

//========================
//更新処理
//========================
void UpdateEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//現在の位置を前回の位置にする
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;

			//状態に応じて処理
			switch (g_aEnemy[nCntEnemy].state)
			{
			case OBJSTATE_NONE:
				break;
			case OBJSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = OBJSTATE_NONE;
				}
				break;
			case OBJSTATE_BROKEN:
				break;
			}

			//メモ。今はやらないで暇なときやって
#if 0
			//カメラ向きに応じてプレイヤーの向き旋回
			if (GetMouseClickPress(MOUSE_CLICK_LEFT) == true)
			{
				g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + 1.0f * D3DX_PI + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			}

			//モデル移動
			//カメラからみて
			if (GetKeyboardPress(DIK_W) == true)
			{
				if (false)
				{//左前
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_WA + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
				else if (false)
				{//右前
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_WD + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
				else
				{//前
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_W + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{
				if (false)
				{//左後
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_SA + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
				else if (false)
				{//右後
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_SD + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
				else
				{//後ろ
					g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_S + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
					g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
					g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				}
			}
			else if (false)
			{//左
				g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_A + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
				g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
			}
			else if (false)
			{//右
				g_aEnemy[nCntEnemy].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_D + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
				g_aEnemy[nCntEnemy].move.x = sinf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
				g_aEnemy[nCntEnemy].move.z = cosf((float)fmod((g_aEnemy[nCntEnemy].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
			}

			//ボタン操作に応じてプレイヤー移動
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.z += g_aEnemy[nCntEnemy].move.z;

			//壁当たり判定
			CollisionWallEnemy(nCntEnemy);

			//オブジェクト当たり判定
			CollisionObjEnemy(nCntEnemy);

			//移動量減衰
			g_aEnemy[nCntEnemy].move.x += (0 - g_aEnemy[nCntEnemy].move.x) * DUMP_COEF;
			g_aEnemy[nCntEnemy].move.z += (0 - g_aEnemy[nCntEnemy].move.z) * DUMP_COEF;
#endif
			//影位置設定
			SetPositionShadow(g_aEnemy[nCntEnemy].nIdxShadow, g_aEnemy[nCntEnemy].pos);
		}
	}
}

//========================
//描画処理
//========================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//"プレイヤーの"ワールドマトリックス初期化
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//"プレイヤーの"ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			for (int nCntModel = 0; nCntModel < EXITHUMAN_MODEL_NUM; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用
				D3DXMATRIX mtxParent;					//親のマトリ

														//"モデルの"ワールドマトリックス初期化
				D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCntEnemy].aModel[nCntModel].rotOffset.y, g_aEnemy[nCntEnemy].aModel[nCntModel].rotOffset.x, g_aEnemy[nCntEnemy].aModel[nCntModel].rotOffset.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//位置反映
				D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCntEnemy].aModel[nCntModel].posOffset.x, g_aEnemy[nCntEnemy].aModel[nCntModel].posOffset.y, g_aEnemy[nCntEnemy].aModel[nCntModel].posOffset.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//パーツの親マトリ設定
				if (g_aEnemy[nCntEnemy].aModel[nCntModel].mIdxModelParent != -1)
				{
					mtxParent = g_aEnemy[nCntEnemy].aModel[g_aEnemy[nCntEnemy].aModel[nCntModel].mIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_aEnemy[nCntEnemy].mtxWorld;
				}

				//パーツのマトリと親マトリをかけ合わせる
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxParent);

				//"プレイヤーの"ワールドマトリックス設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//マテリアルデータへのポインタ取得
				pMat = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].dwNumMatModel; nCntMat++)
				{
					//ゾンさんは緑
					//マテリアル設定
					D3DMATERIAL9 changeMat = pMat[nCntMat].MatD3D;
					//ダメージ状態なら赤追加
					changeMat.Diffuse = D3DXCOLOR(0.0f, 0.45f, 0.13f, 1.0f);

					if (g_aEnemy[nCntEnemy].state == OBJSTATE_DAMAGE)
					{
						changeMat.Diffuse.r = 1.0f * OBJ_RED_ALPHA + changeMat.Diffuse.r * (1.0f - OBJ_RED_ALPHA);
						changeMat.Diffuse.g = 0.0f * OBJ_RED_ALPHA + changeMat.Diffuse.g * (1.0f - OBJ_RED_ALPHA);
						changeMat.Diffuse.b = 0.0f * OBJ_RED_ALPHA + changeMat.Diffuse.b * (1.0f - OBJ_RED_ALPHA);
					}

					//マテリアル設定
					pDevice->SetMaterial(&changeMat);

					//テクスチャ設定
					pDevice->SetTexture(0, g_aEnemy[nCntEnemy].aModel[nCntModel].apTexture[nCntMat]);

					//モデル描画
					g_aEnemy[nCntEnemy].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}
			}
		}
	}

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//========================
//設定処理
//========================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELNAME name, int nLife)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			Model *pModel = GetModel(name);
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].rot = rot;
			g_aEnemy[nCntEnemy].nLife = nLife;
			for (int nCntParts = 0; nCntParts < EXITHUMAN_MODEL_NUM; nCntParts++)
			{
				g_aEnemy[nCntEnemy].aModel[nCntParts] = *(pModel + nCntParts);
			}

			//自動設定
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[nCntEnemy].nIdxShadow = SetShadow();
			g_aEnemy[nCntEnemy].bUse = true;

			break;
		}
	}
}

//========================
//壁当たり判定処理
//========================
void CollisionWallEnemy(int nNumber)
{
	Wall *wall = GetWall();
	D3DXVECTOR3 pos0, pos1;
	D3DXVECTOR3 vecMove, vecLine;
	D3DXVECTOR3 vecToPos, vecToPosOld;
	float fAreaA, fAreaB;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, wall++)
	{
		//使っているときだけ処理
		if (wall->bUse == true)
		{
			//移動ベクトル
			vecMove = g_aEnemy[nNumber].pos - g_aEnemy[nNumber].posOld;

			//位置計算
			pos0.x = wall->pos.x - (wall->fWidth / 2) * cosf(wall->rot.y);
			pos0.y = 0.0f;
			pos0.z = wall->pos.z + (wall->fWidth / 2) * sinf(wall->rot.y);

			pos1.x = wall->pos.x + (wall->fWidth / 2) * cosf(wall->rot.y);
			pos1.y = 0.0f;
			pos1.z = wall->pos.z - (wall->fWidth / 2) * sinf(wall->rot.y);

			vecLine = pos1 - pos0;	//境界線ベクトル
			vecToPos = g_aEnemy[nNumber].pos - pos0;
			vecToPosOld = g_aEnemy[nNumber].posOld - pos0;

			//面積求める
			fAreaA = (vecToPos.z * vecMove.x) - (vecToPos.x * vecMove.z);
			fAreaB = (vecLine.z * vecMove.x) - (vecLine.x * vecMove.z);

			if ((vecLine.z * vecToPosOld.x) - (vecLine.x * vecToPosOld.z) >= 0.0f && (vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) < 0.0f)
			{
				if (fAreaA / fAreaB >= 0.0f && fAreaA / fAreaB <= 1.0f)
				{//ごっつん
					float fRate = fAreaA / fAreaB;
					g_aEnemy[nNumber].pos.x = pos0.x + (vecLine.x * fRate) - sinf(wall->rot.y) / D3DX_PI * PUSHING_BACK;
					g_aEnemy[nNumber].pos.z = pos0.z + (vecLine.z * fRate) - cosf(wall->rot.y) / D3DX_PI * PUSHING_BACK;
					break;
				}
			}
		}
	}
}

//========================
//オブジェクト当たり判定処理
//========================
void CollisionObjEnemy(int nNumber)
{
	//=pos0~pos3の説明==================
	// pos3		pos2
	//	・<-----・		矢印:vecLine
	//	｜		↑
	//	｜		｜
	//	↓		｜
	//	・----->・
	// pos0		pos1
	//==================================

	BluePrint *pbprint = GetBluePrint();
	Object *pObject = GetObj();
	D3DXVECTOR3 pos0, pos1, pos2, pos3;
	D3DXVECTOR3 vecLineRight, vecToPosRight, vecToPosOldRight;
	D3DXVECTOR3 vecLineLeft, vecToPosLeft, vecToPosOldLeft;
	D3DXVECTOR3 vecLineUp, vecToPosUp, vecToPosOldUp;
	D3DXVECTOR3 vecLineDown, vecToPosDown, vecToPosOldDown;
	D3DXVECTOR3 vecMove;
	float fAreaARight, fAreaALeft, fAreaBRight, fAreaBLeft;
	float fAreaAUp, fAreaADown, fAreaBUp, fAreaBDown;


	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++, pObject++)
	{
		if (pObject->bUse == true)
		{
			//各頂点求める
			float fLengthX, fLengthZ;
			float fLength;
			float fAngle;
			float rot;

			//-pos0---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMin.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMin.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
																	//0 - 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(-fAngle - pObject->rot.y);

			//角度に応じて頂点の位置をずらす
			pos0.x = pObject->pos.x + sinf(rot) * fLength;
			pos0.y = 0.0f;
			pos0.z = pObject->pos.z - cosf(rot) * fLength;
			//-pos0---------------------------------------------------------------------------------------------------------------------------

			//-pos1---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMax.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMin.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
																	//0 + 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(-fAngle - pObject->rot.y);

			//角度に応じて頂点の位置をずらす
			pos1.x = pObject->pos.x + sinf(rot) * fLength;
			pos1.y = 0.0f;
			pos1.z = pObject->pos.z - cosf(rot) * fLength;
			//-pos1---------------------------------------------------------------------------------------------------------------------------

			//-pos2---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMax.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMax.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
																	//PI - 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(D3DX_PI - fAngle - pObject->rot.y);

			//角度に応じて頂点の位置をずらす
			pos2.x = pObject->pos.x - sinf(rot) * fLength;
			pos2.y = 0.0f;
			pos2.z = pObject->pos.z + cosf(rot) * fLength;
			//-pos2---------------------------------------------------------------------------------------------------------------------------

			//-pos3---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMin.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMax.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
																	//-PI + 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(-D3DX_PI - fAngle - pObject->rot.y);

			//角度に応じて頂点の位置をずらす
			pos3.x = pObject->pos.x - sinf(rot) * fLength;
			pos3.y = 0.0f;
			pos3.z = pObject->pos.z + cosf(rot) * fLength;
			//-pos3---------------------------------------------------------------------------------------------------------------------------

			//ベクトル求める
			//move
			vecMove = g_aEnemy[nNumber].pos - g_aEnemy[nNumber].posOld;

			//X
			//右方向の計算
			vecLineRight = pos1 - pos0;
			vecToPosRight = g_aEnemy[nNumber].pos - pos0;
			vecToPosOldRight = g_aEnemy[nNumber].posOld - pos0;

			//左方向の計算
			vecLineLeft = pos3 - pos2;
			vecToPosLeft = g_aEnemy[nNumber].pos - pos2;
			vecToPosOldLeft = g_aEnemy[nNumber].posOld - pos2;

			//Z
			//上方向の計算
			vecLineUp = pos2 - pos1;
			vecToPosUp = g_aEnemy[nNumber].pos - pos1;
			vecToPosOldUp = g_aEnemy[nNumber].posOld - pos1;
			//下方向の計算
			vecLineDown = pos0 - pos3;
			vecToPosDown = g_aEnemy[nNumber].pos - pos3;
			vecToPosOldDown = g_aEnemy[nNumber].posOld - pos3;

			//当たり判定本番
			//X
			//面積求める
			fAreaARight = (vecToPosRight.z * vecMove.x) - (vecToPosRight.x * vecMove.z);
			fAreaALeft = (vecToPosLeft.z * vecMove.x) - (vecToPosLeft.x * vecMove.z);
			fAreaBRight = (vecLineRight.z * vecMove.x) - (vecLineRight.x * vecMove.z);
			fAreaBLeft = (vecLineLeft.z * vecMove.x) - (vecLineLeft.x * vecMove.z);

			//左側AND範囲内vecToPosOldOps
			if ((vecLineRight.z * vecToPosOldRight.x) - (vecLineRight.x * vecToPosOldRight.z) >= 0.0f && (vecLineRight.z * vecToPosRight.x) - (vecLineRight.x * vecToPosRight.z) < 0.0f)
			{
				if (fAreaARight / fAreaBRight >= 0.0f && fAreaARight / fAreaBRight <= 1.0f)
				{//ごっつん
					float fRate = fAreaARight / fAreaBRight;
					g_aEnemy[nNumber].pos.x = pos0.x + (vecLineRight.x * fRate) - sinf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					g_aEnemy[nNumber].pos.z = pos0.z + (vecLineRight.z * fRate) - cosf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					break;
				}
			}
			else if ((vecLineLeft.z * vecToPosOldLeft.x) - (vecLineLeft.x * vecToPosOldLeft.z) >= 0.0f && (vecLineLeft.z * vecToPosLeft.x) - (vecLineLeft.x * vecToPosLeft.z) < 0.0f)
			{
				if (fAreaALeft / fAreaBLeft >= 0.0f && fAreaALeft / fAreaBLeft <= 1.0f)
				{//ごっつん
					float fRate = fAreaALeft / fAreaBLeft;
					g_aEnemy[nNumber].pos.x = pos2.x + (vecLineLeft.x * fRate) + sinf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					g_aEnemy[nNumber].pos.z = pos2.z + (vecLineLeft.z * fRate) + cosf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					break;
				}
			}

			//Z
			//面積求める
			fAreaAUp = (vecToPosUp.z * vecMove.x) - (vecToPosUp.x * vecMove.z);
			fAreaADown = (vecToPosDown.z * vecMove.x) - (vecToPosDown.x * vecMove.z);
			fAreaBUp = (vecLineUp.z * vecMove.x) - (vecLineUp.x * vecMove.z);
			fAreaBDown = (vecLineDown.z * vecMove.x) - (vecLineDown.x * vecMove.z);

			//左側AND範囲内vecToPosOldOps
			if ((vecLineUp.z * vecToPosOldUp.x) - (vecLineUp.x * vecToPosOldUp.z) >= 0.0f && (vecLineUp.z * vecToPosUp.x) - (vecLineUp.x * vecToPosUp.z) < 0.0f)
			{
				if (fAreaAUp / fAreaBUp >= 0.0f && fAreaAUp / fAreaBUp <= 1.0f)
				{//ごっつん
					float fRate = fAreaAUp / fAreaBUp;
					g_aEnemy[nNumber].pos.x = pos1.x + (vecLineUp.x * fRate) + cosf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					g_aEnemy[nNumber].pos.z = pos1.z + (vecLineUp.z * fRate) - sinf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					break;
				}
			}
			else if ((vecLineDown.z * vecToPosOldDown.x) - (vecLineDown.x * vecToPosOldDown.z) >= 0.0f && (vecLineDown.z * vecToPosDown.x) - (vecLineDown.x * vecToPosDown.z) < 0.0f)
			{
				if (fAreaADown / fAreaBDown >= 0.0f && fAreaADown / fAreaBDown <= 1.0f)
				{//ごっつん
					float fRate = fAreaADown / fAreaBDown;
					g_aEnemy[nNumber].pos.x = pos3.x + (vecLineDown.x * fRate) - cosf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					g_aEnemy[nNumber].pos.z = pos3.z + (vecLineDown.z * fRate) + sinf(pObject->rot.y) / D3DX_PI * PUSHING_BACK;
					break;
				}
			}
		}
	}
}

//========================
//取得処理
//========================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//========================
//当たった時の処理
//========================
void HitEnemy(int nNumber)
{
	g_aEnemy[nNumber].nLife--;

	if (g_aEnemy[nNumber].nLife <= 0)
	{//ぶっこわーす処理
		DestroyEnemy(nNumber);
	}
	else
	{
		g_aEnemy[nNumber].state = OBJSTATE_DAMAGE;
		g_aEnemy[nNumber].nCounterState = OBJ_DAMAGE_TIME;
	}
}

//========================
//ぶっこわーす処理
//========================
void DestroyEnemy(int nNumber)
{
	g_aEnemy[nNumber].bUse = false;
	ReleaseIdxShadow(g_aEnemy[nNumber].nIdxShadow);
}