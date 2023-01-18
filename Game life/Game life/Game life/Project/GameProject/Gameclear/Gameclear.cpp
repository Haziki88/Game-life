#include "Gameclear.h"
#include"../Title/Title.h"

Gameclear::Gameclear():Base(eType_Scene),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	m_img = COPY_RESOURCE("towerED", CImage);
}

Gameclear::~Gameclear()
{
	Base::Add(new Title());
}

void Gameclear::Update()
{
	if (PUSH(CInput::eButton1)) {
		m_kill = true;
	}
}

void Gameclear::Draw()
{
	m_img.Draw();
}
