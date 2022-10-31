#pragma once
#include "../Base/Base.h"

class Slash : public Base {
private:
	//画像オブジェクト
	CImage m_img;
	//反転フラグ
	bool	m_flip;
	//攻撃番号
	int m_attack_no;

public:
	Slash(const CVector2D& pos, bool flip, int type, int attack_no);
	void Update();
	void Draw();

	int GetAttackNo() {
		return m_attack_no;
	}
};
