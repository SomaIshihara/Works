//==========================================
//
//モデル関係プログラム[object.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "object.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"

//マクロ
#define OBJ_MOVE_SPEED		(1.0f)	//モデル移動速度

//グローバル変数
BluePrint g_aBPrint[BLUEPRINTIDX_MAX];
Object g_aObject[MAX_OBJECT];
int g_nNumObj = 0;

//ファイルパス
const char* c_apFilePathObject[] =
{
	"data\\MODEL\\jobi.x",
	"data\\MODEL\\subway_entrance.x",
	"data\\MODEL\\Rock_xfile\\Rock_01.x",
	"data\\MODEL\\Rock_xfile\\Rock_02.x",
	"data\\MODEL\\Rock_xfile\\Rock_03.x",
	"data\\MODEL\\Rock_xfile\\Rock_04.x",
	"data\\MODEL\\Rock_xfile\\Rock_05.x",
	"data\\MODEL\\Rock_xfile\\Rock_06.x",
	"data\\MODEL\\Rock_xfile\\Rock_07.x",
	"data\\MODEL\\Rock_xfile\\Rock_08.x",
	"data\\MODEL\\Rock_xfile\\Rock_09.x",
	"data\\MODEL\\Rock_xfile\\Rock_10.x",
	"data\\MODEL\\Rock_xfile\\Rock_11.x",
	"data\\MODEL\\building002.x",
	"data\\MODEL\\building102.x",
	"data\\MODEL\\building202.x",
	"data\\MODEL\\building302.x",
	"data\\MODEL\\building402.x",
	"data\\MODEL\\building502.x"
};

//========================
//初期化処理
//========================
void InitObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATERIAL *pMat;	//マテリアルポインタ
	int nNumVtx;		//頂点数
	DWORD dwSizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファポインタ

	//変数初期化
	for (int nCntInitBP = 0; nCntInitBP < BLUEPRINTIDX_MAX; nCntInitBP++)
	{
		g_aBPrint[nCntInitBP].dwNumMat = 0;
		g_aBPrint[nCntInitBP].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBPrint[nCntInitBP].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	for (int nCntInitOBJ = 0; nCntInitOBJ < MAX_OBJECT; nCntInitOBJ++)
	{
		g_aObject[nCntInitOBJ].bpidx = {};
		g_aObject[nCntInitOBJ].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntInitOBJ].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntInitOBJ].bLifeUse = true;
		g_aObject[nCntInitOBJ].nLife = 0;
		g_aObject[nCntInitOBJ].state = OBJSTATE_BROKEN;
		g_aObject[nCntInitOBJ].nCounterState = 0;
		g_aObject[nCntInitOBJ].nIdxShadow = -1;
		g_aObject[nCntInitOBJ].bUse = false;
	}

	//読み込み
	for (int nCntModel = 0; nCntModel < BLUEPRINTIDX_MAX && nCntModel < (sizeof c_apFilePathObject / sizeof(char *)); nCntModel++)
	{
		//Xファイル読み込み		
		if (SUCCEEDED(D3DXLoadMeshFromX(
			c_apFilePathObject[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aBPrint[nCntModel].pBuffMat,
			NULL,
			&g_aBPrint[nCntModel].dwNumMat,
			&g_aBPrint[nCntModel].pMesh)))
		{
			//頂点数を取得
			nNumVtx = g_aBPrint[nCntModel].pMesh->GetNumVertices();

			//頂点フォーマット
			dwSizeFVF = D3DXGetFVFVertexSize(g_aBPrint[nCntModel].pMesh->GetFVF());

			//頂点バッファロック
			g_aBPrint[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void **)&pVtxBuff);

			//最初だけ全部入れる
			D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

			g_aBPrint[nCntModel].vtxMax = vtx;
			g_aBPrint[nCntModel].vtxMin = vtx;

			pVtxBuff += dwSizeFVF;

			for (int nCntVtx = 1; nCntVtx < nNumVtx; nCntVtx++, pVtxBuff += dwSizeFVF)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

				if (g_aBPrint[nCntModel].vtxMax.x < vtx.x)
				{
					g_aBPrint[nCntModel].vtxMax.x = vtx.x;
				}
				if (g_aBPrint[nCntModel].vtxMax.z < vtx.z)
				{
					g_aBPrint[nCntModel].vtxMax.z = vtx.z;
				}
				if (g_aBPrint[nCntModel].vtxMin.x > vtx.x)
				{
					g_aBPrint[nCntModel].vtxMin.x = vtx.x;
				}
				if (g_aBPrint[nCntModel].vtxMin.z > vtx.z)
				{
					g_aBPrint[nCntModel].vtxMin.z = vtx.z;
				}
			}

			//頂点バッファアンロック
			g_aBPrint[nCntModel].pMesh->UnlockVertexBuffer();

			//テクスチャ読み込み
			//マテリアル情報に対するポインタ取得
			pMat = (D3DXMATERIAL *)g_aBPrint[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntTex = 0; nCntTex < (int)g_aBPrint[nCntModel].dwNumMat; nCntTex++)
			{
				if (pMat[nCntTex].pTextureFilename != NULL)
				{
					//テクスチャ読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntTex].pTextureFilename,
						&g_aBPrint[nCntModel].apTexture[nCntTex]);
				}
			}
		}
		else
		{
			break;
		}
	}

	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		g_aObject[nCntObj].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntObj].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntObj].state = OBJSTATE_MAX;
		g_aObject[nCntObj].nLife = 5;
		g_aObject[nCntObj].nCounterState = 0;
		g_aObject[nCntObj].nIdxShadow = -1;
		g_aObject[nCntObj].bUse = false;
	}
	
	//オブジェクト使用数を0に
	g_nNumObj = 0;
}

