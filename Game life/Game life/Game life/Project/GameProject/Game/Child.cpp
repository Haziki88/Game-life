#include "Child.h"
#include"Player.h"

Child::Child(const CVector2D& pos)
	:Base(eType_Child)
{
	m_pos = pos;
	m_rad = 16.0f;
	m_parent = nullptr;
}

Child::~Child()
{
	//親があれば、親のリストから外してもらう
	if (m_parent)
		m_parent->EraseChild(this);
}

void Child::Update()
{
	//子で動かしているが、親から子の座標を指定する場合もある
	//親があれば
	if (m_parent) {
		const float speed = 4;
		CVector2D vec = m_parent->m_pos - m_pos;
		//親との距離が64より遠ければ
		if (vec.Length() > 64) {
			m_ang = atan2(vec.x, vec.y);
			CVector2D dir(sin(m_ang), cos(m_ang));
			//親の方向へ移動
			m_pos += dir * speed;
		}
	}
}

void Child::Draw()
{
	//緑
	CVector4D color(0, 1, 0, 1);
	//親があれば黄色
	if (m_parent)
		color = CVector4D(1, 1, 0, 1);
	Utility::DrawCircle(GetScreenPos(m_pos), m_rad, color);
}
