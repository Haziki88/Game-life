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
	//�e������΁A�e�̃��X�g����O���Ă��炤
	if (m_parent)
		m_parent->EraseChild(this);
}

void Child::Update()
{
	//�q�œ������Ă��邪�A�e����q�̍��W���w�肷��ꍇ������
	//�e�������
	if (m_parent) {
		const float speed = 4;
		CVector2D vec = m_parent->m_pos - m_pos;
		//�e�Ƃ̋�����64��艓�����
		if (vec.Length() > 64) {
			m_ang = atan2(vec.x, vec.y);
			CVector2D dir(sin(m_ang), cos(m_ang));
			//�e�̕����ֈړ�
			m_pos += dir * speed;
		}
	}
}

void Child::Draw()
{
	//��
	CVector4D color(0, 1, 0, 1);
	//�e������Ή��F
	if (m_parent)
		color = CVector4D(1, 1, 0, 1);
	Utility::DrawCircle(GetScreenPos(m_pos), m_rad, color);
}
