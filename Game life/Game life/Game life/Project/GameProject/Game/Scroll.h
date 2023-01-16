#pragma once
#include "../Base/Base.h"
class Scroll :public Base {
private:
	Base* m_player;
	
	CVector2D m_screen_size;
public:
	Scroll(const CVector2D& screen_size);
	void Draw();
};