#include "Player.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash.h"
#include "Effect.h"
#include"Map.h"
#include"Child.h"
#include"AreaChange.h"
Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	//�摜����
	m_img = COPY_RESOURCE("Knight", CImage);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos_old=m_pos = p;
	//���S�ʒu�ݒ�
	m_img.SetCenter(44, 54);
	//��`�ݒ�
	m_rect = CRect(-9, -28, 9, 0);
	//���]�t���O
	m_flip = flip;
	//�ʏ��Ԃ�
	m_state = eState_Idle;
	//���n�t���O
	m_is_ground=true;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
	m_damage_no = -1;
	//
	m_hp = 100;
	m_rad = 32.0f;
	m_path_idx = 0;

}
Player::~Player()
{

}
void Player::StateIdle()
{
	//�ړ���
	const float move_speed = 4;
	//�ړ��t���O
	bool move_flag = false;
	//�W�����v��
	const float jump_pow = 12;

	CVector2D mousePos = (CInput::GetMousePoint() + m_scroll-CVector2D(640,150))*m_scale;
	if (mousePos.x > m_pos.x) {
		m_flip = false;
	}
	else if(mousePos.x<m_pos.x) {
		m_flip = true;
	}
	//�ړ�
	
		if (PUSH(CInput::eMouseL)) {
			if (Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Field))) {
				m_path.FindShortestPath(m,m_pos, mousePos);
				
				m_path_idx = 0;
			}
		}
	
		
	if (m_path_idx < m_path.GetPathSize()) {
		CVector2D vec = m_path.GetPathPoint(m_path_idx) - m_pos;
		if (vec.Length() > 8) {
			m_ang = atan2(vec.x, vec.y);
			CVector2D dir(sin(m_ang), cos(m_ang));
			m_pos += dir * move_speed;
			move_flag = true;
		}
		else {
			m_path_idx++;
		}
	}
	
	//�W�����v
	/*if (m_is_ground && PUSH(CInput::eButton2)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
	}*/

	//�U��
		//�U����Ԃֈڍs

	//�U��
	if (PUSH(CInput::eMouseR)) {
		//�U����Ԃֈڍs
		m_state = eState_Attack;
		m_attack_no++;
	}

	//�W�����v���Ȃ�
	if (!m_is_ground) {
		/*if (m_vec.y < 0)
			//�㏸�A�j���[�V����
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else
			//���~�A�j���[�V����
			m_img.ChangeAnimation(eAnimJumpDown, false);*/
	}
	//�ړ����Ȃ�
	else
	{
		if (move_flag) {
			//����A�j���[�V����
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			//�ҋ@�A�j���[�V����
			m_img.ChangeAnimation(eAnimIdle);
		}

	}


}
void Player::StateAttack()
{
	//�U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttack01, false);
	//2�Ԗڂ̃p�^�[���Ȃ�
	//if (m_img.GetIndex() == 2) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-32, -16), m_flip, eType_Player_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(32, -16), m_flip, eType_Player_Attack, m_attack_no));
		}
	//}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}


void Player::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Player::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		m_kill = true;
	}
}
void Player::Update() {
	m_pos_old = m_pos;
	switch (m_state) {
		//�ʏ���
	case eState_Idle:
		StateIdle();
		break;
		//�U�����
	case eState_Attack:
		StateAttack();
		break;
		//�_���[�W���
	case eState_Damage:
		StateDamage();
		break;
		//�_�E�����
	case eState_Down:
		StateDown();
		break;
	}
	//�����Ă����痎������Ԃֈڍs
	//if (m_is_ground && m_vec.y > GRAVITY * 4)
		//m_is_ground = false;
	//�d�͂ɂ�闎��
	//m_vec.y += GRAVITY;
	//m_pos += m_vec;


	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();

	//�X�N���[���ݒ�
	/*m_scroll.x = m_pos.x - 1280 / 2;
	m_scroll.y = m_pos.y - 500;*/

	if (!m_enable_area_change && !m_hit_area_change)
		m_enable_area_change = true;
	m_hit_area_change = false;
}

void Player::Draw() {
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//m_path.Draw();
	if (m_path.GetPathSize() > 0) {
		Utility::DrawCircle(GetScreenPos(m_path.GetPathPoint(m_path.GetPathSize() - 1)), 16, CVector4D(1, 0, 1, 1));
	}
	Utility::DrawCircle(GetScreenPos(m_pos), 16, CVector4D(1, 0, 0, 1));
	//�`��
	m_img.Draw();
	//DrawRect();
}
void Player::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_AreaChange:
		if (Base::CollisionRect(this, b)) {
			//�G���A�`�F���W�ɐG��Ă���
			m_hit_area_change = true;
			//�G���A�`�F���W�\�Ȃ�
			if (m_enable_area_change) {
				if (AreaChange* a = dynamic_cast<AreaChange*>(b)) {
					//�}�b�v�ƃG���A�`�F���W�I�u�W�F�N�g���폜
					KillByType(eType_Field);
					KillByType(eType_AreaChange);
					//���̃}�b�v�𐶐�
					Base::Add(new Map(a->m_nextArea, a->m_nextplayerpos));
					//�G���A�`�F���W�ꎞ�s����
					m_enable_area_change = false;
				}
			}
		}

		break;
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			CVector2D v;
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect,&v);
			if (t != NULL_TIP)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect,&v);
			if (t != NULL_TIP)
				m_pos.y = m_pos_old.y;
		}
		break;
	case eType_Child:
		if (Base::CollisionCircle(this, b)) {
			if (Child* c = dynamic_cast<Child*>(b)) {
				if (!c->m_parent) {
					c->m_parent = this;
					m_childs.push_back(c);
				}
			}
		}
		/*if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y));
			if (t != 0)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y));
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;*/
		//�S�[������
	/*case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			SetKill();
		}
		break;*/
		//�U���G�t�F�N�g�Ƃ̔���
	case eType_Enemy_Attack:
		//Slash�^�փL���X�g�A�^�ϊ��ł�����
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//�����U���̘A���_���[�W�h�~
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;

				}
				//Base::Add(new Effect("Effect_Blood",
					//m_pos + CVector2D(0, -64), m_flip));

				//Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -64), m_flip));
			}
		}
		break;
		
		//Field�^�փL���X�g�A�^�ϊ��ł�����
		/*if (Field* f = dynamic_cast<Field*>(b)) {
			//�n�ʂ�艺�ɂ�������
			if (m_pos.y > f->GetGroundY()) {
				//�n�ʂ̍����ɖ߂�
				m_pos.y = f->GetGroundY();
				//�������x���Z�b�g
				m_vec.y = 0;
				//�ڒn�t���OON
				m_is_ground = true;
			}
		}
		break;*/
	}

}

void Player::EraseChild(Child* c)
{
	//���X�g����q������
	auto it = std::find(m_childs.begin(), m_childs.end(), c);
	//�q�@�e������
	(*it)->m_parent = nullptr;
	m_childs.erase(it);
}

void Player::EraseAllChild()
{
	//�擪���疖���܂ł̃��[�v(�폜���邽��it���ς��̂ŁAit++�͂��Ȃ�)
	for (auto it = m_childs.begin(); it != m_childs.end();/*it++*/) {
		//	�q�@�e������
		(*it)->m_parent = nullptr;
		//�e�@�q�����X�g����O��
		it = m_childs.erase(it);
	}
}




