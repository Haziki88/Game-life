#include "Gameover.h"
#include"../Title/Title.h"

Gameover::Gameover():Base(eType_Scene),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	m_img = COPY_RESOURCE("Gameover", CImage);
}

Gameover::~Gameover()
{
	Base::Add(new Title());
}

void Gameover::Update()
{
	if (PUSH(CInput::eButton1)) {
		m_kill = true;
	}
}

void Gameover::Draw()
{
	m_img.Draw();
}
