#pragma once

#include "../Base/Base.h"

class Game : public Base {
private:
	bool m_clear_flag=false;
public:
	Game();
	~Game();
	void Update();
};