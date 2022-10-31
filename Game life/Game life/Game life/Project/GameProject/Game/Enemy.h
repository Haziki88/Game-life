#pragma once
#include "../Base/Base.h"

class Enemy : public Base {
private:
	//状態
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
		eState_Wait,
	};
	//状態変数
	int m_state;
	int m_cnt;

	CImage m_img;
	bool	m_flip;
	//着地フラグ
	bool	m_is_ground;
	//攻撃番号
	int m_attack_no;
	//ダメージ番号
	int m_damage_no;
	int m_hp=100;

	//各状態での挙動

	void StateWait();
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDown();

public:
	Enemy(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};
