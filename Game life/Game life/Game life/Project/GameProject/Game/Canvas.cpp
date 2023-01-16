#include "Canvas.h"
Canvas::Canvas(const CVector2D& screen_size) :Base(eType_Canvas) {
	m_screen_size = screen_size;
}

void Canvas::Draw() {

	//スクリーンサイズを元に戻す
	CCamera::GetCamera()->SetSize(m_screen_size.x, m_screen_size.y);



}