//========================
//終了処理
//========================
void UninitObject(void)
{
	for (int nCount = 0; nCount < BLUEPRINTIDX_MAX; nCount++)
	{
		//テクスチャ破棄
		for (int nCntUniniTex = 0; nCntUniniTex < OBJ_MAX_TEXTURE; nCntUniniTex++)
		{
			if (g_aBPrint[nCount].apTexture[nCntUniniTex] != NULL)
			{
				g_aBPrint[nCount].apTexture[nCntUniniTex]->Release();
				g_aBPrint[nCount].apTexture[nCntUniniTex] = NULL;
			}
		}
		//メッシュの破棄
		if (g_aBPrint[nCount].pMesh != NULL)
		{
			g_aBPrint[nCount].pMesh->Release();
			g_aBPrint[nCount].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_aBPrint[nCount].pBuffMat != NULL)
		{
			g_aBPrint[nCount].pBuffMat->Release();
			g_aBPrint[nCount].pBuffMat = NULL;
		}
	}
}

//========================
//更新処理
//========================
void UpdateObject(void)
{
	//オブジェクト処理
	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		if (g_aObject[nCount].bUse == true)
		{
			//状態に応じて処理
			switch (g_aObject[nCount].state)
			{
			case OBJSTATE_NONE:
				break;
			case OBJSTATE_DAMAGE:
				g_aObject[nCount].nCounterState--;
				if (g_aObject[nCount].nCounterState <= 0)
				{
					g_aObject[nCount].state = OBJSTATE_NONE;
				}
				break;
			case OBJSTATE_BROKEN:
				break;
			}

			//影位置設定
			SetPositionShadow(g_aObject[nCount].nIdxShadow, g_aObject[nCount].pos);
		}
	}

	//操作
	if (GetKeyboardTrigger(DIK_F5) == true && g_nNumObj == 0)
	{
		//オブジェクト生成
		//今は何もしない
	}
}

