#pragma once
#include "../Base/Base.h"
#include"Dijkstra.h"

class Enemy : public Base {
private:
	//���
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
		eState_Wait,
	};
	//��ԕϐ�
	int m_state;
	int m_cnt;
	int m_count;
	//���싗��
	float m_viewLength; 
	//����p�x
	float m_viewAngle;
	//�ǐՒ����ǂ���
	bool m_isChase;
	//�ړ��x�N�g��
	CVector2D m_moveDir;
	CVector2D m_next_pos;
	CImage m_img;
	CVector2D m_target_point;
	Dijkstra m_path;
	bool	m_flip;
	//���n�t���O
	bool	m_is_ground;
	//�U���ԍ�
	int m_attack_no;
	//�_���[�W�ԍ�
	int m_damage_no;
	int m_hp=100;
	int m_path_idx;

	//�e��Ԃł̋���

	void StateWait();
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDown();
	bool IsFoundPlayer() const;
public:
	Enemy(const CVector2D& p, bool flip);
	~Enemy();
	const CVector2D& GetForward() const {
		return m_moveDir;
	}
	void Update();
	void Draw();
	void Collision(Base* b);
};
