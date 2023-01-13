#pragma once
#include "../Base/Base.h"
#include"Dijkstra.h"
class Child;
class Player : public Base {
	std::list<Child*> m_childs;
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
	//�G���A�`�F���W�t���O
	bool m_enable_area_change;
	//�G���A�`�F���W�I�u�W�F�N�g�ɐG��Ă���t���O
	bool m_hit_area_change;
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
	/// <summary>
	/// ���X�g����q���O��
	/// </summary>
	/// <param name="c">�O���q</param>
	void EraseChild(Child* c);
	/// <summary>
	/// ���X�g����S�Ă̎q���O��
	/// </summary>
	void EraseAllChild();
	const CVector2D& GetPos() const {
		return m_pos;
	}
	int gethp() {
		Base* player = Base::FindObject(eType_Player);
		if (player) {
			return m_hp;
		}
	}
	
};
