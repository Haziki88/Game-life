#pragma once
#include "../Base/Base.h"

class Player : public Base {
private:
	//状態
	enum {														
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
	};
	//状態変数
	int m_state;
	CVector2D m_mouse_pos;
	CVector2D m_target_point;
	CImage m_img;
	bool	m_flip;
	//着地フラグ
	bool	m_is_ground;
	//攻撃番号
	int m_attack_no;
	//ダメージ番号
	int m_damage_no;

	int m_hp;

	//矩形
	//各状態での挙動
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
};
