#pragma once
#include "../Base/Base.h"
#include"Dijkstra.h"

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
	int m_count;
	//視野距離
	float m_viewLength; 
	//視野角度
	float m_viewAngle;
	//追跡中かどうか
	bool m_isChase;
	//移動ベクトル
	CVector2D m_moveDir;
	CVector2D m_next_pos;
	CImage m_img;
	CVector2D m_target_point;
	Dijkstra m_path;
	bool	m_flip;
	//着地フラグ
	bool	m_is_ground;
	//攻撃番号
	int m_attack_no;
	//ダメージ番号
	int m_damage_no;
	int m_hp=100;
	int m_path_idx;

	//各状態での挙動

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
