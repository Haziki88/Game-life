#pragma once
#include "../Base/Base.h"
/// <summary>
/// ‰æ–Ê‰ð‘œ“x‚ðŒ³‚É–ß‚·ƒNƒ‰ƒX
/// </summary>
class Canvas :public Base {
private:
	CVector2D m_screen_size;
public:
	Canvas(const CVector2D& screen_size);
	void Draw();
};