#pragma once
#include "../Base/Base.h"
class Goal :public Base {
private:
	//画像オブジェクト
	CImage m_img;

public:
	Goal(const CVector2D& pos);
	void Draw();
};