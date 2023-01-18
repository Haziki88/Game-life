#pragma once
#include "../Base/Base.h"

class Gameover : public Base {
	//画像オブジェクト
	CImage m_img;
	//文字表示オブジェクト
	CFont m_title_text;
public:
	Gameover();
	~Gameover();
	void Update();
	void Draw();
};