#include <stdio.h>
#include "fmfmap.h"

//-----------------------------------------------------------------------------
//	コンストラクタ
//-----------------------------------------------------------------------------
CFmfMap::CFmfMap(void) : m_pLayerAddr(NULL)
{}
//-----------------------------------------------------------------------------
//	デストラクタ
//-----------------------------------------------------------------------------
CFmfMap::~CFmfMap()
{
	Close();
}
//-----------------------------------------------------------------------------
//	マップを開いてデータを読み込む
// 引数：	szFilePath	= マップファイルのパス
// 戻り値:	正常終了	= TRUE
//			エラー		= FALSE
//-----------------------------------------------------------------------------
BOOL CFmfMap::Open(const char* szFilePath)
{
	Close();
	FILE* fp;
	// ファイルを開く
	fopen_s(&fp, szFilePath, "rb");
	if (!fp) return FALSE;

	// ヘッダ情報を読む
	fread(&m_fmfHeader, sizeof(FMFHEADER), 1, fp);

	// 識別子のチェック
	if (memcmp(&m_fmfHeader.dwIdentifier, "FMF_", 4) != 0)
		goto error_return;

	// メモリ確保
	m_pLayerAddr = new BYTE[m_fmfHeader.dwSize];
	if (m_pLayerAddr == NULL)
		goto error_return;

	// レイヤーデータを読む
	fread(m_pLayerAddr, m_fmfHeader.dwSize, 1, fp);


	// 正常終了
	fclose(fp);
	return TRUE;

error_return:
	// エラー終了
	fclose(fp);
	Close();
	return FALSE;
}
//-----------------------------------------------------------------------------
// マップが開かれているか
//-----------------------------------------------------------------------------
BOOL CFmfMap::IsOpen() const
{
	return m_pLayerAddr != NULL;
}
//-----------------------------------------------------------------------------
//	マップメモリを開放
//-----------------------------------------------------------------------------
void CFmfMap::Close(void)
{
	if (m_pLayerAddr != NULL)
	{
		delete[] m_pLayerAddr;
		m_pLayerAddr = NULL;
	}
}
//-----------------------------------------------------------------------------
//	指定レイヤの先頭アドレスを得る
//	引数：	レイヤ番号
//	戻り値:	正常終了	= レイヤデータのアドレス
//			エラー		= NULL
//	各レイヤデータは連続したメモリ領域に配置されてるので
//	指定レイヤデータのアドレスを計算で求める。
//-----------------------------------------------------------------------------
void* CFmfMap::GetLayerAddr(BYTE byLayerIndex) const
{
	// メモリチェック、範囲チェック
	if ((m_pLayerAddr == NULL) || (byLayerIndex >= m_fmfHeader.byLayerCount))
		return NULL;

	BYTE bySize = m_fmfHeader.byBitCount / 8;
	return m_pLayerAddr + m_fmfHeader.dwWidth * m_fmfHeader.dwHeight * bySize * byLayerIndex;
}
//-----------------------------------------------------------------------------
// レイヤ番号と座標を指定して直接データを貰う
// 引数：
// 	byLayerIndex	= レイヤ番号
// 	dwX				= X座標（0～m_fmfHeader.dwWidth - 1）
// 	dwY				= Y座標（0～m_fmfHeader.dwHeight - 1）
// 戻り値：
// 	正常終了	= 座標の値
//	エラー		= -1
//-----------------------------------------------------------------------------
int CFmfMap::GetValue(BYTE byLayerIndex, DWORD dwX, DWORD dwY) const
{
	int nIndex = -1;

	// 範囲チェック
	if (byLayerIndex >= m_fmfHeader.byLayerCount ||
		dwX >= m_fmfHeader.dwWidth ||
		dwY >= m_fmfHeader.dwHeight)
		return nIndex;

	if (m_fmfHeader.byBitCount == 8)
	{
		// 8bit layer
		BYTE* pLayer = (BYTE*)GetLayerAddr(byLayerIndex);
		nIndex = *(pLayer + dwY * m_fmfHeader.dwWidth + dwX);
	}
	else
	{
		// 16bit layer	
		WORD* pLayer = (WORD*)GetLayerAddr(byLayerIndex);
		nIndex = *(pLayer + dwY * m_fmfHeader.dwWidth + dwX);
	}

	return nIndex;
}

//-----------------------------------------------------------------------------
// レイヤ番号と座標を指定してデータをセット
//-----------------------------------------------------------------------------
void CFmfMap::SetValue(BYTE byLayerIndex, DWORD dwX, DWORD dwY, int nValue)
{
	// 範囲チェック
	if (byLayerIndex >= m_fmfHeader.byLayerCount ||
		dwX >= m_fmfHeader.dwWidth ||
		dwY >= m_fmfHeader.dwHeight)
		return;

	if (m_fmfHeader.byBitCount == 8)
	{
		// 8bit layer
		BYTE* pLayer = (BYTE*)GetLayerAddr(byLayerIndex);
		*(pLayer + dwY * m_fmfHeader.dwWidth + dwX) = (BYTE)nValue;
	}
	else
	{
		// 16bit layer	
		WORD* pLayer = (WORD*)GetLayerAddr(byLayerIndex);
		*(pLayer + dwY * m_fmfHeader.dwWidth + dwX) = (WORD)nValue;
	}
}

//-----------------------------------------------------------------------------
// マップの横幅を得る
//-----------------------------------------------------------------------------
DWORD CFmfMap::GetMapWidth(void) const
{
	return m_fmfHeader.dwWidth;
}
//-----------------------------------------------------------------------------
// マップの高さを得る
//-----------------------------------------------------------------------------
DWORD CFmfMap::GetMapHeight(void) const
{
	return m_fmfHeader.dwHeight;
}
//-----------------------------------------------------------------------------
// チップの横幅を得る
//-----------------------------------------------------------------------------
BYTE CFmfMap::GetChipWidth(void) const
{
	return m_fmfHeader.byChipWidth;
}
//-----------------------------------------------------------------------------
// チップの高さを得る
//-----------------------------------------------------------------------------
BYTE CFmfMap::GetChipHeight(void) const
{
	return m_fmfHeader.byChipHeight;
}
//-----------------------------------------------------------------------------
// レイヤー数を得る
//-----------------------------------------------------------------------------
BYTE CFmfMap::GetLayerCount(void) const
{
	return m_fmfHeader.byLayerCount;
}
//-----------------------------------------------------------------------------
// レイヤーデータのビットカウントを得る
//-----------------------------------------------------------------------------
BYTE CFmfMap::GetLayerBitCount(void) const
{
	return m_fmfHeader.byBitCount;
}