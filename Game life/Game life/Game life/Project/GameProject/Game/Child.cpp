#include "Child.h"
#include"Player.h"
#include"AnimData.h"

Child::Child(const CVector2D& pos)
	:Base(eType_Child)
{
	m_img = COPY_RESOURCE("Wizzard", CImage);
	m_img.ChangeAnimation(0);
	m_pos = pos;
	//中心位置設定
	m_img.SetCenter(32, 32);
	m_state = eState_Idle;
	m_rad = 16.0f;
	m_parent = nullptr;
}

Child::~Child()
{
	//親があれば、親のリストから外してもらう
	if (m_parent)
		m_parent->EraseChild(this);
}
void Child::StateIdle()
{
	bool move_flag = false;
	if (m_parent) {
		const float speed = 4;
		CVector2D vec = m_parent->m_pos - m_pos;
		//親との距離が64より遠ければ
		if (vec.Length() > 64) {
			m_ang = atan2(vec.x, vec.y);
			CVector2D dir(sin(m_ang), cos(m_ang));
			//親の方向へ移動
			m_pos += dir * speed;
			move_flag = true;
		}
	}
	if (move_flag) {
		//走るアニメーション
		m_img.ChangeAnimation(eAnimRun);
	}
	else {
		//待機アニメーション
		m_img.ChangeAnimation(eAnimIdle);
	}
}

void Child::StateDown()
{
}
void Child::Update()
{
	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Down:
		StateDown();
		break;

	}
	m_img.UpdateAnimation();
}

void Child::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	//緑
	CVector4D color(0, 1, 0, 1);
	//親があれば黄色
	if (m_parent)
		color = CVector4D(1, 1, 0, 1);
	Utility::DrawCircle(GetScreenPos(m_pos), m_rad, color);
	m_img.Draw();
}
