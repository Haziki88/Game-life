#include "Goal.h"
Goal::Goal(const CVector2D& pos) :Base(eType_Goal) {
	m_img = COPY_RESOURCE("chest_3", CImage);
	m_img.SetCenter(16,16);
	m_pos = pos;
	m_rect = CRect(-16, -16, 16, 16);
	m_img.SetSize(32, 32);
}

void Goal::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}