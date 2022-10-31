#pragma once
#include "../Base/Base.h"

class Effect : public Base {
private:
	//画像オブジェクト
	CImage m_img;
	//反転フラグ
	bool	m_flip;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="name">リソース名</param>
	/// <param name="p">位置</param>
	/// <param name="flip">反転フラグ</param>
	/// <returns></returns>
	Effect(const char *name,const CVector2D& p, bool flip);
	void Update();
	void Draw();
};