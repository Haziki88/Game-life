#pragma once
#include"../Base/Base.h"
class Player;
class Child :public Base {
private:
	enum {
		eState_Idle,
		eState_Down,
	};
	CImage m_img;
	int m_state;
	void StateIdle();
	void StateDown();
public:
	Player* m_parent;
	Child(const CVector2D& pos);
	~Child();
	void Update();
	void Draw();
};