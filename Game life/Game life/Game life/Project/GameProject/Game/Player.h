#pragma once
#include "../Base/Base.h"
#include"Dijkstra.h"

class Player : public Base {
private:
	//���
	enum {														
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
	};
	//��ԕϐ�
	int m_state;
	int m_cnt;
	CVector2D m_target_point;
	Dijkstra m_path;
	CImage m_img;
	bool	m_flip;
	//���n�t���O
	bool	m_is_ground;
	//�U���ԍ�
	int m_attack_no;
	//�_���[�W�ԍ�
	int m_damage_no;

	int m_hp;


	int m_path_idx;
	//��`
	//�e��Ԃł̋���
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDown();

public:
	Player(const CVector2D& p, bool flip);
	~Player();
	void Update();
	void Draw();
	void Collision(Base* b);
	const CVector2D& GetPos() const {
		return m_pos;
	}
};
