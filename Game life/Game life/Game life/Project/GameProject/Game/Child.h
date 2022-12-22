#pragma once
#include"../Base/Base.h"
class Player;
class Child :public Base {
public:
	Player* m_parent;
	Child(const CVector2D& pos);
	~Child();
	void Update();
	void Draw();
};