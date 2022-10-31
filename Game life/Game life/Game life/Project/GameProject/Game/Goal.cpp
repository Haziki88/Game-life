#include "Goal.h"
Goal::Goal(const CVector2D& pos) :Base(eType_Goal) {
	m_img = COPY_RESOURCE("Goal", CImage);
	m_img.SetCenter(32, 128);
	m_pos = pos;
	m_rect = CRect(-32, -128, 32, 0);
	m_img.SetSize(64, 128);
}

void Goal::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}