//========================
//描画処理
//========================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		if (g_aObject[nCount].bUse == true)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&g_aObject[nCount].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObject[nCount].rot.y, g_aObject[nCount].rot.x, g_aObject[nCount].rot.z);
			D3DXMatrixMultiply(&g_aObject[nCount].mtxWorld, &g_aObject[nCount].mtxWorld, &mtxRot);

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aObject[nCount].pos.x, g_aObject[nCount].pos.y, g_aObject[nCount].pos.z);
			D3DXMatrixMultiply(&g_aObject[nCount].mtxWorld, &g_aObject[nCount].mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aObject[nCount].mtxWorld);

			//マテリアルデータへのポインタ取得
			pMat = (D3DXMATERIAL*)g_aBPrint[g_aObject[nCount].bpidx].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBPrint[g_aObject[nCount].bpidx].dwNumMat; nCntMat++)
			{
				//マテリアル設定
				D3DMATERIAL9 changeMat = pMat[nCntMat].MatD3D;
				//ダメージ状態なら赤追加
				if (g_aObject[nCount].state == OBJSTATE_DAMAGE)
				{
					changeMat.Diffuse.r = 1.0f * OBJ_RED_ALPHA + pMat[nCntMat].MatD3D.Diffuse.r * (1.0f - OBJ_RED_ALPHA);
					changeMat.Diffuse.g = 0.0f * OBJ_RED_ALPHA + pMat[nCntMat].MatD3D.Diffuse.g * (1.0f - OBJ_RED_ALPHA);
					changeMat.Diffuse.b = 0.0f * OBJ_RED_ALPHA + pMat[nCntMat].MatD3D.Diffuse.b * (1.0f - OBJ_RED_ALPHA);
				}
				pDevice->SetMaterial(&changeMat);

				//テクスチャ設定
				pDevice->SetTexture(0, g_aBPrint[g_aObject[nCount].bpidx].apTexture[nCntMat]);

				//モデル描画
				g_aBPrint[g_aObject[nCount].bpidx].pMesh->DrawSubset(nCntMat);
			}
		}
	}
	
	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//========================
//表示処理
//========================
void SetObject(BLUEPRINTIDX bpidx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bLifeUse, int nLife)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		if (g_aObject[nCntObj].bUse == false)
		{
			//引数の情報を追加
			g_aObject[nCntObj].bpidx = bpidx;
			g_aObject[nCntObj].pos = pos;
			g_aObject[nCntObj].rot = rot;
			g_aObject[nCntObj].bLifeUse = bLifeUse;
			g_aObject[nCntObj].nLife = nLife;

			//体力を使用する場合のみ影設定
			if (g_aObject[nCntObj].bLifeUse == true)
			{
				//影設定
				g_aObject[nCntObj].nIdxShadow = SetShadow();
			}

			//使用していることにする
			g_aObject[nCntObj].bUse = true;

			//オブジェクト数増やす
			g_nNumObj++;

			//抜ける
			break;
		}
	}
}

//========================
//オブジェクト取得処理
//========================
Object *GetObj(void)
{
	return &g_aObject[0];
}

//========================
//設計図取得処理
//========================
BluePrint *GetBluePrint(void)
{
	return &g_aBPrint[0];
}

//========================
//当たった時の処理
//========================
void HitObj(int nNumObj)
{
	//体力の項目を使用するならダメージ
	if (g_aObject[nNumObj].bLifeUse == true)
	{
		g_aObject[nNumObj].nLife--;

		if (g_aObject[nNumObj].nLife <= 0)
		{//ぶっこわーす処理
			DestroyObj(nNumObj);
			ReleaseIdxShadow(g_aObject[nNumObj].nIdxShadow);
		}
		else
		{
			g_aObject[nNumObj].state = OBJSTATE_DAMAGE;
			g_aObject[nNumObj].nCounterState = OBJ_DAMAGE_TIME;
		}
	}
}

//========================
//ぶっこわーす処理
//========================
void DestroyObj(int nNumObj)
{
	g_aObject[nNumObj].bUse = false;
	g_nNumObj--;
}