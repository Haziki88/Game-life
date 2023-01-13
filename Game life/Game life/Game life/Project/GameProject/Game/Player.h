#pragma once
#include "../Base/Base.h"
#include"Dijkstra.h"
class Child;
class Player : public Base {
	std::list<Child*> m_childs;
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
	int m_cnt;
	CVector2D m_target_point;
	Dijkstra m_path;
	CImage m_img;
	bool	m_flip;
	//着地フラグ
	bool	m_is_ground;
	//攻撃番号
	int m_attack_no;
	//ダメージ番号
	int m_damage_no;

	int m_hp;

	int m_path_idx;
	//エリアチェンジフラグ
	bool m_enable_area_change;
	//エリアチェンジオブジェクトに触れているフラグ
	bool m_hit_area_change;
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
	/// <summary>
	/// リストから子を外す
	/// </summary>
	/// <param name="c">外す子</param>
	void EraseChild(Child* c);
	/// <summary>
	/// リストから全ての子を外す
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
